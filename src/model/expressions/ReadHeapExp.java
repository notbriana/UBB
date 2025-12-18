package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public record ReadHeapExp(Exp expression) implements Exp {

    @Override
    public Value eval(ISymbolTable<String, Value> symTable, IHeap<Integer, Value> heap)
            throws DivisionByZeroException, TypeMismatchException, UndefinedVariableException, CollectionException {

        Value value = expression.eval(symTable, heap);

        if (!(value instanceof RefValue)) {
            throw new TypeMismatchException("Expression must evaluate to a RefValue");
        }

        RefValue refValue = (RefValue) value;
        int address = refValue.getAddr();

        if (!heap.isDefined(address)) {
            throw new CollectionException("Address " + address + " is not defined in the heap");
        }

        return heap.get(address);
    }

    @Override
    public Type typecheck(ISymbolTable<String, Type> typeEnv)
            throws TypeMismatchException, UndefinedVariableException, CollectionException {
        Type typ = expression.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft = (RefType) typ;
            return reft.inner();
        } else {
            throw new TypeMismatchException("The rH argument is not a Ref Type");
        }
    }

    @Override
    public String toString() {
        return "rH(" + expression.toString() + ")";
    }
}