package model.statements;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import javafx.util.Pair;
import model.ADTs.ISymbolTable;
import model.ADTs.SymbolTable;
import model.PrgState;
import model.expressions.Exp;
import model.types.Type;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public class CallStmt implements IStmt {
    private final String procedureName;
    private final List<Exp> arguments;

    public CallStmt(String procedureName, List<Exp> arguments) {
        this.procedureName = procedureName;
        this.arguments = arguments;
    }

    @Override
    public PrgState execute(PrgState state) throws CollectionException, DivisionByZeroException,
            TypeMismatchException, UndefinedVariableException {
        if (!state.procTable().isDefined(procedureName)) {
            throw new UndefinedVariableException("Procedure " + procedureName + " is not defined");
        }

        Pair<List<String>, IStmt> procDef = state.procTable().lookupProcedure(procedureName);
        List<String> formalParams = procDef.getKey();
        IStmt body = procDef.getValue();

        if (arguments.size() != formalParams.size()) {
            throw new CollectionException("Procedure " + procedureName + " expects " +
                    formalParams.size() + " arguments but got " + arguments.size());
        }

        List<Value> evaluatedArgs = new ArrayList<>();
        for (Exp arg : arguments) {
            evaluatedArgs.add(arg.eval(state.symTable(), state.heap()));
        }

        ISymbolTable<String, Value> newSymTable = new SymbolTable<>();
        for (int i = 0; i < formalParams.size(); i++) {
            newSymTable.put(formalParams.get(i), evaluatedArgs.get(i));
        }

        state.pushSymTable(newSymTable);

        state.exeStack().push(new ReturnStmt());

        state.exeStack().push(body);

        return null;
    }

    @Override
    public ISymbolTable<String, Type> typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {

        for (Exp arg : arguments) {
            arg.typecheck(typeEnv);
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("call ").append(procedureName).append("(");
        for (int i = 0; i < arguments.size(); i++) {
            sb.append(arguments.get(i));
            if (i < arguments.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString();
    }
}

