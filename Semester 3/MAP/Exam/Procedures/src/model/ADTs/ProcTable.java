package model.ADTs;

import javafx.util.Pair;
import model.statements.IStmt;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProcTable implements IProcTable {
    private final Map<String, Pair<List<String>, IStmt>> procedures;

    public ProcTable() {
        this.procedures = new HashMap<>();
    }

    @Override
    public synchronized void addProcedure(String name, List<String> parameters, IStmt body) {
        procedures.put(name, new Pair<>(parameters, body));
    }

    @Override
    public synchronized Pair<List<String>, IStmt> lookupProcedure(String name) {
        if (!procedures.containsKey(name))
            throw new RuntimeException("Procedure " + name + " not defined");
        return procedures.get(name);
    }

    @Override
    public synchronized boolean isDefined(String name) {
        return procedures.containsKey(name);
    }

    @Override
    public synchronized Map<String, Pair<List<String>, IStmt>> getContent() {
        return new HashMap<>(procedures);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String, Pair<List<String>, IStmt>> entry : procedures.entrySet()) {
            sb.append(entry.getKey())
                    .append("(")
                    .append(String.join(", ", entry.getValue().getKey()))
                    .append(") -> ")
                    .append(entry.getValue().getValue())
                    .append("\n");
        }
        return sb.toString();
    }
}

