package model.ADTs;

import javafx.util.Pair;
import model.statements.IStmt;

import java.util.List;
import java.util.Map;

public interface IProcTable {
    void addProcedure(String name, List<String> parameters, IStmt body);

    Pair<List<String>, IStmt> lookupProcedure(String name);

    boolean isDefined(String name);

    Map<String, Pair<List<String>, IStmt>> getContent();
}


