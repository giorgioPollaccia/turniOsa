/****************************************************************************
** Meta object code from reading C++ file 'formcalendario.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../formcalendario.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formcalendario.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormCalendario_t {
    QByteArrayData data[5];
    char stringdata[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormCalendario_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormCalendario_t qt_meta_stringdata_FormCalendario = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 11),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 25),
QT_MOC_LITERAL(4, 54, 4)
    },
    "FormCalendario\0signal_data\0\0"
    "on_calendarWidget_clicked\0date\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormCalendario[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QDate,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    4,

       0        // eod
};

void FormCalendario::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormCalendario *_t = static_cast<FormCalendario *>(_o);
        switch (_id) {
        case 0: _t->signal_data((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormCalendario::*_t)(QDate );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormCalendario::signal_data)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FormCalendario::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormCalendario.data,
      qt_meta_data_FormCalendario,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormCalendario::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormCalendario::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormCalendario.stringdata))
        return static_cast<void*>(const_cast< FormCalendario*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormCalendario::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FormCalendario::signal_data(QDate _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
