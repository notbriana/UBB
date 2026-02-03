package model.ADTs;

import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface IBarrierTable {

    int addBarrier(int limit);

    Pair<Integer, List<Integer>> lookup(int index);

    void update(int index, Pair<Integer, List<Integer>> value);

    boolean containsKey(int index);

    Map<Integer, Pair<Integer, List<Integer>>> getContent();
}
