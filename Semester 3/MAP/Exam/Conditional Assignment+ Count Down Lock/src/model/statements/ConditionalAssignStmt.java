package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.Type;

public record ConditionalAssignStmt(String varName, Exp exp1, Exp exp2, Exp exp3) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        IStmt newStmt = new IfStmt(exp1, new AssignStmt(varName, exp2), new AssignStmt(varName, exp3));
        state.exeStack().push(newStmt);
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return varName + " = (" + exp1 + ") ? " + exp2 + " : " + exp3;
    }
}
