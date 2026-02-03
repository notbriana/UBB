package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ILatchTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

public record CountDownStmt(String varName) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        IntValue indexVal = (IntValue) state.symTable().lookup(varName);
        int index = indexVal.value();

        ILatchTable latchTable = state.latchTable();
        synchronized (latchTable) {
            if (!latchTable.isDefined(index))
                throw new UndefinedVariableException("CountDown: latch index not found");

            int value = latchTable.get(index);
            if (value > 0)
                latchTable.update(index, value - 1);

            // write to output the current PrgState id
            state.out().add(new IntValue(state.getId()));
        }
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {

        if (!typeEnv.isDefined(varName))
            throw new UndefinedVariableException("countDown: variable " + varName + " not defined");

        if (!typeEnv.lookup(varName).equals(new IntType()))
            throw new TypeMismatchException("countDown: variable must be int");

        return typeEnv;
    }


    @Override
    public String toString() {
        return "countDown(" + varName + ")";
    }

}
