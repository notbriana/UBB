package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public record IfStmt(Exp condition, IStmt thenStmt, IStmt elseStmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {

        Value condValue = condition.eval(state.symTable(), state.heap());

        if (!(condValue.getType() instanceof BoolType)) {
            throw new TypeMismatchException("Condition is not a boolean");
        }

        BoolValue boolValue = (BoolValue) condValue;
        if (boolValue.value()) {
            state.exeStack().push(thenStmt);
        } else {
            state.exeStack().push(elseStmt);
        }

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typexp = condition.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            thenStmt.typecheck(typeEnv.clone());
            elseStmt.typecheck(typeEnv.clone());
            return typeEnv;
        } else {
            throw new TypeMismatchException("The condition of IF has not the type bool");
        }
    }

    @Override
    public String toString() {
        return "if (" + condition.toString() + ") then " + thenStmt.toString() + " else " + elseStmt.toString();
    }
}