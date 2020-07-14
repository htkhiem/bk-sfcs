import QtQuick 2.0
import "../delegates"
MenuEditorForm {
    id: menuEditorForm
    Connections {
        target: backend
        onManagementModeChanged: check_authorization();
    }
    property bool needsToUpdateImages: false
    authorizeButton.onClicked: {
        backend.loginAsManager(mgrPswField.text);
    }
    function get_category_idx(name) {
        for (var i = 0; i < categoryViewModel.length; ++i) {
            if(categoryViewModel[i].name === name) return i;
        }
        return -1;
    }
    function enable_buttons() {
        if (listViewLoader.item.check_model_data())
            confirmButton.enabled = true;
        else confirmButton.enabled = false;
        revertButton.enabled = true;
    }
    function check_authorization() {
        if (backend.isManagementModeEnabled()) {
            state = "authorized"
            console.log("State changed")
        }
        else {
            mgrPswField.text = "";
            mgrPswField.placeholderText = "Wrong password"
        }
    }
    function markUpdateImages() {
        needsToUpdateImages = true;
    }


    addButton.onClicked: {
        backend.proposeAddFood();
        enable_buttons();
    }

    revertButton.onActivated: {
        backend.getStallMenu(backend.getCurrentStallIdx());
    }

    confirmButton.onActivated: backend.applyProposal(needsToUpdateImages);
    Component {
        id: fullListView
        ListView {
            property bool validData: false
            id: listView
            width: parent.width
            height: parent.height
            bottomMargin: 0
            model: menuViewModel
            delegate: MenuDelegate {
                width: listView.width
                nameField.text: model.modelData.name
                descField.text: model.modelData.description
                priceField.text: model.modelData.price
                oosCheckbox.checked: model.modelData.isOOS
                estTimeField.text: model.modelData.estimatedTime
                categoryBox.currentIndex: get_category_idx(model.modelData.type)
            }
            function check_model_data() {
                console.log("Checking...")
                for (var i = 0; i < count; ++i) {
                    if (!menuViewModel[i].isValid) {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    Component {
        id: restrictedListView
        ListView {
            id: listView
            width: parent.width
            height: parent.height
            bottomMargin: 0
            model: menuViewModel
            delegate: SimpleMenuDelegate {
                width: listView.width
                nameField.text: model.modelData.name
                descField.text: model.modelData.description
                priceField.text: model.modelData.price
                oosCheckbox.checked: model.modelData.isOOS
                estTimeField.text: model.modelData.estimatedTime
                categoryBox.currentIndex: get_category_idx(model.modelData.type)
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
