package exceptions;

public class DivisionByZeroException extends Exception {
    public DivisionByZeroException(String divisionByZero) {
        super("Division by zero error!");
    }
}