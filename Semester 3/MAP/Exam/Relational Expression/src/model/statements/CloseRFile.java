package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IFileTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.StringType;
import model.types.Type;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public record CloseRFile(Exp exp) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, TypeMismatchException, UndefinedVariableException, DivisionByZeroException {

        Value val = exp.eval(state.symTable(), state.heap());
        if (!(val.getType() instanceof StringType))
            throw new TypeMismatchException("CloseRFile: expression is not a string");

        StringValue strVal = (StringValue) val;
        IFileTable fileTable = state.fileTable();

        if (!fileTable.isDefined(strVal))
            throw new CollectionException("CloseRFile: file not open: " + strVal.val());

        BufferedReader br = fileTable.lookup(strVal);
        try {
            br.close();
        } catch (IOException _) {
            throw new CollectionException("CloseRFile: cannot close file " + strVal.val());
        }

        fileTable.remove(strVal);
        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typexp = exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        } else {
            throw new TypeMismatchException("CloseRFile: expression must be of type string");
        }
    }

    @Override
    public String toString() {
        return "closeRFile(" + exp + ")";
    }
}