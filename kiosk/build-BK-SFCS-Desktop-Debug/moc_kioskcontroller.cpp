/****************************************************************************
** Meta object code from reading C++ file 'kioskcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../BK-SFCS/controller/kioskcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kioskcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KioskController_t {
    QByteArrayData data[14];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KioskController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KioskController_t qt_meta_stringdata_KioskController = {
    {
QT_MOC_LITERAL(0, 0, 15), // "KioskController"
QT_MOC_LITERAL(1, 16, 18), // "getCurrentStallIdx"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 18), // "setCurrentStallIdx"
QT_MOC_LITERAL(4, 55, 3), // "idx"
QT_MOC_LITERAL(5, 59, 12), // "searchFilter"
QT_MOC_LITERAL(6, 72, 6), // "_input"
QT_MOC_LITERAL(7, 79, 16), // "setOrderFoodItem"
QT_MOC_LITERAL(8, 96, 16), // "setOrderQuantity"
QT_MOC_LITERAL(9, 113, 3), // "qty"
QT_MOC_LITERAL(10, 117, 14), // "setOrderMethod"
QT_MOC_LITERAL(11, 132, 6), // "method"
QT_MOC_LITERAL(12, 139, 9), // "sendOrder"
QT_MOC_LITERAL(13, 149, 15) // "currentStallIdx"

    },
    "KioskController\0getCurrentStallIdx\0\0"
    "setCurrentStallIdx\0idx\0searchFilter\0"
    "_input\0setOrderFoodItem\0setOrderQuantity\0"
    "qty\0setOrderMethod\0method\0sendOrder\0"
    "currentStallIdx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KioskController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   66, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,
      10,    1,   62,    2, 0x0a /* Public */,
      12,    0,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

 // properties: name, type, flags
      13, QMetaType::Int, 0x00095103,

       0        // eod
};

void KioskController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KioskController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->getCurrentStallIdx();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setCurrentStallIdx((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->searchFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setOrderFoodItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setOrderQuantity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setOrderMethod((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sendOrder(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<KioskController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getCurrentStallIdx(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<KioskController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCurrentStallIdx(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject KioskController::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractController::staticMetaObject>(),
    qt_meta_stringdata_KioskController.data,
    qt_meta_data_KioskController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KioskController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KioskController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KioskController.stringdata0))
        return static_cast<void*>(this);
    return AbstractController::qt_metacast(_clname);
}

int KioskController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractController::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
