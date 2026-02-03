package model.ADTs;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SemaphoreTable implements ISemaphoreTable {

    private final Map<Integer, Pair<Integer, List<Integer>>> table;
    private int freeLocation;

    public SemaphoreTable() {
        this.table = new HashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public synchronized int getFreeLocation() {
        return freeLocation++;
    }

    @Override
    public synchronized void put(int key, Pair<Integer, List<Integer>> value) {
        table.put(key, value);
    }

    @Override
    public synchronized Pair<Integer, List<Integer>> get(int key) {
        return table.get(key);
    }

    @Override
    public synchronized boolean containsKey(int key) {
        return table.containsKey(key);
    }

    @Override
    public synchronized Map<Integer, Pair<Integer, List<Integer>>> getContent() {
        return table;
    }
}
