import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class calculatorController 
{
    private calculatorModel calcModel = new calculatorModel();

    @FXML
    private Button charButton;

    @FXML
    private Button numButton;

    @FXML
    private Button delButton;

    @FXML
    private Button opButton;

    @FXML
    private Button decButton;

    @FXML
    private Button hexButton;

    @FXML
    private Button binButton;

    @FXML
    private Button evalButton;

    @FXML
    private Label curr;

    @FXML
    private Label prev;

    private void setTextByChangeRadixResponse(String res){
        String[] resTab = res.split(";");
        curr.setText( resTab.length > 1 ? resTab[1] : "" );

        prev.setText( resTab[0] );
    }

    @FXML
    void binButtonClicked(ActionEvent event) {
        setTextByChangeRadixResponse( calcModel.changeRadix(2) );
    }

    @FXML
    void charButtonClicked(ActionEvent event) {
        if( !(calcModel.getRadix() == 16) ) return;
        curr.setText( calcModel.addChar( ((Button)(event.getSource())).getText() ) );
    }

    @FXML
    void decButtonClicked(ActionEvent event) {
        setTextByChangeRadixResponse( calcModel.changeRadix(10) );
    }

    @FXML
    void delButtonClicked(ActionEvent event) {
        String res = calcModel.removeChar();

        if( res.equals("") )
        {
            prev.setText("");
        }
        curr.setText( res );
    }

    @FXML
    void evalButtonClicked(ActionEvent event) {
        prev.setText( calcModel.eval() );
        curr.setText( "" );
    }

    @FXML
    void hexButtonClicked(ActionEvent event) {
        setTextByChangeRadixResponse( calcModel.changeRadix(16) );
    }

    @FXML
    void numButtonClicked(ActionEvent event) {
        String sourceVal = ((Button)(event.getSource())).getText();
        if( calcModel.getRadix() == 2 && !( sourceVal.equals("0") || sourceVal.equals("1") ) ) return;
        curr.setText( calcModel.addChar( sourceVal ) );
    }

    @FXML
    void opButtonClicked(ActionEvent event) {
        curr.setText( calcModel.addOperator( ((Button)(event.getSource())).getText() ) );
    }
}