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

public record NewBarrier(String var, Exp exp) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        Value v = exp.eval(state.symTable(), state.heap());

        if (!(v instanceof IntValue))
            throw new TypeMismatchException("Expression must evaluate to an integer");

        int Nr = ((IntValue) v).value();

        int newFreeLocation = state.barrierTable().addBarrier(Nr);

        if (!state.symTable().isDefined(var))
            throw new UndefinedVariableException("Variable " + var + " does not exist in SymTable");

        Value varValue = state.symTable().lookup(var);
        if (!(varValue instanceof IntValue))
            throw new TypeMismatchException("Variable " + var + " must have type int");

        state.symTable().update(var, new IntValue(newFreeLocation));

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type expType = exp.typecheck(typeEnv);
        if (!expType.equals(new IntType()))
            throw new TypeMismatchException("Expression must be int type");

        if (!typeEnv.isDefined(var))
            throw new UndefinedVariableException("Variable " + var + " not defined");

        Type varType = typeEnv.lookup(var);
        if (!varType.equals(new IntType()))
            throw new TypeMismatchException("Variable " + var + " must be int type");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "newBarrier(" + var + ", " + exp + ")";
    }
}