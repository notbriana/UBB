package model.ADTs;

import java.util.ArrayList;
import java.util.List;

public class Out<T> implements IOut<T> {
    private final List<T> list;

    public Out() {
        list = new ArrayList<>();
    }

    @Override
    public synchronized void add(T v) {
        list.add(v);
    }

    @Override
    public synchronized List<T> getList() {
        return new ArrayList<>(list);
    }

    @Override
    public synchronized String toString() {
        return list.toString();
    }
}