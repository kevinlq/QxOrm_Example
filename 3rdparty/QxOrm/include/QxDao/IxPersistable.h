/****************************************************************************
**
** https://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _IX_PERSISTABLE_H_
#define _IX_PERSISTABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxPersistable.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface (abstract class) for persistents classes using QX_PERSISTABLE_HPP() and QX_PERSISTABLE_CPP() macros
 */

#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxDao.h>
#include <QxDao/QxSqlSaveMode.h>

#include <QxRegister/QxClass.h>

#include <QxCollection/QxCollection.h>

#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/QxValidatorFct.h>

#include <QxTraits/get_class_name.h>

namespace qx {

class IxPersistableCollection;

/*!
 * \ingroup QxDao
 * \brief qx::IxPersistable : common interface (abstract class) for persistents classes using QX_PERSISTABLE_HPP() and QX_PERSISTABLE_CPP() macros
 *
 * To use this common interface for persistents classes : <br>
 * <b>1-</b> inherit your persistent class from <i>qx::IxPersistable</i> ; <br>
 * <b>2-</b> into your class definition (<i>myClass.h</i> for example), add <i>QX_PERSISTABLE_HPP(myClass)</i> macro ; <br>
 * <b>3-</b> into your class implementation (<i>myClass.cpp</i> for example), add <i>QX_PERSISTABLE_CPP(myClass)</i> macro.
 *
 * <b>Note :</b> for a list of objects (<i>qxFetchAll()</i> method or <i>qxFetchByQuery()</i> method), use <i>qx::QxCollection<type_primary_key, std::shared_ptr<my_type>></i> type.
 * Or just use <i>qx::QxPersistableCollectionHelper<T>::type</i> to retrieve your persistent collection type.
 * A convenient way to fetch a list of objects is to use following static methods <i>qxFetchAll()</i> and <i>qxFetchByQuery()</i> :
 * \code
std::shared_ptr<qx::IxPersistableCollection> lst = qx::IxPersistable::qxFetchAll("myClass");
for (long l = 0; l < lst->_count(); l++)
{ qx::IxPersistable_ptr ptr = lst->_get<qx::IxPersistable_ptr>(l); etc... }
 * \endcode
 */
class QX_DLL_EXPORT IxPersistable
{

public:

   IxPersistable();
   virtual ~IxPersistable();

   /*!
    * \brief Return the number of lines in the table (database) mapped to the current C++ class (registered into QxOrm context) and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxCount(...) execute following SQL query :<br>
    * <i>SELECT COUNT(*) FROM my_table</i> + <i>XXX_JOINS_XXX</i> + <i>WHERE my_query...</i>
    */
   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList()) = 0;

