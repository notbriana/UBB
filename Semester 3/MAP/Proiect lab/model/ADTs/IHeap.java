package model.ADTs;

import exceptions.CollectionException;

import java.util.Map;

public interface IHeap<K, V> {
    int allocate(V value);

    V get(K address) throws CollectionException;

    void update(K address, V value) throws CollectionException;

    boolean isDefined(K address);

    Map<K, V> getContent();

    void setContent(Map<K, V> newContent);

    String toString();
}