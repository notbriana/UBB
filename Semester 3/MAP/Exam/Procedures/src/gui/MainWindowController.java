package gui;

import controller.Controller;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;
import model.ADTs.ISymbolTable;
import model.PrgState;
import model.statements.IStmt;
import model.values.StringValue;
import model.values.Value;

import java.util.List;
import java.util.Map;
import java.util.Stack;

public class MainWindowController {

    private Controller controller;

    @FXML
    private TextField prgCountTextField;

    @FXML
    private TableView<Map.Entry<Integer, Value>> heapTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, Integer> heapAddressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapValueColumn;

    @FXML
    private ListView<String> outListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<String> exeStackListView;

    @FXML
    private TableView<Map.Entry<String, Value>> symTableView;

    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symVarColumn;

    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symValueColumn;

    @FXML
    private ListView<String> prgStateIdListView;

    @FXML
    private Button runOneStepButton;


    @FXML
    private TableView<ProcTableEntry> procTableView;

    @FXML
    private TableColumn<ProcTableEntry, String> procNameColumn;

    @FXML
    private TableColumn<ProcTableEntry, String> procParamsColumn;

    @FXML
    private TableColumn<ProcTableEntry, String> procBodyColumn;

    @FXML
    private ListView<String> symTableStackListView;

    private ObservableList<String> exeStackList = FXCollections.observableArrayList();
    private ObservableList<String> outList = FXCollections.observableArrayList();
    private ObservableList<String> fileTableList = FXCollections.observableArrayList();
    private ObservableList<String> programIdList = FXCollections.observableArrayList();
    private ObservableList<String> symTableStackList = FXCollections.observableArrayList();

