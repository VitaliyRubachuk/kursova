/****************************************************************************
** Meta object code from reading C++ file 'managerwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Bank/managerwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'managerwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSManagerWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSManagerWindowENDCLASS = QtMocHelpers::stringData(
    "ManagerWindow",
    "hasCard",
    "",
    "username",
    "repayCredit",
    "updateCreditTable",
    "showIssueCreditDialog",
    "issueCreditToAccount",
    "account",
    "amount",
    "isAccountExists",
    "applyTextEditStyle",
    "QTextEdit*",
    "textEdit",
    "applyButtonStyle",
    "QPushButton*",
    "button",
    "canTakeLoan",
    "showManagerWindow"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSManagerWindowENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[14];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[12];
    char stringdata5[18];
    char stringdata6[22];
    char stringdata7[21];
    char stringdata8[8];
    char stringdata9[7];
    char stringdata10[16];
    char stringdata11[19];
    char stringdata12[11];
    char stringdata13[9];
    char stringdata14[17];
    char stringdata15[13];
    char stringdata16[7];
    char stringdata17[12];
    char stringdata18[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSManagerWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSManagerWindowENDCLASS_t qt_meta_stringdata_CLASSManagerWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "ManagerWindow"
        QT_MOC_LITERAL(14, 7),  // "hasCard"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 8),  // "username"
        QT_MOC_LITERAL(32, 11),  // "repayCredit"
        QT_MOC_LITERAL(44, 17),  // "updateCreditTable"
        QT_MOC_LITERAL(62, 21),  // "showIssueCreditDialog"
        QT_MOC_LITERAL(84, 20),  // "issueCreditToAccount"
        QT_MOC_LITERAL(105, 7),  // "account"
        QT_MOC_LITERAL(113, 6),  // "amount"
        QT_MOC_LITERAL(120, 15),  // "isAccountExists"
        QT_MOC_LITERAL(136, 18),  // "applyTextEditStyle"
        QT_MOC_LITERAL(155, 10),  // "QTextEdit*"
        QT_MOC_LITERAL(166, 8),  // "textEdit"
        QT_MOC_LITERAL(175, 16),  // "applyButtonStyle"
        QT_MOC_LITERAL(192, 12),  // "QPushButton*"
        QT_MOC_LITERAL(205, 6),  // "button"
        QT_MOC_LITERAL(212, 11),  // "canTakeLoan"
        QT_MOC_LITERAL(224, 17)   // "showManagerWindow"
    },
    "ManagerWindow",
    "hasCard",
    "",
    "username",
    "repayCredit",
    "updateCreditTable",
    "showIssueCreditDialog",
    "issueCreditToAccount",
    "account",
    "amount",
    "isAccountExists",
    "applyTextEditStyle",
    "QTextEdit*",
    "textEdit",
    "applyButtonStyle",
    "QPushButton*",
    "button",
    "canTakeLoan",
    "showManagerWindow"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSManagerWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x08,    1 /* Private */,
       4,    0,   77,    2, 0x08,    3 /* Private */,
       5,    0,   78,    2, 0x08,    4 /* Private */,
       6,    0,   79,    2, 0x08,    5 /* Private */,
       7,    2,   80,    2, 0x08,    6 /* Private */,
      10,    1,   85,    2, 0x08,    9 /* Private */,
      11,    1,   88,    2, 0x08,   11 /* Private */,
      14,    1,   91,    2, 0x08,   13 /* Private */,
      17,    1,   94,    2, 0x08,   15 /* Private */,
      18,    0,   97,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ManagerWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSManagerWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSManagerWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSManagerWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ManagerWindow, std::true_type>,
        // method 'hasCard'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'repayCredit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCreditTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showIssueCreditDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'issueCreditToAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'isAccountExists'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'applyTextEditStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTextEdit *, std::false_type>,
        // method 'applyButtonStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        // method 'canTakeLoan'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showManagerWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ManagerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManagerWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { bool _r = _t->hasCard((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->repayCredit(); break;
        case 2: _t->updateCreditTable(); break;
        case 3: _t->showIssueCreditDialog(); break;
        case 4: _t->issueCreditToAccount((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: { bool _r = _t->isAccountExists((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->applyTextEditStyle((*reinterpret_cast< std::add_pointer_t<QTextEdit*>>(_a[1]))); break;
        case 7: _t->applyButtonStyle((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 8: { bool _r = _t->canTakeLoan((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->showManagerWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTextEdit* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *ManagerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManagerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSManagerWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ManagerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
