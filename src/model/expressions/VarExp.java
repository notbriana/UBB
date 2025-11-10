package model.expressions;

import exceptions.CollectionException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.values.Value;

public record VarExp(String id) implements Exp {

    @Override
    public Value eval(final ISymbolTable<String, Value> symTable)
            throws CollectionException, UndefinedVariableException {
        if (!symTable.isDefined(id)) {
            throw new UndefinedVariableException(id);
        }
        return symTable.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
