package model;

import model.ADTs.IExeStack;
import model.ADTs.IFileTable;
import model.ADTs.IOut;
import model.ADTs.ISymbolTable;
import model.statements.IStmt;
import model.values.Value;

public class PrgState {
    private final IExeStack<IStmt> exeStack;
    private final ISymbolTable<String, Value> symTable;
    private final IOut<Value> out;
    private final IFileTable fileTable;
    private final IStmt originalProgram;

    public PrgState(final IExeStack<IStmt> exeStack,
                    final ISymbolTable<String, Value> symTable,
                    final IOut<Value> out,
                    final IFileTable fileTable,
                    final IStmt program) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = program;
        this.exeStack.push(program);
    }

    public IExeStack<IStmt> getExeStack() {
        return exeStack;
    }

    public ISymbolTable<String, Value> getSymTable() {
        return symTable;
    }

    public IOut<Value> getOut() {
        return out;
    }

    public IFileTable getFileTable() {
        return fileTable;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    @Override
    public String toString() {
        return "=== Program State ===\n" +
                "ExeStack: " + exeStack + "\n" +
                "SymTable: " + symTable + "\n" +
                "Out: " + out + "\n" +
                "FileTable: " + fileTable + "\n";
    }
}
