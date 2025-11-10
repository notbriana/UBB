package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IOut;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.values.Value;

public record PrintStmt(Exp exp) implements IStmt {

    @Override
    public PrgState execute(final PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        final IOut<Value> out = state.getOut();
        final ISymbolTable<String, Value> sym = state.getSymTable();
        final Value v = exp.eval(sym);
        out.add(v);
        return state;
    }

    @Override
    public String toString() {
        return "Print(" + exp + ")";
    }
}
