/****************************************************************************
** Meta object code from reading C++ file 'QMachinePTWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QMachinePTWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMachinePTWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMachinePTWidget_t {
    QByteArrayData data[4];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMachinePTWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMachinePTWidget_t qt_meta_stringdata_QMachinePTWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QMachinePTWidget"
QT_MOC_LITERAL(1, 17, 12), // "updataNozzle"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 36) // "QMap<NozzleStoreRoom,OneNozzl..."

    },
    "QMachinePTWidget\0updataNozzle\0\0"
    "QMap<NozzleStoreRoom,OneNozzleStore>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMachinePTWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void QMachinePTWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMachinePTWidget *_t = static_cast<QMachinePTWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updataNozzle((*reinterpret_cast< QMap<NozzleStoreRoom,OneNozzleStore>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QMachinePTWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QMachinePTWidget.data,
      qt_meta_data_QMachinePTWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QMachinePTWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMachinePTWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QMachinePTWidget.stringdata0))
        return static_cast<void*>(const_cast< QMachinePTWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QMachinePTWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
