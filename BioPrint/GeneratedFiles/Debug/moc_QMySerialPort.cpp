/****************************************************************************
** Meta object code from reading C++ file 'QMySerialPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QMySerialPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMySerialPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMySerialPort_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMySerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMySerialPort_t qt_meta_stringdata_QMySerialPort = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QMySerialPort"
QT_MOC_LITERAL(1, 14, 22), // "signalUpdataNozzleInfo"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "info"
QT_MOC_LITERAL(4, 43, 22), // "signalUpdataNozzleTemp"
QT_MOC_LITERAL(5, 66, 4), // "temp"
QT_MOC_LITERAL(6, 71, 22), // "signalUpdataChilleInfo"
QT_MOC_LITERAL(7, 94, 10), // "serialRead"
QT_MOC_LITERAL(8, 105, 11), // "serialWrite"
QT_MOC_LITERAL(9, 117, 11), // "const char*"
QT_MOC_LITERAL(10, 129, 3) // "ins"

    },
    "QMySerialPort\0signalUpdataNozzleInfo\0"
    "\0info\0signalUpdataNozzleTemp\0temp\0"
    "signalUpdataChilleInfo\0serialRead\0"
    "serialWrite\0const char*\0ins"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMySerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   48,    2, 0x0a /* Public */,
       8,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 9,   10,

       0        // eod
};

void QMySerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMySerialPort *_t = static_cast<QMySerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdataNozzleInfo((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->signalUpdataNozzleTemp((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->signalUpdataChilleInfo((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->serialRead(); break;
        case 4: { bool _r = _t->serialWrite((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QMySerialPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QMySerialPort::signalUpdataNozzleInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QMySerialPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QMySerialPort::signalUpdataNozzleTemp)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QMySerialPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QMySerialPort::signalUpdataChilleInfo)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QMySerialPort::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QMySerialPort.data,
      qt_meta_data_QMySerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QMySerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMySerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QMySerialPort.stringdata0))
        return static_cast<void*>(const_cast< QMySerialPort*>(this));
    return QThread::qt_metacast(_clname);
}

int QMySerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QMySerialPort::signalUpdataNozzleInfo(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMySerialPort::signalUpdataNozzleTemp(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QMySerialPort::signalUpdataChilleInfo(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
