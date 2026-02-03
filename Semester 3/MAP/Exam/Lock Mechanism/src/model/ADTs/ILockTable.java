package model.ADTs;

import exceptions.CollectionException;

import java.util.Map;

public interface ILockTable {
    int allocate(int value);

    int get(int key) throws CollectionException;

    void update(int key, int value) throws CollectionException;

    boolean isDefined(int key);

    Map<Integer, Integer> getContent();

    void setContent(Map<Integer, Integer> newContent);
}


