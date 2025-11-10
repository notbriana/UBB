package model.statements;

import model.ADTs.IExeStack;
import model.PrgState;

public record CompStmt(IStmt first, IStmt second) implements IStmt {

    @Override
    public PrgState execute(final PrgState state) {
        final IExeStack<IStmt> stk = state.getExeStack();
        stk.push(second);
        stk.push(first);
        return state;
    }

    @Override
    public String toString() {
        return "(" + first + "; " + second + ")";
    }
}
