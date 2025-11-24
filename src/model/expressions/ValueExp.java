package model.expressions;

import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.values.Value;

public record ValueExp(Value value) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap) {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}