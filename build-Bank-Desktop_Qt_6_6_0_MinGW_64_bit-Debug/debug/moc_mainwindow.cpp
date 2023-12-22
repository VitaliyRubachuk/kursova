/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Bank/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBankENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBankENDCLASS = QtMocHelpers::stringData(
    "Bank",
    "togglePasswordVisibility",
    "",
    "createUserTable",
    "createCreditTable",
    "createCardsTable",
    "clearTable",
    "loginClicked",
    "registerClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBankENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[5];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[18];
    char stringdata5[17];
    char stringdata6[11];
    char stringdata7[13];
    char stringdata8[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBankENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBankENDCLASS_t qt_meta_stringdata_CLASSBankENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "Bank"
        QT_MOC_LITERAL(5, 24),  // "togglePasswordVisibility"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 15),  // "createUserTable"
        QT_MOC_LITERAL(47, 17),  // "createCreditTable"
        QT_MOC_LITERAL(65, 16),  // "createCardsTable"
        QT_MOC_LITERAL(82, 10),  // "clearTable"
        QT_MOC_LITERAL(93, 12),  // "loginClicked"
        QT_MOC_LITERAL(106, 15)   // "registerClicked"
    },
    "Bank",
    "togglePasswordVisibility",
    "",
    "createUserTable",
    "createCreditTable",
    "createCardsTable",
    "clearTable",
    "loginClicked",
    "registerClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBankENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    0,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Bank::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSBankENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBankENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBankENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Bank, std::true_type>,
        // method 'togglePasswordVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createUserTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createCreditTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createCardsTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loginClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'registerClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Bank::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Bank *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->togglePasswordVisibility(); break;
        case 1: _t->createUserTable(); break;
        case 2: _t->createCreditTable(); break;
        case 3: _t->createCardsTable(); break;
        case 4: _t->clearTable(); break;
        case 5: _t->loginClicked(); break;
        case 6: _t->registerClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Bank::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bank::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBankENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Bank::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
