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

public record NotExp(Exp exp) implements Exp {

    @Override
    public String toString() {
        return "!(" + exp + ")";
    }

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap) throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {
        Value v = exp.eval(symTable, heap);

        if (!v.getType().equals(new BoolType())) {
            throw new TypeMismatchException("NOT expression requires a boolean");
        }

        boolean val = ((BoolValue) v).value();
        return new BoolValue(!val);
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type t = exp.typecheck(typeEnv);
        if (!t.equals(new BoolType())) {
            throw new TypeMismatchException("NOT expression requires a boolean");
        }
        return new BoolType();
    }
}