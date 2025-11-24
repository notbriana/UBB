package controller;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.statements.IStmt;
import model.utils.GarbageCollector;
import repository.IRepository;

public class Controller {
    private final IRepository repo;

    public Controller(IRepository repo) {
        this.repo = repo;
    }

    public void oneStep(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (state.exeStack().isEmpty()) {
            throw new CollectionException("Execution stack is empty");
        }

        IStmt currentStmt = state.exeStack().pop();
        currentStmt.execute(state);
    }

    public void allStep()
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        PrgState prg = repo.getCrtPrg();
        repo.logPrgStateExec();

        while (!prg.exeStack().isEmpty()) {
            oneStep(prg);

            prg.heap().setContent(
                    GarbageCollector.safeGarbageCollector(
                            GarbageCollector.getAddrFromSymTable(
                                    prg.symTable().getContent().values()
                            ),
                            prg.heap().getContent()
                    )
            );

            repo.logPrgStateExec();
        }
    }

    public IRepository getRepo() {
        return repo;
    }
}