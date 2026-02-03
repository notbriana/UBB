package model.ADTs;

import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BarrierTable implements IBarrierTable {

    private final Map<Integer, Pair<Integer, List<Integer>>> table;
    private int freeLocation = 1;

    public BarrierTable() {
        table = new HashMap<>();
    }


    @Override
    public synchronized int addBarrier(int limit) {
        int index = freeLocation++;
        table.put(index, new Pair<>(limit, new ArrayList<>()));
        return index;
    }

    @Override
    public synchronized Pair<Integer, List<Integer>> lookup(int index) {
        if (!table.containsKey(index))
            throw new RuntimeException("Barrier not found!");
        return table.get(index);
    }

    @Override
    public synchronized void update(int index, Pair<Integer, List<Integer>> value) {
        if (!table.containsKey(index))
            throw new RuntimeException("Barrier not found!");
        table.put(index, value);
    }

    @Override
    public synchronized boolean containsKey(int index) {
        return table.containsKey(index);
    }

    @Override
    public synchronized Map<Integer, Pair<Integer, List<Integer>>> getContent() {
        return new HashMap<>(table);
    }
}


