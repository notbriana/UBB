package model.ADTs;

import exceptions.CollectionException;
import model.values.StringValue;

import java.io.BufferedReader;
import java.util.Map;

public interface IFileTable {
    boolean isDefined(StringValue key);

    void put(StringValue key, BufferedReader value);

    BufferedReader lookup(StringValue key) throws CollectionException;

    void remove(StringValue key) throws CollectionException;

    Map<StringValue, BufferedReader> getContent();
}
