package model.expressions;

import model.ADTs.ISymbolTable;
import model.values.Value;

public record ValueExp(Value value) implements Exp {

    @Override
    public Value eval(final ISymbolTable<String, Value> symTable) {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
