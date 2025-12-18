package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.Type;

public class NopStmt implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "nop";
    }
}