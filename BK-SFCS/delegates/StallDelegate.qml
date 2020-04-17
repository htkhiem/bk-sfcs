import QtQuick 2.4

StallDelegateForm {
    stallMouseArea.onClicked: {
        console.log(stallName.text)
        openMenu(stallName.text)
    }
}
