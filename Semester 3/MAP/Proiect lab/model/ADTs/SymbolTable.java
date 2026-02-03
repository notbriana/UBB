package model.ADTs;

import exceptions.CollectionException;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class SymbolTable<K, V> implements ISymbolTable<K, V> {
    private final Map<K, V> map;

    public SymbolTable() {
        this.map = new HashMap<>();
    }

    @Override
    public synchronized boolean isDefined(final K key) {
        return map.containsKey(key);
    }

    @Override
    public synchronized void put(final K key, final V value) {
        Objects.requireNonNull(key, "SymbolTable key cannot be null");
        map.put(key, value);
    }

    @Override
    public synchronized V lookup(final K key) throws CollectionException {
        if (!map.containsKey(key)) {
            throw new CollectionException("Undefined key in symbol table: " + key);
        }
        return map.get(key);
    }

    @Override
    public synchronized void update(final K key, final V value) throws CollectionException {
        if (!map.containsKey(key)) {
            throw new CollectionException("Cannot update undefined key: " + key);
        }
        map.put(key, value);
    }

    @Override
    public synchronized String toString() {
        return map.toString();
    }

    @Override
    public synchronized Map<K, V> getContent() {
        return new HashMap<>(map);
    }

    @Override
    public synchronized ISymbolTable<K, V> clone() {
        SymbolTable<K, V> cloned = new SymbolTable<>();
        for (Map.Entry<K, V> entry : this.map.entrySet()) {
            cloned.put(entry.getKey(), entry.getValue());
        }
        return cloned;
    }
}
