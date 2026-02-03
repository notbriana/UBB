package model.ADTs;

import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface ISemaphoreTable {
    int getFreeLocation();

    void put(int key, Pair<Integer, List<Integer>> value);

    Pair<Integer, List<Integer>> get(int key);

    boolean containsKey(int key);

    Map<Integer, Pair<Integer, List<Integer>>> getContent();

}
