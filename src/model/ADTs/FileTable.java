package model.ADTs;

import exceptions.CollectionException;
import model.values.StringValue;

import java.io.BufferedReader;
import java.util.HashMap;
import java.util.Map;

public class FileTable implements IFileTable {
    private final Map<StringValue, BufferedReader> table;

    public FileTable() {
        this.table = new HashMap<>();
    }

    @Override
    public synchronized boolean isDefined(StringValue key) {
        return table.containsKey(key);
    }

    @Override
    public synchronized void put(StringValue key, BufferedReader value) {
        table.put(key, value);
    }

    @Override
    public synchronized BufferedReader lookup(StringValue key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("FileTable: Undefined key " + key);
        return table.get(key);
    }

    @Override
    public synchronized void remove(StringValue key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("FileTable: Cannot remove undefined key " + key);
        table.remove(key);
    }

    @Override
    public synchronized Map<StringValue, BufferedReader> getContent() {
        return new HashMap<>(table);
    }

    @Override
    public synchronized String toString() {
        return table.keySet().toString();
    }
}