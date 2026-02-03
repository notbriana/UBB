package model.ADTs;

import exceptions.CollectionException;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Objects;


public class ExeStack<T> implements IExeStack<T> {
    private final Deque<T> stack;

    public ExeStack() {
        this.stack = new ArrayDeque<>();
    }

    @Override
    public void push(final T value) {
        Objects.requireNonNull(value, "Cannot push null onto exe stack");
        stack.push(value);
    }

    @Override
    public T pop() throws CollectionException {
        if (stack.isEmpty()) {
            throw new CollectionException("Cannot pop from an empty execution stack");
        }
        return stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public String toString() {
        return stack.toString();
    }

    public ArrayList<T> getStackReversed() {
        ArrayList<T> reversed = new ArrayList<>();
        stack.descendingIterator().forEachRemaining(reversed::add);
        return reversed;
    }


}
