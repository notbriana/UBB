package model.expressions;

import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.Type;
import model.values.Value;

public record ValueExp(Value value) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap) {
        return value;
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv) {
        return value.getType();
    }

    @Override
    public String toString() {
        return value.toString();
    }
}