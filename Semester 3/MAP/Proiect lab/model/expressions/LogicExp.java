package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;


public record LogicExp(Exp exp1, Exp exp2, String operation) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {

        Value v1 = exp1.eval(symTable, heap);
        Value v2 = exp2.eval(symTable, heap);

        if (!(v1.getType() instanceof BoolType)) {
            throw new TypeMismatchException("First operand is not a boolean");
        }
        if (!(v2.getType() instanceof BoolType)) {
            throw new TypeMismatchException("Second operand is not a boolean");
        }

        BoolValue b1 = (BoolValue) v1;
        BoolValue b2 = (BoolValue) v2;

        boolean result = switch (operation) {
            case "&&" -> b1.value() && b2.value();
            case "||" -> b1.value() || b2.value();
            default -> throw new TypeMismatchException("Unknown operation: " + operation);
        };

        return new BoolValue(result);
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typ1 = exp1.typecheck(typeEnv);
        Type typ2 = exp2.typecheck(typeEnv);

        if (typ1.equals(new BoolType())) {
            if (typ2.equals(new BoolType())) {
                return new BoolType();
            } else {
                throw new TypeMismatchException("Second operand is not a boolean");
            }
        } else {
            throw new TypeMismatchException("First operand is not a boolean");
        }
    }

    @Override
    public String toString() {
        return exp1.toString() + " " + operation + " " + exp2.toString();
    }
}