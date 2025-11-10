package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IFileTable;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.IntType;
import model.types.StringType;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public record ReadFile(Exp exp, String varName) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, TypeMismatchException, UndefinedVariableException, DivisionByZeroException {

        ISymbolTable<String, Value> symTable = state.getSymTable();
        IFileTable fileTable = state.getFileTable();

        if (!symTable.isDefined(varName))
            throw new UndefinedVariableException("ReadFile: variable " + varName + " not defined");

        Value varVal = symTable.lookup(varName);
        if (!(varVal.getType() instanceof IntType))
            throw new TypeMismatchException("ReadFile: variable must be int");

        Value expVal = exp.eval(symTable);
        if (!(expVal.getType() instanceof StringType))
            throw new TypeMismatchException("ReadFile: expression must evaluate to string");

        StringValue strVal = (StringValue) expVal;

        if (!fileTable.isDefined(strVal))
            throw new CollectionException("ReadFile: file not open: " + strVal.val());

        BufferedReader br = fileTable.lookup(strVal);
        try {
            String line = br.readLine();
            int value = (line == null || line.isEmpty()) ? 0 : Integer.parseInt(line.trim());
            symTable.put(varName, new IntValue(value));
        } catch (IOException _) {
            throw new CollectionException("ReadFile: error reading from " + strVal.val());
        } catch (NumberFormatException _) {
            throw new CollectionException("ReadFile: invalid number format in file " + strVal.val());
        }

        return null;
    }

    @Override
    public String toString() {
        return "readFile(" + exp + ", " + varName + ")";
    }
}
