package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.Type;
import model.values.Value;

public record AssignStmt(String varName, Exp expression) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value val = expression.eval(state.symTable(), state.heap());

        if (!state.symTable().isDefined(varName)) {
            throw new UndefinedVariableException("Variable " + varName + " is not defined");
        }

        Value varValue = state.symTable().lookup(varName);
        if (!val.getType().equals(varValue.getType())) {
            throw new TypeMismatchException("Type mismatch for variable " + varName);
        }

        state.symTable().update(varName, val);
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typevar = typeEnv.lookup(varName);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(typexp)) {
            return typeEnv;
        } else {
            throw new TypeMismatchException("Assignment: right hand side and left hand side have different types");
        }
    }

    @Override
    public String toString() {
        return varName + " = " + expression.toString();
    }
}