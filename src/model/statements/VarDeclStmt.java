package model.statements;

import exceptions.CollectionException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.Type;
import model.values.Value;

public record VarDeclStmt(String name, Type type) implements IStmt {

    @Override
    public PrgState execute(final PrgState state) throws CollectionException {
        final ISymbolTable<String, Value> sym = state.getSymTable();

        if (sym.isDefined(name)) {
            throw new CollectionException("Variable already declared: " + name);
        }

        final Value defaultValue = type.defaultValue();
        sym.put(name, defaultValue);

        return state;
    }

    @Override
    public String toString() {
        return type + " " + name;
    }
}
