package view;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Logger;

public class TextMenu {
    private static final Logger LOGGER = Logger.getLogger(TextMenu.class.getName());
    private final Map<String, Command> commands = new HashMap<>();

    public void addCommand(Command command) {
        commands.put(command.getKey(), command);
    }

    private void printMenu() {
        LOGGER.info("MENU");

        commands.values().forEach(cmd ->
                LOGGER.info("  " + cmd.getKey() + ". " + cmd.getDescription())
        );

        LOGGER.info("Enter your choice: ");
    }

    public void show() {
        try (Scanner scanner = new Scanner(System.in)) {
            boolean running = true;
            while (running && scanner.hasNextLine()) {
                printMenu();

                String input = scanner.nextLine();
                input = (input == null) ? "" : input.trim();

                Command command = commands.get(input);

                if (command == null) {
                    LOGGER.warning("\nInvalid option. Please try again.");
                } else {
                    try {
                        command.execute();
                    } catch (Exception e) {
                        LOGGER.severe("Error executing command: " + e.getMessage());
                    }

                    if ("0".equals(input)) {
                        running = false;
                    }
                }
            }
        } catch (Exception e) {
            LOGGER.severe("Unexpected error: " + e.getMessage());
        }
    }
}