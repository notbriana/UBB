package model.ADTs;

import exceptions.CollectionException;

import java.util.Map;

public interface ISymbolTable<K, V> {
    boolean isDefined(K key);

    void put(K key, V value);

    V lookup(K key) throws CollectionException;

    void update(K key, V value) throws CollectionException;

    String toString();

    Map<K, V> getContent();

}
