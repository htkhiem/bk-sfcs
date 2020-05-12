import QtQuick 2.0
import backend.qfood 1.0

MenuEditorForm {
    id: menuEditorForm
    authorizeButton.onClicked: {
        authorize_editing(mgrPswField.text);
    }
    function get_category_idx(name) {
        for (var i = 0; i < categoryViewModel.length; ++i) {
            if(categoryViewModel[i].name === name) return i;
        }
        return -1;
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
        var newFood = newFoodComponent.createObject(menuEditorForm);
        backend.proposeAddFood(newFood);
        listViewLoader.source = "";
        listViewLoader.source = "MenuEditorFullListView.qml"
        enable_buttons();
    }

    confirmButton.onActivated: backend.applyProposal();

    Component {
        id: newFoodComponent
        QFood {}
    }
}
