package exceptions;

public class UndefinedVariableException extends Exception {
    public UndefinedVariableException(String name) {
        super("Undefined variable: " + name);
    }
}
