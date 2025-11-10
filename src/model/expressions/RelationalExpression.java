package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.Value;

public record RelationalExpression(Exp exp1, Exp exp2, String op) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {

        Value v1 = exp1.eval(symTable);
        if (!(v1.getType() instanceof IntType))
            throw new TypeMismatchException("First operand is not an integer");

        Value v2 = exp2.eval(symTable);
        if (!(v2.getType() instanceof IntType))
            throw new TypeMismatchException("Second operand is not an integer");

        int n1 = ((IntValue) v1).value();
        int n2 = ((IntValue) v2).value();

        return switch (op) {
            case "<" -> new BoolValue(n1 < n2);
            case "<=" -> new BoolValue(n1 <= n2);
            case "==" -> new BoolValue(n1 == n2);
            case "!=" -> new BoolValue(n1 != n2);
            case ">" -> new BoolValue(n1 > n2);
            case ">=" -> new BoolValue(n1 >= n2);
            default -> throw new TypeMismatchException("Invalid relational operator: " + op);
        };
    }

    @Override
    public String toString() {
        return exp1 + " " + op + " " + exp2;
    }
}
