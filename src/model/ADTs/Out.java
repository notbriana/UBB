package model.ADTs;

import java.util.ArrayList;
import java.util.List;

public class Out<T> implements IOut<T> {
    private final List<T> list;

    public Out() {
        list = new ArrayList<>();
    }

    @Override
    public void add(T v) {
        list.add(v);
    }

    @Override
    public List<T> getList() {
        return list;
    }

    @Override
    public String toString() {
        return getList().toString();
    }
}
