import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

Window {
    id: login_window
    title: qsTr("Login")
    width: 640
    height: 530
    visible: true
    Connections {
        target: backend
        onCurrentStallIndexChanged: checkLoginResults(backend.currentStallIdx);
    }
    function setCurrentIdx(index) {
        loginForm.stallSelector.currentIndex = index;
    }
    function login(stall_idx) {
        console.log(stall_idx);
        var login_result = backend.login(stall_idx, loginForm.passwordInput.text);
    }
    function checkLoginResults(loginStatus) {
        if (loginStatus === -2) { // wrong password
            loginForm.passwordInput.text = "";
            loginForm.passwordInput.placeholderText = "Invalid password!";
        }
        else {
            login_window.close();
            backend.getStallMenu(loginStatus);
            var main_window = Qt.createComponent("Window.qml");
            var window = main_window.createObject(this);
            window.show();
        }
    }

    LoginForm {
        id: loginForm
        width: 640
        height: 530
        anchors.fill: parent
        loginButton.onClicked: login(stallSelector.currentIndex);
    }
}


