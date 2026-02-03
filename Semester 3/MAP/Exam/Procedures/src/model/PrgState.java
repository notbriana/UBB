package model;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.*;
import model.statements.IStmt;
import model.values.Value;

import java.util.Stack;

public class PrgState {
    private static int nextId = 1;

    private final IExeStack<IStmt> exeStack;
    private Stack<ISymbolTable<String, Value>> symTableStack;
    private final IOut<Value> out;
    private final IFileTable fileTable;
    private final IStmt originalProgram;
    private final IHeap<Integer, Value> heap;
    private final IProcTable procTable;
    private final int id;

    public PrgState(IExeStack<IStmt> exeStack,
                    ISymbolTable<String, Value> symTable,
                    IOut<Value> out,
                    IFileTable fileTable,
                    IStmt originalProgram,
                    IHeap<Integer, Value> heap,
                    IProcTable procTable) {
        this.exeStack = exeStack;
        this.symTableStack = new Stack<>();
        this.symTableStack.push(symTable);
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = originalProgram;
        this.heap = heap;
        this.procTable = procTable;

        this.id = getNewId();
        if (originalProgram != null) {
            this.exeStack.push(originalProgram);
        }
    }

    public PrgState(IExeStack<IStmt> exeStack,
                    Stack<ISymbolTable<String, Value>> symTableStack,
                    IOut<Value> out,
                    IFileTable fileTable,
                    IStmt originalProgram,
                    IHeap<Integer, Value> heap,
                    IProcTable procTable) {
        this.exeStack = exeStack;
        this.symTableStack = symTableStack;
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = originalProgram;
        this.heap = heap;
        this.procTable = procTable;

        this.id = getNewId();
        if (originalProgram != null) {
            this.exeStack.push(originalProgram);
        }
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

    public void pushSymTable(ISymbolTable<String, Value> newSymTable) {
        symTableStack.push(newSymTable);
    }

    public void popSymTable() {
        if (symTableStack.size() > 1) {
            symTableStack.pop();
        }
    }

    public void setSymTableStack(Stack<ISymbolTable<String, Value>> stack) {
        this.symTableStack = stack;
    }

    public IExeStack<IStmt> exeStack() {
        return exeStack;
    }

    public IProcTable procTable() {
        return procTable;
    }

    public ISymbolTable<String, Value> symTable() {
        return symTableStack.peek();
    }

    public Stack<ISymbolTable<String, Value>> getSymTableStack() {
        return symTableStack;
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

        sb.append("SymTableStack (").append(symTableStack.size()).append(" levels):\n");
        for (int i = symTableStack.size() - 1; i >= 0; i--) {
            sb.append("  Level ").append(i).append(": ");
            sb.append(symTableStack.get(i).toString());
        }

        sb.append("Out:\n");
        sb.append(out.toString());

        sb.append("Heap:\n");
        sb.append(heap.toString());

        sb.append("FileTable:\n");
        sb.append(fileTable.toString());

        sb.append("ProcTable:\n");
        sb.append(procTable.toString());

        sb.append("------------------------------------------------------");

        return sb.toString();
    }
}

