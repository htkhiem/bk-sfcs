/****************************************************************************
** Meta object code from reading C++ file 'menu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../backend/BK-SFCS-Backend/src/menu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Stall_t {
    QByteArrayData data[24];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Stall_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Stall_t qt_meta_stringdata_Stall = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Stall"
QT_MOC_LITERAL(1, 6, 7), // "getMenu"
QT_MOC_LITERAL(2, 14, 21), // "const QVector<QFood>*"
QT_MOC_LITERAL(3, 36, 0), // ""
QT_MOC_LITERAL(4, 37, 15), // "getEditableMenu"
QT_MOC_LITERAL(5, 53, 15), // "QVector<QFood>*"
QT_MOC_LITERAL(6, 69, 7), // "addFood"
QT_MOC_LITERAL(7, 77, 5), // "QFood"
QT_MOC_LITERAL(8, 83, 4), // "item"
QT_MOC_LITERAL(9, 88, 10), // "removeFood"
QT_MOC_LITERAL(10, 99, 12), // "getImagePath"
QT_MOC_LITERAL(11, 112, 12), // "setImagePath"
QT_MOC_LITERAL(12, 125, 7), // "imgpath"
QT_MOC_LITERAL(13, 133, 12), // "getStallName"
QT_MOC_LITERAL(14, 146, 12), // "setStallName"
QT_MOC_LITERAL(15, 159, 4), // "name"
QT_MOC_LITERAL(16, 164, 11), // "getPassword"
QT_MOC_LITERAL(17, 176, 11), // "setPassword"
QT_MOC_LITERAL(18, 188, 8), // "password"
QT_MOC_LITERAL(19, 197, 15), // "getMgmtPassword"
QT_MOC_LITERAL(20, 213, 15), // "setMgmtPassword"
QT_MOC_LITERAL(21, 229, 13), // "mgmt_password"
QT_MOC_LITERAL(22, 243, 9), // "stallName"
QT_MOC_LITERAL(23, 253, 9) // "imagePath"

    },
    "Stall\0getMenu\0const QVector<QFood>*\0"
    "\0getEditableMenu\0QVector<QFood>*\0"
    "addFood\0QFood\0item\0removeFood\0"
    "getImagePath\0setImagePath\0imgpath\0"
    "getStallName\0setStallName\0name\0"
    "getPassword\0setPassword\0password\0"
    "getMgmtPassword\0setMgmtPassword\0"
    "mgmt_password\0stallName\0imagePath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Stall[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       2,   98, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    3, 0x0a /* Public */,
       4,    0,   75,    3, 0x0a /* Public */,
       6,    1,   76,    3, 0x0a /* Public */,
       9,    1,   79,    3, 0x0a /* Public */,
      10,    0,   82,    3, 0x0a /* Public */,
      11,    1,   83,    3, 0x0a /* Public */,
      13,    0,   86,    3, 0x0a /* Public */,
      14,    1,   87,    3, 0x0a /* Public */,
      16,    0,   90,    3, 0x0a /* Public */,
      17,    1,   91,    3, 0x0a /* Public */,
      19,    0,   94,    3, 0x0a /* Public */,
      20,    1,   95,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2,
    0x80000000 | 5,
    QMetaType::Bool, 0x80000000 | 7,    8,
    QMetaType::Bool, 0x80000000 | 7,    8,
    QMetaType::QUrl,
    QMetaType::Void, QMetaType::QUrl,   12,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,

 // properties: name, type, flags
      22, QMetaType::QString, 0x00095103,
      23, QMetaType::QUrl, 0x00095103,

       0        // eod
};

void Stall::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Stall *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { const QVector<QFood>* _r = _t->getMenu();
            if (_a[0]) *reinterpret_cast< const QVector<QFood>**>(_a[0]) = std::move(_r); }  break;
        case 1: { QVector<QFood>* _r = _t->getEditableMenu();
            if (_a[0]) *reinterpret_cast< QVector<QFood>**>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->addFood((*reinterpret_cast< QFood(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->removeFood((*reinterpret_cast< QFood(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { QUrl _r = _t->getImagePath();
            if (_a[0]) *reinterpret_cast< QUrl*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setImagePath((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 6: { QString _r = _t->getStallName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setStallName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { QString _r = _t->getPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: { QString _r = _t->getMgmtPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setMgmtPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Stall *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getStallName(); break;
        case 1: *reinterpret_cast< QUrl*>(_v) = _t->getImagePath(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Stall *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setStallName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setImagePath(*reinterpret_cast< QUrl*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Stall::staticMetaObject = { {
    QMetaObject::SuperData::link<Jsonable::staticMetaObject>(),
    qt_meta_stringdata_Stall.data,
    qt_meta_data_Stall,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Stall::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Stall::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Stall.stringdata0))
        return static_cast<void*>(this);
    return Jsonable::qt_metacast(_clname);
}

int Stall::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Jsonable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
