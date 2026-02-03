package model.ADTs;

import exceptions.CollectionException;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class LatchTable implements ILatchTable {
    private final Map<Integer, Integer> table;
    private int nextFreeLocation;

    public LatchTable() {
        table = new HashMap<>();
        nextFreeLocation = 1;
    }

    @Override
    public synchronized int allocate(int value) {
        int id = nextFreeLocation;
        table.put(id, value);
        nextFreeLocation++;
        return id;
    }

    @Override
    public synchronized int get(int key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("LatchTable: index " + key + " not defined");
        return table.get(key);
    }

    @Override
    public synchronized void update(int key, int value) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("LatchTable: index " + key + " not defined");
        table.put(key, value);
    }

    @Override
    public synchronized boolean isDefined(int key) {
        return table.containsKey(key);
    }

    @Override
    public synchronized Map<Integer, Integer> getContent() {
        return new HashMap<>(table);
    }

    @Override
    public synchronized void setContent(Map<Integer, Integer> newContent) {
        table.clear();
        table.putAll(newContent);
        nextFreeLocation = table.keySet().stream().mapToInt(k -> k).max().orElse(0) + 1;
    }
}
