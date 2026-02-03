package model.ADTs;

import model.utils.Triplet;

import java.util.List;
import java.util.Map;

public interface ISemaphoreTable {
    int getFreeAddress();

    void put(int key, Triplet<Integer, List<Integer>, Integer> value);

    Triplet<Integer, List<Integer>, Integer> get(int key);

    boolean containsKey(int key);

    void update(int key, Triplet<Integer, List<Integer>, Integer> value);

    Map<Integer, Triplet<Integer, List<Integer>, Integer>> getContent();

    public String toString();
}




