package model.statements;

import exceptions.CollectionException;
import exceptions.TypeMismatchException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

public record LockStmt(String var) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException {
        var symTable = state.symTable();
        var lockTable = state.lockTable();

        if (!symTable.isDefined(var))
            throw new CollectionException("lock: variable not defined");

        int index = ((IntValue) symTable.lookup(var)).value();

        synchronized (lockTable) {
            if (!lockTable.isDefined(index))
                throw new CollectionException("lock: invalid lock index");

            if (lockTable.get(index) == -1)
                lockTable.update(index, state.getId());
            else
                state.exeStack().push(this);
        }

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> env)
            throws TypeMismatchException, CollectionException {
        if (!env.lookup(var).equals(new IntType()))
            throw new TypeMismatchException("lock: var must be int");
        return env;
    }


}

