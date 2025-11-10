package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public record LogicExp(String op, Exp e1, Exp e2) implements Exp {

    @Override
    public Value eval(final ISymbolTable<String, Value> symTable)
            throws TypeMismatchException, UndefinedVariableException, CollectionException, DivisionByZeroException {
        final Value v1 = e1.eval(symTable);
        if (!v1.getType().equals(new BoolType())) {
            throw new TypeMismatchException("first operand not boolean");
        }
        final Value v2 = e2.eval(symTable);
        if (!v2.getType().equals(new BoolType())) {
            throw new TypeMismatchException("second operand not boolean");
        }
        final boolean b1 = ((BoolValue) v1).value();
        final boolean b2 = ((BoolValue) v2).value();

        return switch (op) {
            case "&&" -> new BoolValue(b1 && b2);
            case "||" -> new BoolValue(b1 || b2);
            default -> throw new TypeMismatchException("unknown logical operator: " + op);
        };
    }

    @Override
    public String toString() {
        return e1 + " " + op + " " + e2;
    }
}
