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
    public boolean isDefined(StringValue key) {
        return table.containsKey(key);
    }

    @Override
    public void put(StringValue key, BufferedReader value) {
        table.put(key, value);
    }

    @Override
    public BufferedReader lookup(StringValue key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("FileTable: Undefined key " + key);
        return table.get(key);
    }

    @Override
    public void remove(StringValue key) throws CollectionException {
        if (!table.containsKey(key))
            throw new CollectionException("FileTable: Cannot remove undefined key " + key);
        table.remove(key);
    }

    @Override
    public Map<StringValue, BufferedReader> getContent() {
        return table;
    }

    @Override
    public String toString() {
        return table.keySet().toString();
    }
}
