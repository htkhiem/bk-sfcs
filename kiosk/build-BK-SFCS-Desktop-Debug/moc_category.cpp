/****************************************************************************
** Meta object code from reading C++ file 'category.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../backend/BK-SFCS-Backend/src/category.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'category.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Category_t {
    QByteArrayData data[17];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Category_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Category_t qt_meta_stringdata_Category = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Category"
QT_MOC_LITERAL(1, 9, 7), // "getName"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "setName"
QT_MOC_LITERAL(4, 26, 9), // "getSymbol"
QT_MOC_LITERAL(5, 36, 9), // "setSymbol"
QT_MOC_LITERAL(6, 46, 13), // "getStartColor"
QT_MOC_LITERAL(7, 60, 13), // "setStartColor"
QT_MOC_LITERAL(8, 74, 11), // "getEndColor"
QT_MOC_LITERAL(9, 86, 11), // "setEndColor"
QT_MOC_LITERAL(10, 98, 9), // "isVisible"
QT_MOC_LITERAL(11, 108, 16), // "toggleVisibility"
QT_MOC_LITERAL(12, 125, 4), // "name"
QT_MOC_LITERAL(13, 130, 6), // "symbol"
QT_MOC_LITERAL(14, 137, 10), // "colorStart"
QT_MOC_LITERAL(15, 148, 8), // "colorEnd"
QT_MOC_LITERAL(16, 157, 7) // "visible"

    },
    "Category\0getName\0\0setName\0getSymbol\0"
    "setSymbol\0getStartColor\0setStartColor\0"
    "getEndColor\0setEndColor\0isVisible\0"
    "toggleVisibility\0name\0symbol\0colorStart\0"
    "colorEnd\0visible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Category[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    1,   65,    2, 0x0a /* Public */,
       4,    0,   68,    2, 0x0a /* Public */,
       5,    1,   69,    2, 0x0a /* Public */,
       6,    0,   72,    2, 0x0a /* Public */,
       7,    1,   73,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    1,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::QChar,
    QMetaType::Void, QMetaType::QChar,    2,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    2,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00095103,
      13, QMetaType::QChar, 0x00095103,
      14, QMetaType::QColor, 0x00095003,
      15, QMetaType::QColor, 0x00095003,
      16, QMetaType::Bool, 0x00095003,

       0        // eod
};

void Category::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Category *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { QChar _r = _t->getSymbol();
            if (_a[0]) *reinterpret_cast< QChar*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->setSymbol((*reinterpret_cast< QChar(*)>(_a[1]))); break;
        case 4: { QColor _r = _t->getStartColor();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setStartColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 6: { QColor _r = _t->getEndColor();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setEndColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 8: { bool _r = _t->isVisible();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->toggleVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Category *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 1: *reinterpret_cast< QChar*>(_v) = _t->getSymbol(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->getStartColor(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->getEndColor(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isVisible(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Category *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setSymbol(*reinterpret_cast< QChar*>(_v)); break;
        case 2: _t->setStartColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setEndColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->toggleVisibility(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Category::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Category.data,
    qt_meta_data_Category,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Category::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Category::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Category.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Category::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
