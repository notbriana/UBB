package model.ADTs;

import exceptions.CollectionException;

public interface IExeStack<T> {
    void push(T value);

    T pop() throws CollectionException;

    boolean isEmpty();

    String toString();
}
