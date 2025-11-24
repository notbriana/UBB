package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IFileTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.StringType;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public record OpenRFile(Exp exp) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, TypeMismatchException, UndefinedVariableException, DivisionByZeroException {

        Value val = exp.eval(state.symTable(), state.heap());
        if (!(val.getType() instanceof StringType))
            throw new TypeMismatchException("OpenRFile: expression is not a string");

        StringValue strVal = (StringValue) val;
        IFileTable fileTable = state.fileTable();

        if (fileTable.isDefined(strVal))
            throw new CollectionException("OpenRFile: file already open: " + strVal.val());

        try {
            BufferedReader reader = new BufferedReader(new FileReader(strVal.val()));
            fileTable.put(strVal, reader);
        } catch (IOException _) {
            throw new CollectionException("OpenRFile: cannot open file " + strVal.val());
        }

        return null;
    }

    @Override
    public String toString() {
        return "openRFile(" + exp + ")";
    }
}
