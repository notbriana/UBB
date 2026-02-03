package model.types;

import model.values.StringValue;
import model.values.Value;

public class StringType implements Type {

    @Override
    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    @Override
    public int hashCode() {
        return StringType.class.hashCode();
    }

    @Override
    public Value defaultValue() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "string";
    }
}
