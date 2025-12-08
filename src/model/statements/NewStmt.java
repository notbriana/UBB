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

public record NewStmt(String varName, Exp expression) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (!state.symTable().isDefined(varName)) {
            throw new UndefinedVariableException("Variable " + varName + " is not defined");
        }

        Value varValue = state.symTable().lookup(varName);
        Type varType = varValue.getType();

        if (!(varType instanceof RefType)) {
            throw new TypeMismatchException("Variable " + varName + " must be of RefType");
        }

        RefType refType = (RefType) varType;
        Type locationType = refType.inner();

        Value expValue = expression.eval(state.symTable(), state.heap());

        if (!expValue.getType().equals(locationType)) {
            throw new TypeMismatchException("Type of expression does not match location type of " + varName);
        }

        int newAddress = state.heap().allocate(expValue);

        RefValue newRefValue = new RefValue(newAddress, locationType);
        state.symTable().update(varName, newRefValue);

        return null;
    }

    @Override
    public String toString() {
        return "new(" + varName + ", " + expression.toString() + ")";
    }
}