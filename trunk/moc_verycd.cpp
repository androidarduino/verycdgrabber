/****************************************************************************
** Meta object code from reading C++ file 'verycd.h'
**
** Created: Tue Sep 7 10:49:29 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "verycd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'verycd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Ed2kItem[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_Ed2kItem[] = {
    "Ed2kItem\0"
};

const QMetaObject Ed2kItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ed2kItem,
      qt_meta_data_Ed2kItem, 0 }
};

const QMetaObject *Ed2kItem::metaObject() const
{
    return &staticMetaObject;
}

void *Ed2kItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ed2kItem))
	return static_cast<void*>(const_cast< Ed2kItem*>(this));
    return QObject::qt_metacast(_clname);
}

int Ed2kItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VeryCDListPage[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   26,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VeryCDListPage[] = {
    "VeryCDListPage\0\0updated()\0error\0"
    "pageArrived(bool)\0"
};

const QMetaObject VeryCDListPage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VeryCDListPage,
      qt_meta_data_VeryCDListPage, 0 }
};

const QMetaObject *VeryCDListPage::metaObject() const
{
    return &staticMetaObject;
}

void *VeryCDListPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VeryCDListPage))
	return static_cast<void*>(const_cast< VeryCDListPage*>(this));
    return QObject::qt_metacast(_clname);
}

int VeryCDListPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updated(); break;
        case 1: pageArrived((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VeryCDListPage::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_VeryCDDetailPage[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   33,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VeryCDDetailPage[] = {
    "VeryCDDetailPage\0\0loadComplete()\0error\0"
    "pageArrived(bool)\0"
};

const QMetaObject VeryCDDetailPage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VeryCDDetailPage,
      qt_meta_data_VeryCDDetailPage, 0 }
};

const QMetaObject *VeryCDDetailPage::metaObject() const
{
    return &staticMetaObject;
}

void *VeryCDDetailPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VeryCDDetailPage))
	return static_cast<void*>(const_cast< VeryCDDetailPage*>(this));
    return QObject::qt_metacast(_clname);
}

int VeryCDDetailPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadComplete(); break;
        case 1: pageArrived((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VeryCDDetailPage::loadComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_VeryCDGrabber[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_VeryCDGrabber[] = {
    "VeryCDGrabber\0"
};

const QMetaObject VeryCDGrabber::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VeryCDGrabber,
      qt_meta_data_VeryCDGrabber, 0 }
};

const QMetaObject *VeryCDGrabber::metaObject() const
{
    return &staticMetaObject;
}

void *VeryCDGrabber::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VeryCDGrabber))
	return static_cast<void*>(const_cast< VeryCDGrabber*>(this));
    return QObject::qt_metacast(_clname);
}

int VeryCDGrabber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_VeryCDHistory[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_VeryCDHistory[] = {
    "VeryCDHistory\0"
};

const QMetaObject VeryCDHistory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VeryCDHistory,
      qt_meta_data_VeryCDHistory, 0 }
};

const QMetaObject *VeryCDHistory::metaObject() const
{
    return &staticMetaObject;
}

void *VeryCDHistory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VeryCDHistory))
	return static_cast<void*>(const_cast< VeryCDHistory*>(this));
    return QObject::qt_metacast(_clname);
}

int VeryCDHistory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
