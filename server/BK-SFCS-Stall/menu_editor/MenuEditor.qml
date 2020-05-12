import QtQuick 2.0
import backend.qfood 1.0

MenuEditorForm {
    authorizeButton.onClicked: {
        authorize_editing(mgrPswField.text);
    }

    function enable_buttons() {
        confirmButton.enabled = true;
        revertButton.enabled = true;
    }
    function authorize_editing(psw) {
        // placeholder for actual authorization code
        if (psw === "root") {
            state = "authorized"
            console.log("State changed")
        }
        else {
            mgrPswField.text = "";
            mgrPswField.placeholderText = "Wrong password"
        }
    }
    addButton.onClicked: {
        var newFood = newFoodComponent.createObject();
        backend.addFood(newFood);
    }

    Component {
        id: newFoodComponent
        QFood {}
    }
}
