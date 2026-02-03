package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public record MULExp(Exp exp1, Exp exp2) implements Exp {
    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap) throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {
        Value v1 = exp1.eval(symTable, heap);
        Value v2 = exp2.eval(symTable, heap);

        if (!(v1 instanceof IntValue) || !(v2 instanceof IntValue)) {
            throw new TypeMismatchException("MUL operands must be integers");
        }


        int n1 = ((IntValue) v1).value();
        int n2 = ((IntValue) v2).value();

        int result = (n1 * n2) - (n1 + n2);

        return new IntValue(result);
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type t1 = exp1.typecheck(typeEnv);
        Type t2 = exp2.typecheck(typeEnv);

        if (!t1.equals(new IntType()) || !t2.equals(new IntType())) {
            throw new TypeMismatchException("MUL operands must be int");
        }

        return new IntType();
    }

    @Override
    public String toString() {
        return "MUL(" + exp1 + "," + exp2 + ")";
    }
}

