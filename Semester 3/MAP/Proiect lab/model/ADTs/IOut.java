package model.ADTs;

import java.util.List;

public interface IOut<T> {
    void add(T v);

    List<T> getList();

    String toString();
}
