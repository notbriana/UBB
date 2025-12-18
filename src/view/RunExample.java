package view;

import controller.Controller;

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
            LOGGER.info("EXECUTING: " + getDescription());

            controller.allStep();

            LOGGER.info("Execution completed successfully!");

        } catch (InterruptedException e) {
            LOGGER.log(Level.SEVERE, "\nExecution interrupted: {0}", e.getMessage());
            Thread.currentThread().interrupt();
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "\nExecution error: {0}", e.getMessage());
            e.printStackTrace();
        }
    }
}