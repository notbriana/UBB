package exceptions;

public class TypeMismatchException extends Exception {
    public TypeMismatchException(String msg) {
        super("Type mismatch: " + msg);
    }
}
