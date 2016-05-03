/****************************************************************************
** Meta object code from reading C++ file 'formgestioneferie.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../formgestioneferie.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formgestioneferie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormGestioneFerie_t {
    QByteArrayData data[10];
    char stringdata[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormGestioneFerie_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormGestioneFerie_t qt_meta_stringdata_FormGestioneFerie = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 20),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 17),
QT_MOC_LITERAL(4, 58, 15),
QT_MOC_LITERAL(5, 74, 19),
QT_MOC_LITERAL(6, 94, 34),
QT_MOC_LITERAL(7, 129, 4),
QT_MOC_LITERAL(8, 134, 32),
QT_MOC_LITERAL(9, 167, 29)
    },
    "FormGestioneFerie\0on_pbDataDal_clicked\0"
    "\0slot_dataIniziale\0slot_dataFinale\0"
    "on_pbDataAl_clicked\0"
    "on_cbMatricola_currentIndexChanged\0"
    "arg1\0on_cbCognome_currentIndexChanged\0"
    "on_pbAggiungiPermesso_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormGestioneFerie[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08,
       3,    1,   50,    2, 0x08,
       4,    1,   53,    2, 0x08,
       5,    0,   56,    2, 0x08,
       6,    1,   57,    2, 0x08,
       8,    1,   60,    2, 0x08,
       9,    0,   63,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void FormGestioneFerie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormGestioneFerie *_t = static_cast<FormGestioneFerie *>(_o);
        switch (_id) {
        case 0: _t->on_pbDataDal_clicked(); break;
        case 1: _t->slot_dataIniziale((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 2: _t->slot_dataFinale((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 3: _t->on_pbDataAl_clicked(); break;
        case 4: _t->on_cbMatricola_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_cbCognome_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_pbAggiungiPermesso_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject FormGestioneFerie::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormGestioneFerie.data,
      qt_meta_data_FormGestioneFerie,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormGestioneFerie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormGestioneFerie::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormGestioneFerie.stringdata))
        return static_cast<void*>(const_cast< FormGestioneFerie*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormGestioneFerie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
