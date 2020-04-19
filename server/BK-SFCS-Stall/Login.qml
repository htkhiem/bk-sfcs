import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
Window {
    id: login_window
    title: qsTr("Login")
    width: loginForm.width
    height: loginForm.height
    visible: true
    function setCurrentIdx(index) {
        loginForm.stallSelector.currentIndex = index;
    }
    function login() { // totally useless login function used just for mockup

    }

    LoginForm {
        id: loginForm
        width: 640
        height: 530
        anchors.fill: parent
    }
}


