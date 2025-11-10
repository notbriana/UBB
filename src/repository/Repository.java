package repository;

import exceptions.CollectionException;
import model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public record Repository(PrgState program, String logFilePath) implements IRepository {

    @Override
    public PrgState getCrtPrg() {
        return program;
    }

    @Override
    public void logPrgState(final PrgState state) throws CollectionException {
        logPrgStateExec();
    }

    @Override
    public void logPrgStateExec() throws CollectionException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {

            logFile.println("ExeStack:");
            var stack = program.getExeStack();
            logFile.println("   " + stack.toString());

            logFile.println("SymTable:");
            var symTable = program.getSymTable().getContent();
            for (var entry : symTable.entrySet()) {
                logFile.println("   " + entry.getKey() + " --> " + entry.getValue());
            }

            logFile.println("Out:");
            var outList = program.getOut().getList();
            for (var value : outList) {
                logFile.println("   " + value);
            }

            if (program.getFileTable() != null) {
                logFile.println("FileTable:");
                var fileTable = program.getFileTable().getContent();
                for (var entry : fileTable.entrySet()) {
                    logFile.println("   " + entry.getKey());
                }
            }

            logFile.println("------------------------------------------------------");

        } catch (IOException e) {
            throw new CollectionException("Error writing to log file: " + e.getMessage());
        }
    }
}
