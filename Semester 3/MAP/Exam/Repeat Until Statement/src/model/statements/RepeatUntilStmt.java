package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.expressions.NotExp;
import model.types.BoolType;
import model.types.Type;

public record RepeatUntilStmt(IStmt stmt, Exp exp) implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        IStmt newRepeat = new CompStmt(stmt, new WhileStmt(new NotExp(exp), stmt));
        state.exeStack().push(newRepeat);
        return null;
    }

    @Override
    public String toString() {
        return "repeat(" + stmt + ") until(" + exp + ")";
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type expType = exp.typecheck(typeEnv);
        if (!expType.equals(new BoolType())) {
            throw new TypeMismatchException("Repeat UNTIL condition must be boolean");
        }

        return typeEnv;
    }
}

