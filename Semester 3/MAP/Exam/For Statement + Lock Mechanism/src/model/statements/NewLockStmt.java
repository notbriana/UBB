package model.statements;

import exceptions.CollectionException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

public record NewLockStmt(String var) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException {
        var symTable = state.symTable();
        var lockTable = state.lockTable();

        int location = lockTable.allocate(-1);

        if (symTable.isDefined(var))
            symTable.update(var, new IntValue(location));
        else
            symTable.put(var, new IntValue(location));

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {

        if (!typeEnv.isDefined(var)) {
            throw new UndefinedVariableException("newLock: variable " + var + " is not defined");
        }

        Type varType = typeEnv.lookup(var);
        if (!varType.equals(new IntType())) {
            throw new TypeMismatchException("newLock: variable must be int");
        }

        return typeEnv;
    }


    @Override
    public String toString() {
        return "newLock(" + var + ")";
    }


}
