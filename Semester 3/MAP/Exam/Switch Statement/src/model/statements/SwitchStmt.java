package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.expressions.RelExp;
import model.types.Type;

public record SwitchStmt(Exp exp, Exp case1, Exp case2, IStmt stmt1, IStmt stmt2, IStmt defaultStmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        IStmt newEx = new IfStmt(new RelExp(exp, case1, "=="), stmt1, new IfStmt(new RelExp(exp, case2, "=="), stmt2, defaultStmt));
        state.exeStack().push(newEx);
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type expType = exp.typecheck(typeEnv);
        Type case1Type = case1.typecheck(typeEnv);
        Type case2Type = case2.typecheck(typeEnv);

        if (!expType.equals(case1Type) || !expType.equals(case2Type)) {
            throw new TypeMismatchException("Switch statement: case expressions must have the same type as the main expression.");
        }

        stmt1.typecheck(typeEnv);
        stmt2.typecheck(typeEnv);
        defaultStmt.typecheck(typeEnv);

        return typeEnv;
    }

    @Override
    public String toString() {
        return "switch(" + exp + ") (case " + case1 + ": " + stmt1 + ") (case " + case2 + ": " + stmt2 + ") (default: " + defaultStmt + ")";
    }
}
