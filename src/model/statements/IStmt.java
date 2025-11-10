package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.PrgState;

public interface IStmt {
    PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException;
}
