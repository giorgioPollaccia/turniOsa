/****************************************************************************
** Meta object code from reading C++ file 'formanagrafica.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../formanagrafica.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formanagrafica.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormAnagrafica_t {
    QByteArrayData data[12];
    char stringdata[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormAnagrafica_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormAnagrafica_t qt_meta_stringdata_FormAnagrafica = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 23),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 5),
QT_MOC_LITERAL(4, 46, 16),
QT_MOC_LITERAL(5, 63, 19),
QT_MOC_LITERAL(6, 83, 23),
QT_MOC_LITERAL(7, 107, 28),
QT_MOC_LITERAL(8, 136, 26),
QT_MOC_LITERAL(9, 163, 4),
QT_MOC_LITERAL(10, 168, 26),
QT_MOC_LITERAL(11, 195, 18)
    },
    "FormAnagrafica\0on_tvanagrafica_clicked\0"
    "\0index\0updateDetailGrid\0slot_visualizzaFoto\0"
    "on_pbCambiaFoto_clicked\0"
    "on_pbCancellaRisorsa_clicked\0"
    "on_leMatricola_textChanged\0arg1\0"
    "on_pbCambiaReparto_clicked\0"
    "slot_rinfrescaDati\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormAnagrafica[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08,
       4,    0,   57,    2, 0x08,
       5,    1,   58,    2, 0x08,
       6,    0,   61,    2, 0x08,
       7,    0,   62,    2, 0x08,
       8,    1,   63,    2, 0x08,
      10,    0,   66,    2, 0x08,
      11,    0,   67,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FormAnagrafica::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormAnagrafica *_t = static_cast<FormAnagrafica *>(_o);
        switch (_id) {
        case 0: _t->on_tvanagrafica_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->updateDetailGrid(); break;
        case 2: _t->slot_visualizzaFoto((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->on_pbCambiaFoto_clicked(); break;
        case 4: _t->on_pbCancellaRisorsa_clicked(); break;
        case 5: _t->on_leMatricola_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_pbCambiaReparto_clicked(); break;
        case 7: _t->slot_rinfrescaDati(); break;
        default: ;
        }
    }
}

const QMetaObject FormAnagrafica::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormAnagrafica.data,
      qt_meta_data_FormAnagrafica,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormAnagrafica::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormAnagrafica::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormAnagrafica.stringdata))
        return static_cast<void*>(const_cast< FormAnagrafica*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormAnagrafica::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
