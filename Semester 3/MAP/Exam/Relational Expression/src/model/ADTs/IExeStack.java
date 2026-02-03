package model.ADTs;

import exceptions.CollectionException;

import java.util.ArrayList;

public interface IExeStack<T> {
    void push(T value);

    T pop() throws CollectionException;

    boolean isEmpty();

    String toString();

    ArrayList<T> getStackReversed();

}
