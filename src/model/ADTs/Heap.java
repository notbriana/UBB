package model.ADTs;

import exceptions.CollectionException;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class Heap<K, V> implements IHeap<Integer, V> {
    private Map<Integer, V> heap;
    private int nextFreeLocation;

    public Heap() {
        heap = new HashMap<>();
        nextFreeLocation = 1;
    }

    @Override
    public int allocate(V value) {
        int address = nextFreeLocation;
        heap.put(address, value);
        nextFreeLocation++;
        return address;
    }

    @Override
    public V get(Integer address) throws CollectionException {
        if (!heap.containsKey(address)) {
            throw new CollectionException("Address " + address + " is not defined in the heap");
        }
        return heap.get(address);
    }

    @Override
    public void update(Integer address, V value) throws CollectionException {
        if (!heap.containsKey(address)) {
            throw new CollectionException("Address " + address + " is not defined in the heap");
        }
        heap.put(address, value);
    }

    @Override
    public boolean isDefined(Integer address) {
        return heap.containsKey(address);
    }

    @Override
    public Map<Integer, V> getContent() {
        return heap;
    }

    @Override
    public void setContent(Map<Integer, V> newContent) {
        heap = newContent;
    }

    @Override
    public String toString() {
        if (heap.isEmpty()) {
            return "";
        }

        return heap.entrySet().stream()
                .sorted(Map.Entry.comparingByKey())
                .map(entry -> "   " + entry.getKey() + " --> " + entry.getValue())
                .collect(Collectors.joining("\n", "", "\n"));
    }
}