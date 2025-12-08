package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public record IfStmt(Exp condition, IStmt thenStmt, IStmt elseStmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value condValue = condition.eval(state.symTable(), state.heap());

        if (!(condValue.getType() instanceof BoolType)) {
            throw new TypeMismatchException("Condition is not a boolean");
        }

        BoolValue boolValue = (BoolValue) condValue;
        if (boolValue.value()) {
            state.exeStack().push(thenStmt);
        } else {
            state.exeStack().push(elseStmt);
        }

        return null;
    }

    @Override
    public String toString() {
        return "if (" + condition.toString() + ") then " + thenStmt.toString() + " else " + elseStmt.toString();
    }
}