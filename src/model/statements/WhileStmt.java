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

public record WhileStmt(Exp expression, IStmt statement) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value conditionValue = expression.eval(state.symTable(), state.heap());

        if (!(conditionValue.getType() instanceof BoolType)) {
            throw new TypeMismatchException("Condition expression is not a boolean");
        }

        BoolValue boolValue = (BoolValue) conditionValue;

        if (boolValue.value()) {
            state.exeStack().push(this);
            state.exeStack().push(statement);
        }

        return null;
    }

    @Override
    public String toString() {
        return "while (" + expression.toString() + ") " + statement.toString();
    }
}