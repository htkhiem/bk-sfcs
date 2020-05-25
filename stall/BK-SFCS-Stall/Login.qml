import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

Window {
    id: login_window
    title: qsTr("Login")
    width: 640
    height: 530
    visible: true
    function setCurrentIdx(index) {
        loginForm.stallSelector.currentIndex = index;
    }
    function login(stall_idx) {
        console.log(stall_idx);
        var login_result = backend.login(stall_idx, loginForm.passwordInput.text);
        if (login_result) {
            login_window.close();
            var main_window = Qt.createComponent("Window.qml");
            var window = main_window.createObject(this);
            window.show();
        }
        else {
            loginForm.passwordInput.text = "";
            loginForm.passwordInput.placeholderText = "Invalid password!";
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


