package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.Type;

public interface IStmt {
    PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException;

    ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException;
}