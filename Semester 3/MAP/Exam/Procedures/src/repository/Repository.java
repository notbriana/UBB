package repository;

import exceptions.CollectionException;
import javafx.util.Pair;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.statements.IStmt;
import model.values.Value;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Stack;

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

            logFile.println("SymTableStack:");
            Stack<ISymbolTable<String, Value>> symTableStack = state.getSymTableStack();
            logFile.println("   Stack Size: " + symTableStack.size());
            for (int i = symTableStack.size() - 1; i >= 0; i--) {
                logFile.println("   Level " + i + ":");
                var symTableContent = symTableStack.get(i).getContent();
                if (symTableContent.isEmpty()) {
                    logFile.println("      (empty)");
                } else {
                    for (var entry : symTableContent.entrySet()) {
                        logFile.println("      " + entry.getKey() + " --> " + entry.getValue());
                    }
                }
            }

            logFile.println("SymTable (Top Level):");
            var symTable = state.symTable().getContent();
            if (symTable.isEmpty()) {
                logFile.println("   (empty)");
            } else {
                for (var entry : symTable.entrySet()) {
                    logFile.println("   " + entry.getKey() + " --> " + entry.getValue());
                }
            }

            logFile.println("Out:");
            var outList = state.out().getList();
            if (outList.isEmpty()) {
                logFile.println("   (empty)");
            } else {
                for (var value : outList) {
                    logFile.println("   " + value);
                }
            }

            logFile.println("Heap:");
            var heap = state.heap().getContent();
            if (heap.isEmpty()) {
                logFile.println("   (empty)");
            } else {
                for (var entry : heap.entrySet()) {
                    logFile.println("   " + entry.getKey() + " --> " + entry.getValue());
                }
            }

            if (state.fileTable() != null) {
                logFile.println("FileTable:");
                var fileTable = state.fileTable().getContent();
                if (fileTable.isEmpty()) {
                    logFile.println("   (empty)");
                } else {
                    for (var entry : fileTable.entrySet()) {
                        logFile.println("   " + entry.getKey());
                    }
                }
            }


            if (state.procTable() != null) {
                logFile.println("ProcTable:");
                Map<String, Pair<List<String>, IStmt>> procContent = state.procTable().getContent();
                if (procContent.isEmpty()) {
                    logFile.println("   (empty)");
                } else {
                    for (var entry : procContent.entrySet()) {
                        logFile.println("   Procedure: " + entry.getKey());
                        logFile.println("      Parameters: " + String.join(", ", entry.getValue().getKey()));
                        logFile.println("      Body: " + entry.getValue().getValue().toString());
                    }
                }
            }

            logFile.println("------------------------------------------------------");

        } catch (IOException e) {
            throw new CollectionException("Error writing to log file: " + e.getMessage());
        }
    }
}





