package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.expressions.Exp;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public record WriteHeapStmt(String varName, Exp expression) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (!state.symTable().isDefined(varName)) {
            throw new UndefinedVariableException("Variable " + varName + " is not defined");
        }

        Value varValue = state.symTable().lookup(varName);

        if (!(varValue.getType() instanceof RefType)) {
            throw new TypeMismatchException("Variable " + varName + " must be of RefType");
        }

        RefValue refValue = (RefValue) varValue;
        int address = refValue.getAddr();

        if (!state.heap().isDefined(address)) {
            throw new CollectionException("Address " + address + " is not defined in the heap");
        }

        Value expValue = expression.eval(state.symTable(), state.heap());

        Type locationType = refValue.locationType();
        if (!expValue.getType().equals(locationType)) {
            throw new TypeMismatchException("Type of expression does not match location type");
        }

        state.heap().update(address, expValue);

        return null;
    }

    @Override
    public String toString() {
        return "wH(" + varName + ", " + expression.toString() + ")";
    }
}