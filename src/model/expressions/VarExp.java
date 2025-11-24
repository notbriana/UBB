package model.expressions;

import exceptions.CollectionException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.values.Value;

public record VarExp(String id) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap)
            throws UndefinedVariableException, CollectionException {
        return symTable.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }
}

