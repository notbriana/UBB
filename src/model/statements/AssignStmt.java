package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.expressions.Exp;
import model.values.Value;

public record AssignStmt(String varName, Exp expression) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value val = expression.eval(state.symTable(), state.heap());

        if (!state.symTable().isDefined(varName)) {
            throw new UndefinedVariableException("Variable " + varName + " is not defined");
        }

        Value varValue = state.symTable().lookup(varName);
        if (!val.getType().equals(varValue.getType())) {
            throw new TypeMismatchException("Type mismatch for variable " + varName);
        }

        state.symTable().update(varName, val);
        return state;
    }

    @Override
    public String toString() {
        return varName + " = " + expression.toString();
    }
}