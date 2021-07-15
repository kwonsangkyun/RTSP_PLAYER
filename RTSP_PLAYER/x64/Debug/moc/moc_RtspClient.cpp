/****************************************************************************
** Meta object code from reading C++ file 'RtspClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../RtspClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RtspClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRtspClient_t {
    QByteArrayData data[11];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRtspClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRtspClient_t qt_meta_stringdata_CRtspClient = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CRtspClient"
QT_MOC_LITERAL(1, 12, 17), // "unAuthorizedError"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 25), // "std::map<QString,QString>"
QT_MOC_LITERAL(4, 57, 9), // "headerMap"
QT_MOC_LITERAL(5, 67, 10), // "onNewFrame"
QT_MOC_LITERAL(6, 78, 9), // "frameData"
QT_MOC_LITERAL(7, 88, 10), // "onConneted"
QT_MOC_LITERAL(8, 99, 14), // "onDisconnected"
QT_MOC_LITERAL(9, 114, 14), // "onReceivedData"
QT_MOC_LITERAL(10, 129, 10) // "onSendRtcp"

    },
    "CRtspClient\0unAuthorizedError\0\0"
    "std::map<QString,QString>\0headerMap\0"
    "onNewFrame\0frameData\0onConneted\0"
    "onDisconnected\0onReceivedData\0onSendRtcp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRtspClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CRtspClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CRtspClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->unAuthorizedError((*reinterpret_cast< std::map<QString,QString>(*)>(_a[1]))); break;
        case 1: _t->onNewFrame((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->onConneted(); break;
        case 3: _t->onDisconnected(); break;
        case 4: _t->onReceivedData(); break;
        case 5: _t->onSendRtcp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CRtspClient::*)(std::map<QString,QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRtspClient::unAuthorizedError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CRtspClient::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRtspClient::onNewFrame)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CRtspClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CRtspClient.data,
    qt_meta_data_CRtspClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CRtspClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRtspClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CRtspClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CRtspClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CRtspClient::unAuthorizedError(std::map<QString,QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CRtspClient::onNewFrame(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
