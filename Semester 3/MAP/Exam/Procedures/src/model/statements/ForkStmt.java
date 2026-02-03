package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.*;
import model.PrgState;
import model.types.Type;
import model.values.Value;

import java.util.Stack;

public record ForkStmt(IStmt stmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException,
            TypeMismatchException, UndefinedVariableException {

        try {
            IExeStack<IStmt> newExeStack = state.exeStack().getClass()
                    .getDeclaredConstructor()
                    .newInstance();

            Stack<ISymbolTable<String, Value>> clonedSymTableStack = new Stack<>();
            for (ISymbolTable<String, Value> symTable : state.getSymTableStack()) {
                clonedSymTableStack.push(symTable.clone());
            }

            ISymbolTable<String, model.values.Value> newSymTable = state.symTable().clone();

            IHeap<Integer, model.values.Value> sharedHeap = state.heap();
            IFileTable sharedFileTable = state.fileTable();
            IOut<model.values.Value> sharedOut = state.out();
            IProcTable sharedProcTable = state.procTable();

            PrgState newState;
            newState = new PrgState(
                    newExeStack,
                    clonedSymTableStack,
                    sharedOut,
                    sharedFileTable,
                    stmt,
                    sharedHeap,
                    sharedProcTable
            );

            return newState;

        } catch (Exception e) {
            throw new CollectionException("Error creating fork: " + e.getMessage());
        }
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        stmt.typecheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + stmt.toString() + ")";
    }
}


