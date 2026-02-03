package view;

import java.util.logging.Logger;

public class ExitCommand extends Command {
    private static final Logger LOGGER = Logger.getLogger(ExitCommand.class.getName());

    public ExitCommand(String key, String description) {
        super(key, description);
    }

    @Override
    public void execute() {
        LOGGER.info("\nGoodbye! Exiting interpreter...\n");
        System.exit(0);
    }
}