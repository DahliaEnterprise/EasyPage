/****************************************************************************
** Meta object code from reading C++ file 'head.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DahliaSearch/head.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'head.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_head_t {
    uint offsetsAndSizes[14];
    char stringdata0[5];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[18];
    char stringdata5[7];
    char stringdata6[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_head_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_head_t qt_meta_stringdata_head = {
    {
        QT_MOC_LITERAL(0, 4),  // "head"
        QT_MOC_LITERAL(5, 10),  // "sig_result"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 6),  // "number"
        QT_MOC_LITERAL(24, 17),  // "sig_finished_work"
        QT_MOC_LITERAL(42, 6),  // "result"
        QT_MOC_LITERAL(49, 13)   // "finished_work"
    },
    "head",
    "sig_result",
    "",
    "number",
    "sig_finished_work",
    "result",
    "finished_work"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_head[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    0,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   42,    2, 0x08,    4 /* Private */,
       6,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject head::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_head.offsetsAndSizes,
    qt_meta_data_head,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_head_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<head, std::true_type>,
        // method 'sig_result'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sig_finished_work'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'result'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'finished_work'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void head::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<head *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sig_result((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->sig_finished_work(); break;
        case 2: _t->result((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->finished_work(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (head::*)(int );
            if (_t _q_method = &head::sig_result; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (head::*)();
            if (_t _q_method = &head::sig_finished_work; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *head::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *head::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_head.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int head::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void head::sig_result(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void head::sig_finished_work()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
