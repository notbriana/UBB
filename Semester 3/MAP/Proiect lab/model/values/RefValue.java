package model.values;

import model.types.RefType;
import model.types.Type;

public record RefValue(int address, Type locationType) implements Value {

    public int getAddr() {
        return address;
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public boolean equals(Object another) {
        if (another instanceof RefValue) {
            RefValue ref = (RefValue) another;
            return address == ref.address && locationType.equals(ref.locationType);
        }
        return false;
    }

    @Override
    public String toString() {
        return "(" + address + ", " + locationType.toString() + ")";
    }
}