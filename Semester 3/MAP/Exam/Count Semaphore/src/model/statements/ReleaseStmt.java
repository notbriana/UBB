package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import javafx.util.Pair;
import model.ADTs.ISemaphoreTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public record ReleaseStmt(String var) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        Value v = state.symTable().lookup(var);

        if (!(v instanceof IntValue)) {
            throw new TypeMismatchException("Release: variable " + var + " is not int");
        }

        int index = ((IntValue) v).value();
        ISemaphoreTable semTable = state.semaphoreTable();

        if (!semTable.containsKey(index)) {
            throw new UndefinedVariableException("Release: index " + index + " not in SemaphoreTable");
        }

        Pair<Integer, List<Integer>> entry = semTable.get(index);
        int N1 = entry.getKey();
        List<Integer> list = entry.getValue();

        int currentId = state.getId();

        if (list.contains(currentId)) {
            List<Integer> newList = new ArrayList<>(list);
            newList.remove((Integer) currentId);
            semTable.put(index, new Pair<>(N1, newList));
        }

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type varType = typeEnv.lookup(var);
        if (!varType.equals(new IntType())) {
            throw new TypeMismatchException("release: variable " + var + " is not int");
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return "release(" + var + ")";
    }
}
