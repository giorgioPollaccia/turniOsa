/****************************************************************************
** Meta object code from reading C++ file 'formgenerazioneturno.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../formgenerazioneturno.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formgenerazioneturno.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormGenerazioneTurno_t {
    QByteArrayData data[18];
    char stringdata[395];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FormGenerazioneTurno_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FormGenerazioneTurno_t qt_meta_stringdata_FormGenerazioneTurno = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 39),
QT_MOC_LITERAL(2, 61, 0),
QT_MOC_LITERAL(3, 62, 17),
QT_MOC_LITERAL(4, 80, 15),
QT_MOC_LITERAL(5, 96, 20),
QT_MOC_LITERAL(6, 117, 20),
QT_MOC_LITERAL(7, 138, 19),
QT_MOC_LITERAL(8, 158, 28),
QT_MOC_LITERAL(9, 187, 29),
QT_MOC_LITERAL(10, 217, 5),
QT_MOC_LITERAL(11, 223, 29),
QT_MOC_LITERAL(12, 253, 29),
QT_MOC_LITERAL(13, 283, 19),
QT_MOC_LITERAL(14, 303, 31),
QT_MOC_LITERAL(15, 335, 4),
QT_MOC_LITERAL(16, 340, 23),
QT_MOC_LITERAL(17, 364, 29)
    },
    "FormGenerazioneTurno\0"
    "slot_checkDoppioniAssociazioniTurnoBase\0"
    "\0slot_dataIniziale\0slot_dataFinale\0"
    "slot_cambioIdMatrice\0on_pbDataDal_clicked\0"
    "on_pbDataAl_clicked\0on_pbTurnoPrecedente_clicked\0"
    "on_cbMese_currentIndexChanged\0index\0"
    "on_cbAnno_currentIndexChanged\0"
    "on_pbTurnoPrecedente2_clicked\0"
    "on_pbTurnoP_clicked\0on_cbreparti_currentTextChanged\0"
    "arg1\0on_pbSalvaExcel_clicked\0"
    "on_pbInsertInDatabase_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormGenerazioneTurno[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08,
       3,    1,   85,    2, 0x08,
       4,    1,   88,    2, 0x08,
       5,    1,   91,    2, 0x08,
       6,    0,   94,    2, 0x08,
       7,    0,   95,    2, 0x08,
       8,    0,   96,    2, 0x08,
       9,    1,   97,    2, 0x08,
      11,    1,  100,    2, 0x08,
      12,    0,  103,    2, 0x08,
      13,    0,  104,    2, 0x08,
      14,    1,  105,    2, 0x08,
      16,    0,  108,    2, 0x08,
      17,    0,  109,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FormGenerazioneTurno::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormGenerazioneTurno *_t = static_cast<FormGenerazioneTurno *>(_o);
        switch (_id) {
        case 0: _t->slot_checkDoppioniAssociazioniTurnoBase(); break;
        case 1: _t->slot_dataIniziale((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 2: _t->slot_dataFinale((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 3: _t->slot_cambioIdMatrice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_pbDataDal_clicked(); break;
        case 5: _t->on_pbDataAl_clicked(); break;
        case 6: _t->on_pbTurnoPrecedente_clicked(); break;
        case 7: _t->on_cbMese_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_cbAnno_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_pbTurnoPrecedente2_clicked(); break;
        case 10: _t->on_pbTurnoP_clicked(); break;
        case 11: _t->on_cbreparti_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_pbSalvaExcel_clicked(); break;
        case 13: _t->on_pbInsertInDatabase_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject FormGenerazioneTurno::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormGenerazioneTurno.data,
      qt_meta_data_FormGenerazioneTurno,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormGenerazioneTurno::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormGenerazioneTurno::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormGenerazioneTurno.stringdata))
        return static_cast<void*>(const_cast< FormGenerazioneTurno*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormGenerazioneTurno::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
