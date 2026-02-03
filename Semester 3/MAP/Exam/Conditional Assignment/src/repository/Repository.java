package repository;

import exceptions.CollectionException;
import model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<PrgState> programs;
    private final String logFilePath;

    public Repository(PrgState program, String logFilePath) {
        this.programs = new ArrayList<>();
        this.programs.add(program);
        this.logFilePath = logFilePath;
    }

    @Override
    public List<PrgState> getPrgList() {
        return programs;
    }

    @Override
    public void setPrgList(List<PrgState> prgList) {
        this.programs = prgList;
    }

    @Override
    public void logPrgStateExec(PrgState state) throws CollectionException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {

            logFile.println("ID: " + state.getId());

            logFile.println("ExeStack:");
            var stack = state.exeStack();
            logFile.println("   " + stack.toString());

            logFile.println("SymTable:");
            var symTable = state.symTable().getContent();
            for (var entry : symTable.entrySet()) {
                logFile.println("   " + entry.getKey() + " --> " + entry.getValue());
            }

            logFile.println("Out:");
            var outList = state.out().getList();
            for (var value : outList) {
                logFile.println("   " + value);
            }

            logFile.println("Heap:");
            var heap = state.heap().getContent();
            for (var entry : heap.entrySet()) {
                logFile.println("   " + entry.getKey() + " --> " + entry.getValue());
            }


            if (state.fileTable() != null) {
                logFile.println("FileTable:");
                var fileTable = state.fileTable().getContent();
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