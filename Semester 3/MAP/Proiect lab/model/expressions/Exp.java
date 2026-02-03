package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.Type;
import model.values.Value;

public interface Exp {
    Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException;

    Type typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException;

}