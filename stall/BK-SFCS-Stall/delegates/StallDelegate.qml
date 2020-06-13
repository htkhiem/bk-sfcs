import QtQuick 2.4
import "../"
StallDelegateForm {
    stallMouseArea.onClicked: {
        console.log(stallName.text)
        setCurrentIdx(index)
    }
}
