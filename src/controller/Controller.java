package controller;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IExeStack;
import model.PrgState;
import model.statements.IStmt;
import repository.IRepository;

public record Controller(IRepository repo) {

    public void oneStep(final PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        final IExeStack<IStmt> stk = state.getExeStack();
        if (stk.isEmpty()) {
            throw new CollectionException("Execution stack is empty");
        }
        final IStmt crt = stk.pop();
        crt.execute(state);
    }

    public void allStep()
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        final PrgState prg = repo.getCrtPrg();
        repo.logPrgState(prg);
        while (!prg.getExeStack().isEmpty()) {
            oneStep(prg);
            repo.logPrgState(prg);
        }
    }
}
