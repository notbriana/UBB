package model.values;

import model.types.BoolType;
import model.types.Type;

public record BoolValue(boolean value) implements Value {

    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public boolean equals(Object another) {
        if (this == another)
            return true;
        if (!(another instanceof BoolValue(boolean value1)))
            return false;
        return value == value1;
    }

    @Override
    public String toString() {
        return Boolean.toString(value);
    }
}
