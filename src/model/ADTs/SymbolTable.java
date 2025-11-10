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
    public boolean isDefined(final K key) {
        return map.containsKey(key);
    }

    @Override
    public void put(final K key, final V value) {
        Objects.requireNonNull(key, "SymbolTable key cannot be null");
        map.put(key, value);
    }

    @Override
    public V lookup(final K key) throws CollectionException {
        if (!map.containsKey(key)) {
            throw new CollectionException("Undefined key in symbol table: " + key);
        }
        return map.get(key);
    }

    @Override
    public void update(final K key, final V value) throws CollectionException {
        if (!map.containsKey(key)) {
            throw new CollectionException("Cannot update undefined key: " + key);
        }
        map.put(key, value);
    }

    @Override
    public String toString() {
        return map.toString();
    }

    @Override
    public Map<K, V> getContent() {
        return map;
    }

}
