package view;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class TextMenu {
    private static final Logger LOGGER = Logger.getLogger(TextMenu.class.getName());
    private final Map<String, Command> commands = new HashMap<>();

    public void addCommand(Command command) {
        commands.put(command.getKey(), command);
    }

    private void printMenu() {
        LOGGER.info("\n=== Toy Language Interpreter Menu ===");
        commands.values().forEach(cmd ->
                LOGGER.log(Level.INFO, "{0} : {1}", new Object[]{cmd.getKey(), cmd.getDescription()})
        );
    }

    public void show() {
        try (Scanner scanner = new Scanner(System.in)) {
            boolean running = true;
            while (running && scanner.hasNextLine()) {
                printMenu();
                LOGGER.info("Select an option: ");

                String input = readUserInput(scanner);
                running = processUserChoice(input);
            }
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "Unexpected error in TextMenu: {0}", e.getMessage());
        }
    }


    private String readUserInput(Scanner scanner) {
        String input = scanner.nextLine();
        return input == null ? "" : input.trim();
    }

    private boolean processUserChoice(String input) {
        Optional<Command> commandOpt = Optional.ofNullable(commands.get(input));

        if (commandOpt.isEmpty()) {
            LOGGER.warning("Invalid option selected.");
            return true;
        }

        executeCommand(commandOpt.get());
        return !"0".equals(input);
    }

    private void executeCommand(Command command) {
        try {
            command.execute();
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "Error executing command: {0}", e.getMessage());
        }
    }
}
