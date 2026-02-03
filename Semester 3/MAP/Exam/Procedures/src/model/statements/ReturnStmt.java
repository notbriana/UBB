package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.Type;

public class ReturnStmt implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException,
            TypeMismatchException, UndefinedVariableException {
        state.popSymTable();
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "return";
    }
}

