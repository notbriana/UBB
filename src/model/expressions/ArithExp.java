package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.types.IntType;
import model.values.IntValue;
import model.values.Value;

public record ArithExp(char op, Exp e1, Exp e2) implements Exp {

    @Override
    public Value eval(final ISymbolTable<String, Value> symTable)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {
        final Value v1 = e1.eval(symTable);
        if (!v1.getType().equals(new IntType())) {
            throw new TypeMismatchException("first operand not integer");
        }
        final Value v2 = e2.eval(symTable);
        if (!v2.getType().equals(new IntType())) {
            throw new TypeMismatchException("second operand not integer");
        }
        final int n1 = ((IntValue) v1).value();
        final int n2 = ((IntValue) v2).value();

        return switch (op) {
            case '+' -> new IntValue(n1 + n2);
            case '-' -> new IntValue(n1 - n2);
            case '*' -> new IntValue(n1 * n2);
            case '/' -> {
                if (n2 == 0) {
                    throw new DivisionByZeroException();
                }
                yield new IntValue(n1 / n2);
            }
            default -> throw new TypeMismatchException("unknown arithmetic operator: " + op);
        };
    }

    @Override
    public String toString() {
        return e1 + " " + op + " " + e2;
    }
}
