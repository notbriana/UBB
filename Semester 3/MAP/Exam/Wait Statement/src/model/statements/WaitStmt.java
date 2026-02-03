package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.expressions.ValueExp;
import model.types.Type;
import model.values.IntValue;

public record WaitStmt(int number) implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException, TypeMismatchException, UndefinedVariableException {
        if (number == 0)
            return null;
        else {
            IStmt next = new CompStmt(new PrintStmt(new ValueExp(new IntValue(number))), new WaitStmt(number - 1));
            state.exeStack().push(next);
        }
        return null;
    }


    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv) throws TypeMismatchException, UndefinedVariableException, CollectionException {
        return typeEnv;
    }
}

