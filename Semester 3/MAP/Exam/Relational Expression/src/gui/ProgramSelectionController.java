package gui;

import controller.Controller;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import view.ProgramRepository;

public class ProgramSelectionController {

    @FXML
    private ListView<String> programListView;

    @FXML
    private Button runButton;

    private ProgramRepository programRepo;

    @FXML
    public void initialize() {
        programRepo = new ProgramRepository();
        programListView.getItems().addAll(programRepo.getProgramNames());
    }

    @FXML
    public void runSelectedProgram() {
        int index = programListView.getSelectionModel().getSelectedIndex();
        if (index < 0) return;

        Controller controller = programRepo.getController(index);

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("main.fxml"));
            Parent root = loader.load();

            MainWindowController mainController = loader.getController();
            mainController.setController(controller);

            Stage stage = new Stage();
            stage.setTitle("Interpreter");
            stage.setScene(new Scene(root));
            stage.show();

            runButton.getScene().getWindow().hide();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