   /*!
    * \brief Return the number of lines in the table (database) mapped to the current C++ class (registered into QxOrm context) and filtered by a user SQL query
    * \param lCount Output parameter with the number of lines in the table associated to the SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxCount(...) execute following SQL query :<br>
    * <i>SELECT COUNT(*) FROM my_table</i> + <i>XXX_JOINS_XXX</i> + <i>WHERE my_query...</i>
    */
   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList()) = 0;

   /*!
    * \brief Fetch current instance (retrieve all its properties) mapped to a table in the database (current instance must have a valid id before to be fetched without error, or pass the id to the first parameter of this method)
    * \param id Unique id to fetch properties from database (if empty, check id of current instance)
    * \param columns List of database table columns (mapped to properties of C++ class) to fetch (if empty, all columns are fetched)
    * \param relation List of relationships keys to fetch (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxFetchById(...) execute following SQL query :<br>
    * <i>SELECT * FROM my_table WHERE my_id = ?</i>
    */
   virtual QSqlError qxFetchById(const QVariant & id = QVariant(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Fetch a list of objects (retrieve all elements and properties associated) of current type (container registered into QxOrm context) mapped to a table in the database
    * \param list Container to fetch all items (retrieve all elements and properties associated); list is cleared before executing SQL query
    * \param columns List of database table columns (mapped to properties of C++ class) to fetch (if empty, all columns are fetched)
    * \param relation List of relationships keys to fetch (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * std::shared_ptr<qx::IxPersistableCollection> lst = p->qxNewPersistableCollection();<br>
    * p->qxFetchAll(& lst, ...) execute following SQL query :<br>
    * <i>SELECT * FROM my_table</i>
    */
   virtual QSqlError qxFetchAll(qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Fetch a list of objects (retrieve all elements and properties associated) of current type (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param list Container to fetch all items (retrieve all elements and properties associated); list is cleared before executing SQL query
    * \param columns List of database table columns (mapped to properties of C++ class) to fetch (if empty, all columns are fetched)
    * \param relation List of relationships keys to fetch (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * std::shared_ptr<qx::IxPersistableCollection> lst = p->qxNewPersistableCollection();<br>
    * p->qxFetchByQuery(my_query, & lst, ...) execute following SQL query :<br>
    * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
    */
   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Insert current instance into database
    * \param relation List of relationships keys to insert in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxInsert(...) execute following SQL query :<br>
    * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
    */
   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Update current instance into database (you can add a user SQL query to the default SQL query builded by QxOrm library)
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param columns List of database table columns (mapped to properties of C++ class) to update (if empty, all columns are updated)
    * \param relation List of relationships keys to update in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxUpdate(...) execute following SQL query :<br>
    * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
    */
   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Insert (if no exist) or update (if already exist) current instance into database
    * \param relation List of relationships keys to insert or update in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \param eSaveRecursiveMode Parameter to call qx::dao::save_with_relation_recursive function
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxSave(...) execute following SQL query :<br>
    * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
    * <br>or (if already exist into database) :<br>
    * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
    */
   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, qx::dao::save_mode::e_save_mode eSaveRecursiveMode = qx::dao::save_mode::e_none) = 0;

   /*!
    * \brief Delete current instance from database
    * \param id Unique id to delete from database (if empty, check id of current instance)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDeleteById(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table WHERE my_id = ?</i><br>
    * <br>
    * If a soft delete behavior is defined for current class, p->qxDeleteById(...) execute following SQL query :<br>
    * <i>UPDATE my_table SET is_deleted='1' WHERE my_id = ?</i>
    */
   virtual QSqlError qxDeleteById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Delete all lines of a table (database) mapped to current C++ class (registered into QxOrm context)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDeleteAll(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table</i><br>
    * <br>
    * If a soft delete behavior is defined for current class, p->qxDeleteAll(...) execute following SQL query :<br>
    * <i>UPDATE my_table SET is_deleted='1'</i>
    */
   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Delete all lines of a table (database) mapped to current C++ class (registered into QxOrm context) and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDeleteByQuery(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i><br>
    * <br>
    * If a soft delete behavior is defined for current class, p->qxDeleteByQuery(...) execute following SQL query :<br>
    * <i>UPDATE my_table SET is_deleted='1'</i> + <i>WHERE my_query...</i>
    */
   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Delete current instance from database
    * \param id Unique id to delete from database (if empty, check id of current instance)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDestroyById(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table WHERE my_id = ?</i><br>
    */
   virtual QSqlError qxDestroyById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Delete all lines of a table (database) mapped to current C++ class (registered into QxOrm context)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDestroyAll(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table</i><br>
    */
   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Delete all lines of a table (database) mapped to current C++ class (registered into QxOrm context) and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxDestroyByQuery(...) execute following SQL query :<br>
    * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i><br>
    */
   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Execute a custom SQL query or a stored procedure, all columns that can be mapped to the instance of type T will be fetched automatically
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Execute a custom SQL query or a stored procedure, all columns that can be mapped to the instance of type T will be fetched automatically
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param list Container to fetch all items (retrieve all elements and properties associated); list is cleared before executing SQL query
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Search if current instance already exists into database
    * \param id Unique id to check into database (if empty, check id of current instance)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
    * \return Return true if element already exists into database; otherwise return false; if an error occurred, qx_bool object contains a description of database error executing SQL query
    *
    * qx::IxPersistable * p = ...;<br>
    * p->qxExist(...) execute following SQL query :<br>
    * <i>SELECT * FROM my_table WHERE my_id = ?</i>
    */
   virtual qx_bool qxExist(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL) = 0;

   /*!
    * \brief Check if current instance is valid or not
    * \param groups List of groups to check (defined into QxValidator module for current class)
    * \return Return list of invalid values (if empty, current instance is valid)
    *
    * For more details about <b>QxValidator</b> module : https://www.qxorm.com/qxorm_en/faq.html#faq_250
    */
   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList()) = 0;

   /*!
    * \brief Create a new collection smart-pointer to fetch a list of items of current class type
    * \param bAsList If true, returns a list (array) of persistent instances instead of key/value hash-map
    * \return Return a new collection smart-pointer to fetch a list of items of current class type
    */
   virtual std::shared_ptr<qx::IxPersistableCollection> qxNewPersistableCollection(bool bAsList = false) const = 0;

   /*!
    * \brief Access to introspection engine (or reflection engine) of QxOrm library
    * \return Return a qx::IxClass pointer to access to introspection engine (or reflection engine) of QxOrm library, and get some informations about current class (properties, methods, etc...)
    */
   virtual qx::IxClass * qxClass() const = 0;

#ifndef _QX_NO_JSON
   virtual QString toJson(const QString & format = QString()) const = 0;
   virtual QJsonValue toJson_(const QString & format = QString()) const = 0;
   virtual qx_bool fromJson(const QString & json, const QString & format = QString()) = 0;
   virtual qx_bool fromJson_(const QJsonValue & json, const QString & format = QString()) = 0;
#endif // _QX_NO_JSON

public:

   static std::shared_ptr<qx::IxPersistableCollection> qxFetchAll(const QString & className, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, bool bAsList = false);
   static std::shared_ptr<qx::IxPersistableCollection> qxFetchByQuery(const QString & className, const qx::QxSqlQuery & query, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, bool bAsList = false);
   static std::shared_ptr<qx::IxPersistableCollection> qxExecuteQuery(const QString & className, qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL, bool bAsList = false);

};

typedef std::shared_ptr<qx::IxPersistable> IxPersistable_ptr;

} // namespace qx

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_ix_persistable<T>::value : return true if T implements qx::IxPersistable interface, otherwise return false
 */
template <typename T>
struct is_ix_persistable
{ enum { value = std::is_base_of<qx::IxPersistable, T>::value }; };

} // namespace trait
} // namespace qx

#ifndef _QX_NO_JSON
#define QX_PERSISTABLE_JSON_HPP(className) \
virtual QString toJson(const QString & format = QString()) const; \
virtual QJsonValue toJson_(const QString & format = QString()) const; \
virtual qx_bool fromJson(const QString & json, const QString & format = QString()); \
virtual qx_bool fromJson_(const QJsonValue & json, const QString & format = QString());
#else // _QX_NO_JSON
#define QX_PERSISTABLE_JSON_HPP(className) /* Nothing */
#endif // _QX_NO_JSON

#define QX_PERSISTABLE_HPP(className) \
public: \
virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList()); \
virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList()); \
virtual QSqlError qxFetchById(const QVariant & id = QVariant(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxFetchAll(qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, qx::dao::save_mode::e_save_mode eSaveRecursiveMode = qx::dao::save_mode::e_none); \
virtual QSqlError qxDeleteById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxDestroyById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL); \
virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, QSqlDatabase * pDatabase = NULL); \
virtual qx_bool qxExist(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL); \
virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList()); \
virtual std::shared_ptr<qx::IxPersistableCollection> qxNewPersistableCollection(bool bAsList = false) const; \
virtual qx::IxClass * qxClass() const; \
QX_PERSISTABLE_JSON_HPP(className)

#ifdef _QX_NO_RTTI
#define QX_PERSISTABLE_CAST_COLLECTION(className) \
if (! list) { return QSqlError(); } \
qx::QxPersistableCollectionHelper< className >::type_coll * list_typed = static_cast< qx::QxPersistableCollectionHelper< className >::type * >(list);
#else // _QX_NO_RTTI
#define QX_PERSISTABLE_CAST_COLLECTION(className) \
if (! list) { return QSqlError(); } \
qx::QxPersistableCollectionHelper< className >::type_coll * list_typed = dynamic_cast< qx::QxPersistableCollectionHelper< className >::type * >(list);
#endif // _QX_NO_RTTI

#ifndef _QX_NO_JSON
#define QX_PERSISTABLE_JSON_CPP(className) \
QString className::toJson(const QString & format) const { return qx::serialization::json::to_string((* this), 1, format); } \
QJsonValue className::toJson_(const QString & format) const { return qx::cvt::to_json((* this), format); } \
qx_bool className::fromJson(const QString & json, const QString & format) { return qx::serialization::json::from_string((* this), json, 1, format); } \
qx_bool className::fromJson_(const QJsonValue & json, const QString & format) { return qx::cvt::from_json(json, (* this), format); }
#else // _QX_NO_JSON
#define QX_PERSISTABLE_JSON_CPP(className) /* Nothing */
#endif // _QX_NO_JSON

#define QX_PERSISTABLE_CPP(className) \
\
long className::qxCount(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase, const QStringList & relation) \
{ \
   if (relation.count() == 0) { return qx::dao::count< className >(query, pDatabase); } \
   else { long lCount(0); qx::dao::count_with_relation< className >(lCount, relation, query, pDatabase); return lCount; } \
} \
\
QSqlError className::qxCount(long & lCount, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase, const QStringList & relation) \
{ \
   if (relation.count() == 0) { return qx::dao::count< className >(lCount, query, pDatabase); } \
   else { return qx::dao::count_with_relation< className >(lCount, relation, query, pDatabase); } \
} \
\
QSqlError className::qxFetchById(const QVariant & id, const QStringList & columns, const QStringList & relation, QSqlDatabase * pDatabase) \
{ \
   if (id.isValid()) \
   { \
      qx::IxDataMemberX * pDataMemberX = qx::QxClass< className >::getSingleton()->getDataMemberX(); \
      qx::IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL); \
      if (! pDataMemberId) { qDebug("[QxOrm] problem with 'qxFetchById()' method : '%s'", "data member id not registered"); qAssert(false); } \
      if (! pDataMemberId) { return QSqlError("[QxOrm] problem with 'qxFetchById()' method : 'data member id not registered'", "", QSqlError::UnknownError); } \
      pDataMemberId->fromVariant(this, id, -1, qx::cvt::context::e_database); \
   } \
   QSqlError err; \
   if (relation.count() == 0) { err = qx::dao::fetch_by_id((* this), pDatabase, columns); } \
   else { err = qx::dao::fetch_by_id_with_relation(relation, (* this), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxFetchAll(qx::IxPersistableCollection * list, const QStringList & columns, const QStringList & relation, QSqlDatabase * pDatabase) \
{ \
   QX_PERSISTABLE_CAST_COLLECTION(className) \
   if (! list_typed) { qDebug("[QxOrm] problem with 'qxFetchAll()' method : '%s'", "dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >"); qAssert(false); } \
   if (! list_typed) { return QSqlError("[QxOrm] problem with 'qxFetchAll()' method : 'dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >'", "", QSqlError::UnknownError); } \
   QSqlError err; \
   if (relation.count() == 0) { err = qx::dao::fetch_all((* list_typed), pDatabase, columns); } \
   else { err = qx::dao::fetch_all_with_relation(relation, (* list_typed), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxPersistableCollection * list, const QStringList & columns, const QStringList & relation, QSqlDatabase * pDatabase) \
{ \
   QX_PERSISTABLE_CAST_COLLECTION(className) \
   if (! list_typed) { qDebug("[QxOrm] problem with 'qxFetchByQuery()' method : '%s'", "dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >"); qAssert(false); } \
   if (! list_typed) { return QSqlError("[QxOrm] problem with 'qxFetchByQuery()' method : 'dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >'", "", QSqlError::UnknownError); } \
   QSqlError err; \
   if (relation.count() == 0) { err = qx::dao::fetch_by_query(query, (* list_typed), pDatabase, columns); } \
   else { err = qx::dao::fetch_by_query_with_relation(relation, query, (* list_typed), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxInsert(const QStringList & relation, QSqlDatabase * pDatabase) \
{ \
   QSqlError err; \
   if (relation.count() == 0) { err = qx::dao::insert((* this), pDatabase); } \
   else { err = qx::dao::insert_with_relation(relation, (* this), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxUpdate(const qx::QxSqlQuery & query, const QStringList & columns, const QStringList & relation, QSqlDatabase * pDatabase) \
{ \
   QSqlError err; \
   if (relation.count() == 0) { err = qx::dao::update_by_query(query, (* this), pDatabase, columns); } \
   else { err = qx::dao::update_by_query_with_relation(relation, query, (* this), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxSave(const QStringList & relation, QSqlDatabase * pDatabase, qx::dao::save_mode::e_save_mode eSaveRecursiveMode) \
{ \
   QSqlError err; \
   if (eSaveRecursiveMode != qx::dao::save_mode::e_none) { err = qx::dao::save_with_relation_recursive((* this), eSaveRecursiveMode, pDatabase); } \
   else if (relation.count() == 0) { err = qx::dao::save((* this), pDatabase); } \
   else { err = qx::dao::save_with_relation(relation, (* this), pDatabase); } \
   return err; \
} \
\
QSqlError className::qxDeleteById(const QVariant & id, QSqlDatabase * pDatabase) \
{ \
   if (id.isValid()) \
   { \
      qx::IxDataMemberX * pDataMemberX = qx::QxClass< className >::getSingleton()->getDataMemberX(); \
      qx::IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL); \
      if (! pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); } \
      if (! pDataMemberId) { return QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); } \
      pDataMemberId->fromVariant(this, id, -1, qx::cvt::context::e_database); \
   } \
   return qx::dao::delete_by_id((* this), pDatabase); \
} \
\
QSqlError className::qxDeleteAll(QSqlDatabase * pDatabase) \
{ \
   return qx::dao::delete_all< className >(pDatabase); \
} \
\
QSqlError className::qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase) \
{ \
   return qx::dao::delete_by_query< className >(query, pDatabase); \
} \
\
QSqlError className::qxDestroyById(const QVariant & id, QSqlDatabase * pDatabase) \
{ \
   if (id.isValid()) \
   { \
      qx::IxDataMemberX * pDataMemberX = qx::QxClass< className >::getSingleton()->getDataMemberX(); \
      qx::IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL); \
      if (! pDataMemberId) { qDebug("[QxOrm] problem with 'qxDestroyById()' method : '%s'", "data member id not registered"); qAssert(false); } \
      if (! pDataMemberId) { return QSqlError("[QxOrm] problem with 'qxDestroyById()' method : 'data member id not registered'", "", QSqlError::UnknownError); } \
      pDataMemberId->fromVariant(this, id, -1, qx::cvt::context::e_database); \
   } \
   return qx::dao::destroy_by_id((* this), pDatabase); \
} \
\
QSqlError className::qxDestroyAll(QSqlDatabase * pDatabase) \
{ \
   return qx::dao::destroy_all< className >(pDatabase); \
} \
\
QSqlError className::qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase) \
{ \
   return qx::dao::destroy_by_query< className >(query, pDatabase); \
} \
\
QSqlError className::qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase) \
{ \
   return qx::dao::execute_query(query, (* this), pDatabase); \
} \
\
QSqlError className::qxExecuteQuery(qx::QxSqlQuery & query, qx::IxPersistableCollection * list, QSqlDatabase * pDatabase) \
{ \
   QX_PERSISTABLE_CAST_COLLECTION(className) \
   if (! list_typed) { qDebug("[QxOrm] problem with 'qxExecuteQuery()' method : '%s'", "dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >"); qAssert(false); } \
   if (! list_typed) { return QSqlError("[QxOrm] problem with 'qxExecuteQuery()' method : 'dynamic_cast failed using collection qx::QxCollection< type_primary_key, std::shared_ptr<type> >'", "", QSqlError::UnknownError); } \
   return qx::dao::execute_query(query, (* list_typed), pDatabase); \
} \
\
qx_bool className::qxExist(const QVariant & id, QSqlDatabase * pDatabase) \
{ \
   if (id.isValid()) \
   { \
      qx::IxDataMemberX * pDataMemberX = qx::QxClass< className >::getSingleton()->getDataMemberX(); \
      qx::IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL); \
      if (! pDataMemberId) { qDebug("[QxOrm] problem with 'qxExist()' method : '%s'", "data member id not registered"); qAssert(false); } \
      if (! pDataMemberId) { return qx_bool(false); } \
      pDataMemberId->fromVariant(this, id, -1, qx::cvt::context::e_database); \
   } \
   return qx::dao::exist((* this), pDatabase); \
} \
\
qx::QxInvalidValueX className::qxValidate(const QStringList & groups) \
{ \
   return qx::validate((* this), groups); \
} \
\
std::shared_ptr<qx::IxPersistableCollection> className::qxNewPersistableCollection(bool bAsList) const \
{ \
   if (bAsList) { std::shared_ptr<qx::IxPersistableCollection> coll = std::make_shared<qx::QxPersistableList< className > >(); return coll; } \
   else { std::shared_ptr<qx::IxPersistableCollection> coll = std::make_shared<qx::QxPersistableCollectionHelper< className >::type>(); return coll; } \
} \
\
qx::IxClass * className::qxClass() const \
{ \
   return qx::QxClass< className >::getSingleton(); \
} \
\
QX_PERSISTABLE_JSON_CPP(className)

QX_REGISTER_CLASS_NAME(qx::IxPersistable)

#include <QxDao/IxPersistableCollection.h>

#endif // _IX_PERSISTABLE_H_
