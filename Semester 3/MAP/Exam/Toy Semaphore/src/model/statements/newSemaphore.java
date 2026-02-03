package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISemaphoreTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.IntType;
import model.types.Type;
import model.utils.Triplet;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;

public record newSemaphore(String var, Exp e1, Exp e2) implements IStmt {


    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        Value v1 = e1.eval(state.symTable(), state.heap());
        Value v2 = e2.eval(state.symTable(), state.heap());

        if (!(v1 instanceof IntValue))
            throw new TypeMismatchException("E1 is not an int");

        int number1 = ((IntValue) v1).value();

        if (!(v2 instanceof IntValue))
            throw new TypeMismatchException("E2 is not an int");

        int number2 = ((IntValue) v2).value();

        ISemaphoreTable semaphoreTable = state.semaphoreTable();

        int newIndex;
        synchronized (semaphoreTable) {
            newIndex = semaphoreTable.getFreeAddress();
            semaphoreTable.put(newIndex, new Triplet<>(number1, new ArrayList<>(), number2));

        }
        Value val = state.symTable().lookup(var);
        if (!(val instanceof IntValue))
            throw new TypeMismatchException("Var is not int");

        state.symTable().update(var, new IntValue(newIndex));
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws CollectionException, TypeMismatchException, UndefinedVariableException {
        if (!typeEnv.isDefined(var) || !typeEnv.lookup(var).equals(new IntType()))
            throw new TypeMismatchException("Variable must be int");
        if (!e1.typecheck(typeEnv).equals(new IntType()) ||
                !e2.typecheck(typeEnv).equals(new IntType()))
            throw new TypeMismatchException("Exp must be int");
        return typeEnv;
    }
}
