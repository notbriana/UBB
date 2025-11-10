package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IExeStack;
import model.PrgState;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public record IfStmt(Exp condition, IStmt thenS, IStmt elseS) implements IStmt {

    @Override
    public PrgState execute(final PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        final Value cond = condition.eval(state.getSymTable());
        if (!cond.getType().equals(new BoolType())) {
            throw new TypeMismatchException("If condition must be boolean");
        }
        final boolean value = ((BoolValue) cond).value();
        final IExeStack<IStmt> stk = state.getExeStack();
        stk.push(value ? thenS : elseS);
        return state;
    }

    @Override
    public String toString() {
        return "If(" + condition + ") Then(" + thenS + ") Else(" + elseS + ")";
    }
}
