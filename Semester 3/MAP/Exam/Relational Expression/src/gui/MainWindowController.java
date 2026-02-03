package gui;

import controller.Controller;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.PrgState;
import model.values.StringValue;
import model.values.Value;

import java.util.List;
import java.util.Map;

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

    private ObservableList<String> exeStackList = FXCollections.observableArrayList();
    private ObservableList<String> outList = FXCollections.observableArrayList();
    private ObservableList<String> fileTableList = FXCollections.observableArrayList();
    private ObservableList<String> programIdList = FXCollections.observableArrayList();

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
            outListView.setItems(outList);
            fileTableListView.setItems(fileTableList);
            prgStateIdListView.setItems(programIdList);
            exeStackListView.setItems(exeStackList);
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

        updatePrgStateSpecificUI();

    }

    private void updatePrgStateSpecificUI() {
        if (controller == null) return;

        PrgState selectedPrg = getSelectedPrgState();
        if (selectedPrg != null) {
            Map<String, Value> symTableContent = selectedPrg.symTable().getContent();
            symTableView.getItems().setAll(symTableContent.entrySet());

            List<String> stackStrings = selectedPrg.exeStack().getStackReversed().stream()
                    .map(Object::toString)
                    .toList();
            exeStackList.setAll(stackStrings);
            exeStackListView.setItems(exeStackList);
        } else {
            symTableView.getItems().clear();
            exeStackList.clear();
            exeStackListView.setItems(exeStackList);
        }
    }

    private void showError(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }
}