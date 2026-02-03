
package model.ADTs;

import model.utils.Triplet;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class SemaphoreTable implements ISemaphoreTable {

    private final Map<Integer, Triplet<Integer, List<Integer>, Integer>> semaphoreTable;
    private int freeAddress;

    public SemaphoreTable() {
        semaphoreTable = new ConcurrentHashMap<>();
        freeAddress = 1;
    }


    @Override
    public int getFreeAddress() {
        return freeAddress++;
    }

    @Override
    public void put(int key, Triplet<Integer, List<Integer>, Integer> value) {
        semaphoreTable.put(key, value);
    }

    @Override
    public Triplet<Integer, List<Integer>, Integer> get(int key) {
        return semaphoreTable.get(key);
    }

    @Override
    public boolean containsKey(int key) {
        return semaphoreTable.containsKey(key);
    }

    @Override
    public void update(int key, Triplet<Integer, List<Integer>, Integer> value) {
        semaphoreTable.put(key, value);
    }

    @Override
    public Map<Integer, Triplet<Integer, List<Integer>, Integer>> getContent() {
        return semaphoreTable;
    }

    @Override
    public String toString() {
        return semaphoreTable.toString();
    }


}

