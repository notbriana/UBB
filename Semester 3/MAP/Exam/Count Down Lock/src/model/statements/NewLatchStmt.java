package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public record NewLatchStmt(String varName, Exp exp) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        Value val = exp.eval(state.symTable(), state.heap());

        if (!(val instanceof IntValue))
            throw new TypeMismatchException("newLatch: expression must evaluate to int");

        int num = ((IntValue) val).value();

        synchronized (state.latchTable()) {
            int id = state.latchTable().allocate(num);

            if (!state.symTable().isDefined(varName))
                throw new UndefinedVariableException("newLatch: variable " + varName + " not defined");

            if (!(state.symTable().lookup(varName).getType() instanceof IntType))
                throw new TypeMismatchException("newLatch: variable " + varName + " must be int");

            state.symTable().update(varName, new IntValue(id));
        }

        return null;
    }


    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {

        if (!typeEnv.isDefined(varName))
            throw new UndefinedVariableException("newLatch: variable " + varName + " not defined");

        if (!typeEnv.lookup(varName).equals(new IntType()))
            throw new TypeMismatchException("newLatch: variable must be int");

        Type expType = exp.typecheck(typeEnv);
        if (!expType.equals(new IntType()))
            throw new TypeMismatchException("newLatch: expression must be int");

        return typeEnv;
    }


    @Override
    public String toString() {
        return "newLatch(" + varName + ", " + exp + ")";
    }


}

