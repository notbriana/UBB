package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.ADTs.ISemaphoreTable;

import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.utils.Triplet;
import model.values.IntValue;
import model.values.Value;

import java.util.List;

public record ReleaseStmt(String var) implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (!state.symTable().isDefined(var))
            throw new TypeMismatchException("Variable " + var + " not defined");

        Value value = state.symTable().lookup(var);
        if (!(value instanceof IntValue))
            throw new TypeMismatchException("Variable " + var + " is not int");

        int foundIndex = ((IntValue) value).value();
        ISemaphoreTable semaphoreTable = state.semaphoreTable();

        synchronized (semaphoreTable) {
            if (!semaphoreTable.containsKey(foundIndex)) {
                throw new UndefinedVariableException("Doesn't exist");
            }

            Triplet<Integer, List<Integer>, Integer> entry = semaphoreTable.get(foundIndex);
            int N1 = entry.getFirst();
            List<Integer> list = entry.getSecond();
            int N2 = entry.getThird();

            if (list.contains(state.getId())) {
                list.remove((Integer) state.getId());
                semaphoreTable.update(foundIndex, new Triplet<>(N1, list, N2));
            }
        }
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        if (!typeEnv.isDefined(var) || !typeEnv.lookup(var).equals(new IntType()))
            throw new TypeMismatchException("Variable must be int");
        return typeEnv;
    }
}


