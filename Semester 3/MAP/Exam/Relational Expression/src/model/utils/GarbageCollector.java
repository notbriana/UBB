package model.utils;

import model.values.RefValue;
import model.values.Value;

import java.util.*;
import java.util.stream.Collectors;

public class GarbageCollector {

    public static List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddr();
                })
                .collect(Collectors.toList());
    }


    private static Set<Integer> getAllReachableAddresses(List<Integer> symTableAddr, Map<Integer, Value> heap) {
        Set<Integer> reachable = new HashSet<>(symTableAddr);
        boolean changed = true;

        while (changed) {
            changed = false;
            List<Integer> newAddresses = new ArrayList<>();

            for (Integer addr : reachable) {
                if (heap.containsKey(addr)) {
                    Value value = heap.get(addr);
                    if (value instanceof RefValue) {
                        int refAddr = ((RefValue) value).getAddr();
                        if (!reachable.contains(refAddr)) {
                            newAddresses.add(refAddr);
                            changed = true;
                        }
                    }
                }
            }

            reachable.addAll(newAddresses);
        }

        return reachable;
    }


    public static Map<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
        Set<Integer> reachableAddresses = getAllReachableAddresses(symTableAddr, heap);

        return heap.entrySet().stream()
                .filter(e -> reachableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

}