package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.*;
import model.PrgState;

public record ForkStmt(IStmt stmt) implements IStmt {

    @Override
    public PrgState execute(PrgState state)
            throws CollectionException, DivisionByZeroException,
            TypeMismatchException, UndefinedVariableException {

        try {
            IExeStack<IStmt> newExeStack = state.exeStack().getClass()
                    .getDeclaredConstructor()
                    .newInstance();

            ISymbolTable<String, model.values.Value> newSymTable =
                    state.symTable().clone();

            IHeap<Integer, model.values.Value> sharedHeap = state.heap();
            IFileTable sharedFileTable = state.fileTable();
            IOut<model.values.Value> sharedOut = state.out();

            PrgState newState;
            newState = new PrgState(
                    newExeStack,
                    newSymTable,
                    sharedOut,
                    sharedFileTable,
                    stmt,
                    sharedHeap
            );

            return newState;

        } catch (Exception e) {
            throw new CollectionException("Error creating fork: " + e.getMessage());
        }
    }

    @Override
    public String toString() {
        return "fork(" + stmt.toString() + ")";
    }
}