import QtQuick 2.4

StallDelegateForm {
    stallMouseArea.onClicked: {
        console.log(index)
        openMenu(index)
    }
}
