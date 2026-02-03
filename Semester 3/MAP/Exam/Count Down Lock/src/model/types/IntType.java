package model.types;

import model.values.IntValue;
import model.values.Value;

public class IntType implements Type {

    @Override
    public boolean equals(final Object other) {
        return other instanceof IntType;
    }

    @Override
    public int hashCode() {
        return IntType.class.hashCode();
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }
}
