package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import javafx.util.Pair;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public record AwaitStmt(String var) implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        if (!state.symTable().isDefined(var))
            throw new UndefinedVariableException("Variable " + var + " not defined");

        Value v = state.symTable().lookup(var);
        if (!(v instanceof IntValue))
            throw new TypeMismatchException("Barrier variable must be an IntValue");

        int foundIndex = ((IntValue) v).value();

        if (!state.barrierTable().containsKey(foundIndex))
            throw new UndefinedVariableException("Barrier index not found: " + foundIndex);

        synchronized (state.barrierTable()) {
            Pair<Integer, List<Integer>> entry = state.barrierTable().lookup(foundIndex);
            int N1 = entry.getKey();
            List<Integer> List1 = entry.getValue();
            int NL = List1.size();

            if (N1 > NL) {
                if (List1.contains(state.getId())) {
                    state.exeStack().push(this);
                } else {
                    List<Integer> newList = new ArrayList<>(List1);
                    newList.add(state.getId());
                    state.barrierTable().update(foundIndex, new Pair<>(N1, newList));
                    state.exeStack().push(this);
                }
            }
        }

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        if (!typeEnv.isDefined(var))
            throw new UndefinedVariableException("Variable " + var + " not defined");

        Type varType = typeEnv.lookup(var);
        if (!varType.equals(new IntType()))
            throw new TypeMismatchException("Variable " + var + " must be int type");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "await(" + var + ")";
    }
}