    @FXML
    public void initialize() {
        heapAddressColumn.setCellValueFactory(data ->
                new SimpleIntegerProperty(data.getValue().getKey()).asObject());
        heapValueColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getValue().toString()));

        symVarColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getKey()));
        symValueColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getValue().toString()));


        procNameColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getName()));
        procParamsColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getParameters()));
        procBodyColumn.setCellValueFactory(data ->
                new SimpleStringProperty(data.getValue().getBody()));

        prgStateIdListView.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldVal, newVal) -> {
                    if (newVal != null) {
                        updatePrgStateSpecificUI();
                    }
                }
        );
    }

    public void setController(Controller controller) {
        this.controller = controller;
        populatePrgStateIds();
        updateUI();
    }

    @FXML
    public void runOneStep() {
        if (controller == null) {
            showError("No controller", "Controller is not initialized!");
            return;
        }

        try {
            List<PrgState> prgList = controller.removeCompletedPrg(controller.getRepo().getPrgList());

            if (prgList.isEmpty()) {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Execution Complete");
                alert.setHeaderText(null);
                alert.setContentText("Program execution has finished!");
                alert.showAndWait();
                runOneStepButton.setDisable(true);
                return;
            }

            controller.oneStepForAllPrg(prgList);

            populatePrgStateIds();
            updateUI();

            List<PrgState> updatedList = controller.getRepo().getPrgList();
            if (updatedList.isEmpty()) {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Execution Complete");
                alert.setHeaderText(null);
                alert.setContentText("Program execution has finished!");
                alert.showAndWait();
                runOneStepButton.setDisable(true);
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
            showError("Thread Interrupted", "Execution was interrupted: " + e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
            showError("Execution Error", e.getMessage());
        }
    }

    private void populatePrgStateIds() {
        if (controller == null) return;

        List<PrgState> prgStates = controller.getRepo().getPrgList();
        programIdList.clear();

        for (PrgState prg : prgStates) {
            programIdList.add(String.valueOf(prg.getId()));
        }

        prgStateIdListView.setItems(programIdList);

        if (!programIdList.isEmpty() && prgStateIdListView.getSelectionModel().getSelectedItem() == null) {
            prgStateIdListView.getSelectionModel().selectFirst();
        }
    }

    private PrgState getSelectedPrgState() {
        String selectedId = prgStateIdListView.getSelectionModel().getSelectedItem();
        if (selectedId == null) return null;

        try {
            int id = Integer.parseInt(selectedId);
            for (PrgState prg : controller.getRepo().getPrgList()) {
                if (prg.getId() == id) {
                    return prg;
                }
            }
        } catch (NumberFormatException e) {
            return null;
        }

        return null;
    }

    private void updateUI() {
        if (controller == null) return;

        List<PrgState> prgStates = controller.getRepo().getPrgList();
        prgCountTextField.setText(String.valueOf(prgStates.size()));

        if (prgStates.isEmpty()) {
            heapTableView.getItems().clear();
            outList.clear();
            fileTableList.clear();
            programIdList.clear();
            symTableView.getItems().clear();
            exeStackList.clear();
            procTableView.getItems().clear();
            symTableStackList.clear();
            outListView.setItems(outList);
            fileTableListView.setItems(fileTableList);
            prgStateIdListView.setItems(programIdList);
            exeStackListView.setItems(exeStackList);
            symTableStackListView.setItems(symTableStackList);
            return;
        }

        PrgState firstPrg = prgStates.get(0);

        Map<Integer, Value> heapContent = firstPrg.heap().getContent();
        heapTableView.getItems().setAll(heapContent.entrySet());

        List<Value> outputValues = firstPrg.out().getList();
        outList.clear();
        for (Value val : outputValues) {
            outList.add(val.toString());
        }
        outListView.setItems(outList);

        Map<StringValue, java.io.BufferedReader> fileTableContent = firstPrg.fileTable().getContent();
        fileTableList.clear();
        for (StringValue fileName : fileTableContent.keySet()) {
            fileTableList.add(fileName.toString());
        }
        fileTableListView.setItems(fileTableList);


        updateProcTable(firstPrg);

        updatePrgStateSpecificUI();
    }


    private void updateProcTable(PrgState prgState) {
        ObservableList<ProcTableEntry> procEntries = FXCollections.observableArrayList();

        Map<String, Pair<List<String>, IStmt>> procContent = prgState.procTable().getContent();

        for (Map.Entry<String, Pair<List<String>, IStmt>> entry : procContent.entrySet()) {
            procEntries.add(new ProcTableEntry(
                    entry.getKey(),
                    entry.getValue().getKey(),
                    entry.getValue().getValue()
            ));
        }

        procTableView.setItems(procEntries);
    }

    private void updatePrgStateSpecificUI() {
        if (controller == null) return;

        PrgState selectedPrg = getSelectedPrgState();
        if (selectedPrg != null) {
            // Update Symbol Table (top of stack)
            Map<String, Value> symTableContent = selectedPrg.symTable().getContent();
            symTableView.getItems().setAll(symTableContent.entrySet());

            // Update Execution Stack
            List<String> stackStrings = selectedPrg.exeStack().getStackReversed().stream()
                    .map(Object::toString)
                    .toList();
            exeStackList.setAll(stackStrings);
            exeStackListView.setItems(exeStackList);

            // Update SymTable Stack Info
            updateSymTableStackInfo(selectedPrg);
        } else {
            symTableView.getItems().clear();
            exeStackList.clear();
            symTableStackList.clear();
            exeStackListView.setItems(exeStackList);
            symTableStackListView.setItems(symTableStackList);
        }
    }

    private void updateSymTableStackInfo(PrgState prgState) {
        symTableStackList.clear();
        Stack<ISymbolTable<String, Value>> stack = prgState.getSymTableStack();

        symTableStackList.add("SymTable Stack Size: " + stack.size());
        symTableStackList.add("---");

        for (int i = stack.size() - 1; i >= 0; i--) {
            ISymbolTable<String, Value> symTable = stack.get(i);
            symTableStackList.add("Level " + i + ":");

            Map<String, Value> content = symTable.getContent();
            if (content.isEmpty()) {
                symTableStackList.add("  (empty)");
            } else {
                for (Map.Entry<String, Value> entry : content.entrySet()) {
                    symTableStackList.add("  " + entry.getKey() + " = " + entry.getValue());
                }
            }
            if (i > 0) {
                symTableStackList.add("---");
            }
        }

        symTableStackListView.setItems(symTableStackList);
    }

    private void showError(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }


    public static class ProcTableEntry {
        private final String name;
        private final String parameters;
        private final String body;

        public ProcTableEntry(String name, List<String> params, IStmt bodyStmt) {
            this.name = name;
            this.parameters = String.join(", ", params);
            this.body = bodyStmt.toString();
        }

        public String getName() {
            return name;
        }

        public String getParameters() {
            return parameters;
        }

        public String getBody() {
            return body;
        }
    }
}


