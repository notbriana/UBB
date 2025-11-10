package view;

import controller.Controller;
import exceptions.CollectionException;
import exceptions.DivisionByZeroException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;

import java.util.logging.Level;
import java.util.logging.Logger;

public class RunExample extends Command {
    private static final Logger LOGGER = Logger.getLogger(RunExample.class.getName());
    private final Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            controller.allStep();
            LOGGER.info("Program executed successfully.");
        } catch (CollectionException | DivisionByZeroException | TypeMismatchException | UndefinedVariableException e) {
            LOGGER.log(Level.SEVERE, "Execution error: {0}", e.getMessage());
        }
    }
}
