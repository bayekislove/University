import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.fxml.*;
import javafx.scene.*;

public class App extends Application {

    @Override
    public void start(Stage stage) throws Exception {

        Parent root = FXMLLoader.load( getClass().getResource("calculatorView.fxml") );
    
        Scene scene = new Scene(root, 455, 612);
        scene.getStylesheets().add("outlook.css");

        stage.setTitle("Worst calculator");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

}