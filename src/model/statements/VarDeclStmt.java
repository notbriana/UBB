package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.types.Type;
import model.values.Value;

public record VarDeclStmt(String varName, Type type) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (state.symTable().isDefined(varName)) {
            throw new CollectionException("Variable " + varName + " is already defined");
        }

        Value defaultValue = type.defaultValue();
        state.symTable().put(varName, defaultValue);
        return state;
    }

    @Override
    public String toString() {
        return type.toString() + " " + varName;
    }
}