package model;

import model.ADTs.*;
import model.statements.IStmt;
import model.values.Value;

public record PrgState(IExeStack<IStmt> exeStack, ISymbolTable<String, Value> symTable, IOut<Value> out,
                       IFileTable fileTable, IStmt originalProgram, IHeap<Integer, Value> heap) {
    public PrgState(final IExeStack<IStmt> exeStack,
                    final ISymbolTable<String, Value> symTable,
                    final IOut<Value> out,
                    final IFileTable fileTable,
                    final IStmt originalProgram, IHeap<Integer, Value> heap) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.originalProgram = originalProgram;
        this.heap = heap;
        this.exeStack.push(originalProgram);
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

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

        sb.append("------------------------------------------------------");

        return sb.toString();
    }
}