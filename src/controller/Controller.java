package controller;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.utils.GarbageCollector;
import repository.IRepository;

import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository repo;
    private ExecutorService executor;

    public Controller(IRepository repo) {
        this.repo = repo;
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (CollectionException e) {
                System.err.println("Error logging: " + e.getMessage());
            }
        });

        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (p::oneStep))
                .collect(Collectors.toList());


        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        System.err.println("Error during execution: " + e.getMessage());
                        if (e.getCause() instanceof CollectionException ||
                                e.getCause() instanceof DivisionByZeroException ||
                                e.getCause() instanceof TypeMismatchException ||
                                e.getCause() instanceof UndefinedVariableException) {
                            System.err.println("Statement execution error: " + e.getCause().getMessage());
                        }
                        return null;
                    }
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        prgList.addAll(newPrgList);

        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (CollectionException e) {
                System.err.println("Error logging: " + e.getMessage());
            }
        });

        repo.setPrgList(prgList);
    }

    public void allStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);

        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        while (prgList.size() > 0) {
            conservativeGarbageCollector(prgList);

            oneStepForAllPrg(prgList);

            prgList = removeCompletedPrg(repo.getPrgList());
        }

        executor.shutdownNow();

        repo.setPrgList(prgList);
    }

    private void conservativeGarbageCollector(List<PrgState> prgList) {
        List<Integer> allAddresses = prgList.stream()
                .map(p -> GarbageCollector.getAddrFromSymTable(
                        p.symTable().getContent().values()
                ))
                .flatMap(List::stream)
                .collect(Collectors.toList());

        if (!prgList.isEmpty()) {
            PrgState firstPrg = prgList.get(0);
            firstPrg.heap().setContent(
                    GarbageCollector.safeGarbageCollector(
                            allAddresses,
                            firstPrg.heap().getContent()
                    )
            );
        }
    }

    public IRepository getRepo() {
        return repo;
    }
}