package model.statements;


import exceptions.CollectionException;
import exceptions.TypeMismatchException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

public class UnlockStmt implements IStmt {
    private final String var;

    public UnlockStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws CollectionException {
        var symTable = state.symTable();
        var lockTable = state.lockTable();

        if (!symTable.isDefined(var))
            throw new CollectionException("unlock: variable not defined");

        int index = ((IntValue) symTable.lookup(var)).value();

        synchronized (lockTable) {
            if (lockTable.isDefined(index) &&
                    lockTable.get(index) == state.getId())
                lockTable.update(index, -1);
        }

        return null;
    }


    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> env)
            throws TypeMismatchException, CollectionException {
        if (!env.lookup(var).equals(new IntType()))
            throw new TypeMismatchException("unlock: var must be int");
        return env;
    }


}

