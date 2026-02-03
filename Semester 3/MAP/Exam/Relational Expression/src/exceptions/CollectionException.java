package exceptions;

public class CollectionException extends Exception {
    public CollectionException(String message) {
        super("Collection error: " + message);
    }
}
