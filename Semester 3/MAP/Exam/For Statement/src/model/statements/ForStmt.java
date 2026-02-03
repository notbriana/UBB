package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.expressions.RelExp;
import model.expressions.VarExp;
import model.types.IntType;
import model.types.Type;

public record ForStmt(String var, Exp exp1, Exp exp2, Exp exp3, IStmt stmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        IStmt newFor = new CompStmt(new AssignStmt(var, exp1), new WhileStmt(new RelExp(new VarExp(var), exp2, "<"), new CompStmt(stmt, new AssignStmt(var, exp3))));
        state.exeStack().push(newFor);
        return null;
    }

    @Override
    public String toString() {
        return "for(" + var + "=" + exp1 + ";" + var + "<" + exp2 + ";" + var + "=" + exp3 + ") " + stmt;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        if (!typeEnv.isDefined(var))
            throw new UndefinedVariableException("for: variable " + var + " not declared");

        if (!typeEnv.lookup(var).equals(new IntType()))
            throw new TypeMismatchException("for: variable must be int");

        if (!exp1.typecheck(typeEnv).equals(new IntType()))
            throw new TypeMismatchException("for: exp1 must be int");

        if (!exp2.typecheck(typeEnv).equals(new IntType()))
            throw new TypeMismatchException("for: exp2 must be int");

        if (!exp3.typecheck(typeEnv).equals(new IntType()))
            throw new TypeMismatchException("for: exp3 must be int");

        return typeEnv;
    }
}

