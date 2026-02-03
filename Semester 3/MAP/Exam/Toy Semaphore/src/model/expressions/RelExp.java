package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.Value;

public record RelExp(Exp exp1, Exp exp2, String operation) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {

        Value v1 = exp1.eval(symTable, heap);
        Value v2 = exp2.eval(symTable, heap);

        if (!(v1.getType() instanceof IntType)) {
            throw new TypeMismatchException("First operand is not an integer");
        }
        if (!(v2.getType() instanceof IntType)) {
            throw new TypeMismatchException("Second operand is not an integer");
        }

        IntValue i1 = (IntValue) v1;
        IntValue i2 = (IntValue) v2;

        int n1 = i1.value();
        int n2 = i2.value();
        boolean result = switch (operation) {
            case "<" -> n1 < n2;
            case "<=" -> n1 <= n2;
            case ">" -> n1 > n2;
            case ">=" -> n1 >= n2;
            case "==" -> n1 == n2;
            case "!=" -> n1 != n2;
            default -> throw new TypeMismatchException("Unknown operation: " + operation);
        };

        return new BoolValue(result);
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typ1 = exp1.typecheck(typeEnv);
        Type typ2 = exp2.typecheck(typeEnv);

        if (typ1.equals(new IntType())) {
            if (typ2.equals(new IntType())) {
                return new BoolType();
            } else {
                throw new TypeMismatchException("Second operand is not an integer");
            }
        } else {
            throw new TypeMismatchException("First operand is not an integer");
        }
    }

    @Override
    public String toString() {
        return exp1.toString() + " " + operation + " " + exp2.toString();
    }
}