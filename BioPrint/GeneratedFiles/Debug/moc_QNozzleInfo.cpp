/****************************************************************************
** Meta object code from reading C++ file 'QNozzleInfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QNozzleInfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QNozzleInfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QNozzleInfo_t {
    QByteArrayData data[7];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QNozzleInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QNozzleInfo_t qt_meta_stringdata_QNozzleInfo = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QNozzleInfo"
QT_MOC_LITERAL(1, 12, 25), // "signalNozzleStoreToWidget"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 36), // "QMap<NozzleStoreRoom,OneNozzl..."
QT_MOC_LITERAL(4, 76, 20), // "slotUpdataNozzleInfo"
QT_MOC_LITERAL(5, 97, 4), // "info"
QT_MOC_LITERAL(6, 102, 20) // "slotUpdataNozzleTemp"

    },
    "QNozzleInfo\0signalNozzleStoreToWidget\0"
    "\0QMap<NozzleStoreRoom,OneNozzleStore>\0"
    "slotUpdataNozzleInfo\0info\0"
    "slotUpdataNozzleTemp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QNozzleInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,

       0        // eod
};

void QNozzleInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QNozzleInfo *_t = static_cast<QNozzleInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalNozzleStoreToWidget((*reinterpret_cast< QMap<NozzleStoreRoom,OneNozzleStore>(*)>(_a[1]))); break;
        case 1: _t->slotUpdataNozzleInfo((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->slotUpdataNozzleTemp((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QNozzleInfo::*_t)(QMap<NozzleStoreRoom,OneNozzleStore> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QNozzleInfo::signalNozzleStoreToWidget)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QNozzleInfo::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QNozzleInfo.data,
      qt_meta_data_QNozzleInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QNozzleInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QNozzleInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QNozzleInfo.stringdata0))
        return static_cast<void*>(const_cast< QNozzleInfo*>(this));
    return QThread::qt_metacast(_clname);
}

int QNozzleInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QNozzleInfo::signalNozzleStoreToWidget(QMap<NozzleStoreRoom,OneNozzleStore> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
