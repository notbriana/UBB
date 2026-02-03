package model.ADTs;

import exceptions.CollectionException;

import java.util.HashMap;
import java.util.Map;

public class LockTable implements ILockTable {
    private Map<Integer, Integer> table;
    private int nextFree;

    public LockTable() {
        table = new HashMap<>();
        nextFree = 1;
    }

    @Override
    public synchronized int allocate(int value) {
        int addr = nextFree;
        table.put(addr, value);
        nextFree++;
        return addr;
    }

    @Override
    public synchronized int get(int key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("LockTable: invalid key " + key);
        return table.get(key);
    }

    @Override
    public synchronized void update(int key, int value) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("LockTable: invalid key " + key);
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
        table = new HashMap<>(newContent);
    }
}


