package model.values;

import model.types.IntType;
import model.types.Type;

public record IntValue(int value) implements Value {

    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public boolean equals(Object another) {
        if (this == another)
            return true;
        if (!(another instanceof IntValue(int value1)))
            return false;
        return value == value1;
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }
}
