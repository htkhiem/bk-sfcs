/****************************************************************************
** Meta object code from reading C++ file 'stallmgmtcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../BK-SFCS-Stall/controller/stallmgmtcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stallmgmtcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StallMgmtController_t {
    QByteArrayData data[20];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StallMgmtController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StallMgmtController_t qt_meta_stringdata_StallMgmtController = {
    {
QT_MOC_LITERAL(0, 0, 19), // "StallMgmtController"
QT_MOC_LITERAL(1, 20, 5), // "login"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "idx"
QT_MOC_LITERAL(4, 31, 3), // "psw"
QT_MOC_LITERAL(5, 35, 6), // "logout"
QT_MOC_LITERAL(6, 42, 23), // "updateWaitlistViewModel"
QT_MOC_LITERAL(7, 66, 18), // "populateMgmtGraphs"
QT_MOC_LITERAL(8, 85, 14), // "loginAsManager"
QT_MOC_LITERAL(9, 100, 14), // "proposeAddFood"
QT_MOC_LITERAL(10, 115, 17), // "proposeRemoveFood"
QT_MOC_LITERAL(11, 133, 13), // "applyProposal"
QT_MOC_LITERAL(12, 147, 12), // "setStallName"
QT_MOC_LITERAL(13, 160, 4), // "name"
QT_MOC_LITERAL(14, 165, 16), // "setStallPassword"
QT_MOC_LITERAL(15, 182, 8), // "password"
QT_MOC_LITERAL(16, 191, 20), // "setStallMgmtPassword"
QT_MOC_LITERAL(17, 212, 7), // "mgmtpsw"
QT_MOC_LITERAL(18, 220, 13), // "setStallImage"
QT_MOC_LITERAL(19, 234, 7) // "imgpath"

    },
    "StallMgmtController\0login\0\0idx\0psw\0"
    "logout\0updateWaitlistViewModel\0"
    "populateMgmtGraphs\0loginAsManager\0"
    "proposeAddFood\0proposeRemoveFood\0"
    "applyProposal\0setStallName\0name\0"
    "setStallPassword\0password\0"
    "setStallMgmtPassword\0mgmtpsw\0setStallImage\0"
    "imgpath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StallMgmtController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       5,    0,   79,    2, 0x0a /* Public */,
       6,    0,   80,    2, 0x0a /* Public */,
       7,    0,   81,    2, 0x0a /* Public */,
       8,    1,   82,    2, 0x0a /* Public */,
       9,    0,   85,    2, 0x0a /* Public */,
      10,    1,   86,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    1,   90,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x0a /* Public */,
      16,    1,   96,    2, 0x0a /* Public */,
      18,    1,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   13,
    QMetaType::Bool, QMetaType::QString,   15,
    QMetaType::Bool, QMetaType::QString,   17,
    QMetaType::Bool, QMetaType::QUrl,   19,

       0        // eod
};

void StallMgmtController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StallMgmtController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->login((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->logout();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->updateWaitlistViewModel(); break;
        case 3: _t->populateMgmtGraphs(); break;
        case 4: { bool _r = _t->loginAsManager((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->proposeAddFood(); break;
        case 6: { bool _r = _t->proposeRemoveFood((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->applyProposal(); break;
        case 8: { bool _r = _t->setStallName((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->setStallPassword((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->setStallMgmtPassword((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->setStallImage((*reinterpret_cast< const QUrl(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StallMgmtController::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractController::staticMetaObject>(),
    qt_meta_stringdata_StallMgmtController.data,
    qt_meta_data_StallMgmtController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StallMgmtController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StallMgmtController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StallMgmtController.stringdata0))
        return static_cast<void*>(this);
    return AbstractController::qt_metacast(_clname);
}

int StallMgmtController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractController::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
