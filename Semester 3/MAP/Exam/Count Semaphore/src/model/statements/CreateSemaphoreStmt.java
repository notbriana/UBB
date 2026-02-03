package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import javafx.util.Pair;
import model.ADTs.ISemaphoreTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;

public record CreateSemaphoreStmt(String var, Exp exp) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        Value v = exp.eval(state.symTable(), state.heap());
        if (!(v instanceof IntValue)) {
            throw new TypeMismatchException("CreateSemaphore: expression must evaluate to int");
        }
        int number = ((IntValue) v).value();

        if (!state.symTable().isDefined(var)) {
            throw new UndefinedVariableException("CreateSemaphore: variable " + var + " not defined");
        }

        Value varVal = state.symTable().lookup(var);
        if (!(varVal.getType() instanceof IntType)) {
            throw new TypeMismatchException("CreateSemaphore: variable " + var + " is not int type");
        }

        ISemaphoreTable semTable = state.semaphoreTable();

        int location = semTable.getFreeLocation();
        semTable.put(location, new Pair<>(number, new ArrayList<>()));

        state.symTable().update(var, new IntValue(location));

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type varType = typeEnv.lookup(var);
        if (!varType.equals(new IntType())) {
            throw new TypeMismatchException("createSemaphore: variable " + var + " is not int");
        }

        Type expType = exp.typecheck(typeEnv);
        if (!expType.equals(new IntType())) {
            throw new TypeMismatchException("createSemaphore: expression is not int");
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return "createSemaphore(" + var + ", " + exp.toString() + ")";
    }
}
