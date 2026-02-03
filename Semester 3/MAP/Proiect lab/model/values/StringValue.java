package model.values;

import model.types.StringType;
import model.types.Type;

public record StringValue(String val) implements Value {

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public boolean equals(Object another) {
        if (this == another)
            return true;
        if (!(another instanceof StringValue(String val1)))
            return false;
        return val.equals(val1);
    }

    @Override
    public String toString() {
        return "\"" + val + "\"";
    }
}
