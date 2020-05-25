import QtQuick 2.4

SearchPopupForm {
    searchButton.onClicked:{
        backend.searchFilter(searchField.text)
        close()
    }
    onClosed: refocus();
}
