import QtQuick 2.0
import "../delegates"

ListView {
    id: listView
    width: parent.width
    height: parent.height
    bottomMargin: 0
    model: menuViewModel
    delegate: SimpleMenuDelegate {
        width: listView.width
        itemImage.source: model.modelData.imagePath
        nameField.text: model.modelData.name
        descField.text: model.modelData.description
        priceField.text: model.modelData.price + qsTr("VND")
        oosCheckbox.checked: model.modelData.isOOS
        estTimeField.text: model.modelData.estimatedTime
        categoryBox.currentIndex: get_category_idx(model.modelData.type)
    }
}
