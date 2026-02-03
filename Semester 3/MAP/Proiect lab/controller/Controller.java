package controller;

import exceptions.CollectionException;
import model.PrgState;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;

import java.util.ArrayList;
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
        this.executor = Executors.newFixedThreadPool(2);
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
        if (prgList.isEmpty()) return;

        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (CollectionException e) {
                System.err.println("Error logging: " + e.getMessage());
            }
        });

        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) p::oneStep)
                .collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        System.err.println("Error during execution: " + e.getMessage());
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

    public void oneStepForAllPrg() {
        try {
            List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
            if (!prgList.isEmpty()) {
                oneStepForAllPrg(prgList);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void allStep() throws InterruptedException {
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        while (!prgList.isEmpty()) {
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repo.getPrgList());
        }
        shutdownExecutor();
        repo.setPrgList(prgList);
    }

    public void shutdownExecutor() {
        if (executor != null && !executor.isShutdown()) {
            executor.shutdownNow();
        }
    }

    public IRepository getRepo() {
        return repo;
    }

    public List<Integer> getPrgIds() {
        return repo.getPrgList().stream()
                .map(PrgState::getId)
                .collect(Collectors.toList());
    }

    public PrgState getPrgById(int id) {
        return repo.getPrgList().stream()
                .filter(p -> p.getId() == id)
                .findFirst()
                .orElse(null);
    }

    public List<String> getOut() {
        if (repo.getPrgList().isEmpty()) return new ArrayList<>();
        return repo.getPrgList().get(0).out().getList().stream()
                .map(Value::toString)
                .collect(Collectors.toList());
    }

    public List<String> getFileTable() {
        if (repo.getPrgList().isEmpty()) return new ArrayList<>();
        return new ArrayList<>(repo.getPrgList().get(0).fileTable().getContent().keySet().stream()
                .map(StringValue::toString)
                .toList());
    }

    public List<String> getHeapEntries() {
        if (repo.getPrgList().isEmpty()) return new ArrayList<>();
        return repo.getPrgList().get(0).heap().getContent().entrySet().stream()
                .map(e -> e.getKey() + " -> " + e.getValue())
                .collect(Collectors.toList());
    }

    public List<String> getSymTableEntries(PrgState prg) {
        return prg.symTable().getContent().entrySet().stream()
                .map(e -> e.getKey() + " -> " + e.getValue())
                .collect(Collectors.toList());
    }
    

    public List<String> getExeStackStrings(PrgState prg) {
        return prg.exeStack().getStackReversed().stream()
                .map(Object::toString)
                .toList();
    }


}
