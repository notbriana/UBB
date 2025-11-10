package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.values.Value;

public interface Exp {
    Value eval(ISymbolTable<String, Value> symTable)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException;
}
