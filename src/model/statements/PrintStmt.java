package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.expressions.Exp;
import model.values.Value;

public record PrintStmt(Exp expression) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value val = expression.eval(state.symTable(), state.heap());
        state.out().add(val);
        return null;
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
}