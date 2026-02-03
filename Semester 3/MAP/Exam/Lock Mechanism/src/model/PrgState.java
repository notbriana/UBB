package model;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.*;
import model.statements.IStmt;
import model.values.Value;

public class PrgState {
    private static int nextId = 1;

    private final IExeStack<IStmt> exeStack;
    private final ISymbolTable<String, Value> symTable;
    private final IOut<Value> out;
    private final IFileTable fileTable;
    private final IStmt originalProgram;
    private final IHeap<Integer, Value> heap;
    private final int id;
    private ILockTable lockTable;


    public PrgState(IExeStack<IStmt> exeStack,
                    ISymbolTable<String, Value> symTable,
                    IOut<Value> out,
                    IFileTable fileTable,
                    IStmt originalProgram,
                    IHeap<Integer, Value> heap,
                    ILockTable lockTable) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = originalProgram;
        this.heap = heap;
        this.lockTable = lockTable;
        this.id = getNewId();
        this.exeStack.push(originalProgram);
    }

    private static synchronized int getNewId() {
        return nextId++;
    }

    public int getId() {
        return id;
    }

    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public PrgState oneStep() throws CollectionException, DivisionByZeroException,
            TypeMismatchException, UndefinedVariableException {
        if (exeStack.isEmpty()) {
            throw new CollectionException("PrgState stack is empty");
        }
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

    public IExeStack<IStmt> exeStack() {
        return exeStack;
    }


    public ISymbolTable<String, Value> symTable() {
        return symTable;
    }

    public ILockTable lockTable() {
        return lockTable;
    }

    public IOut<Value> out() {
        return out;
    }

    public IFileTable fileTable() {
        return fileTable;
    }

    public IStmt originalProgram() {
        return originalProgram;
    }

    public IHeap<Integer, Value> heap() {
        return heap;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("ID: ").append(id).append("\n");

        sb.append("ExeStack:\n");
        sb.append("   ").append(exeStack.toString()).append("\n");

        sb.append("SymTable:\n");
        sb.append(symTable.toString());

        sb.append("Out:\n");
        sb.append(out.toString());

        sb.append("Heap:\n");
        sb.append(heap.toString());

        sb.append("FileTable:\n");
        sb.append(fileTable.toString());

        sb.append("LockTable:\n");
        sb.append(lockTable.toString());

        sb.append("------------------------------------------------------");

        return sb.toString();
    }
}


