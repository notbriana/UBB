package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.values.Value;

public record AssignStmt(String id, Exp exp) implements IStmt {

    @Override
    public PrgState execute(final PrgState state)
            throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        final ISymbolTable<String, Value> sym = state.getSymTable();
        if (!sym.isDefined(id)) {
            throw new UndefinedVariableException(id);
        }
        final Value val = exp.eval(sym);
        final Value current = sym.lookup(id);
        if (!val.getType().equals(current.getType())) {
            throw new TypeMismatchException("variable '" + id + "' and expression have different types");
        }
        sym.update(id, val);
        return state;
    }

    @Override
    public String toString() {
        return id + " = " + exp;
    }
}
