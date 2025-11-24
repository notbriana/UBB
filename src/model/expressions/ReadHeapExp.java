package model.expressions;

import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.IHeap;
import model.ADTs.ISymbolTable;
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
    public String toString() {
        return "rH(" + expression.toString() + ")";
    }
}