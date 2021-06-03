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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_FetchAll_Generic
{

   static QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "fetch all", new qx::QxSqlQueryBuilder_FetchAll<T>(), (& query));
      if (! dao.isValid()) { return dao.error(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         dao.setSqlColumns(columns);
         qx::dao::on_before_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         QString json = qx::serialization::json::to_string(t, 1, "mongodb:only_id");
         qx::dao::mongodb::QxMongoDB_Helper::findOne((& dao), dao.getDataMemberX()->getClass(), json, (& query)); if (! dao.isValid()) { return dao.error(); }

         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         QString ctx = QString("mongodb") + ((columns.count() > 0) ? (QString(":columns{,") + columns.join(",") + QString(",}")) : QString());
         qx::serialization::json::from_string(t, json, 1, ctx);
         qx::dao::on_after_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }

      if (dao.nextRecord())
      {
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         qx::dao::on_before_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         qx::dao::detail::QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, dao.query(), dao.builder(), columns);
         qx::dao::on_after_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
      }

      return dao.error();
   }

};

#ifdef _QX_ENABLE_MONGODB
template <class T>
struct QxDao_FetchAll_MongoDB_Fetcher : public qx::dao::mongodb::QxMongoDB_Fetcher
{

   T & m_t;
   qx::dao::detail::QxDao_Helper_Container<T> & m_dao;

   QxDao_FetchAll_MongoDB_Fetcher(T & t, qx::dao::detail::QxDao_Helper_Container<T> & dao) : qx::dao::mongodb::QxMongoDB_Fetcher(), m_t(t), m_dao(dao) { ; }
   virtual ~QxDao_FetchAll_MongoDB_Fetcher() { ; }

   virtual void fetch(const QString & json)
   {
      typedef typename qx::trait::generic_container<T>::type_item type_item;
      typedef typename type_item::type_value_qx type_value_qx;
      type_item item = qx::trait::generic_container<T>::createItem();
      type_value_qx & item_val = item.value_qx();
      qx::IxDataMember * pId = m_dao.getDataId();
      QStringList columns = m_dao.getSqlColumns();

      if (json.isEmpty()) { return; }
      qx::dao::detail::IxDao_Timer timer((& m_dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
      qx::dao::on_before_fetch<type_value_qx>((& item_val), (& m_dao)); if (! m_dao.isValid()) { return; }
      QString ctx = QString("mongodb") + ((columns.count() > 0) ? (QString(":columns{,") + columns.join(",") + QString(",}")) : QString());
      qx::serialization::json::from_string(item_val, json, 1, ctx);
      for (int i = 0; i < (pId ? pId->getNameCount() : 0); i++)
      {
         QVariant id = pId->toVariant((& item_val), "", i, qx::cvt::context::e_database);
         qx::cvt::from_variant(id, item.key(), "", i, qx::cvt::context::e_database);
      }
      qx::dao::on_after_fetch<type_value_qx>((& item_val), (& m_dao)); if (! m_dao.isValid()) { return; }
      qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      qx::trait::generic_container<T>::insertItem(m_t, item);
   }

};
#endif // _QX_ENABLE_MONGODB

template <class T>
struct QxDao_FetchAll_Container
{

   static QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      qx::trait::generic_container<T>::clear(t);
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "fetch all", new qx::QxSqlQueryBuilder_FetchAll<type_item>(), (& query));
      if (! dao.isValid()) { return dao.error(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         dao.setSqlColumns(columns);
         QStringList & itemsAsJson = dao.itemsAsJson();
         QxDao_FetchAll_MongoDB_Fetcher<T> fetcher(t, dao);
         qx::dao::mongodb::QxMongoDB_Helper::findMany((& dao), dao.getDataMemberX()->getClass(), itemsAsJson, (& query), (& fetcher));
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      dao.setSqlColumns(columns);

      bool bSize = (dao.hasFeature(QSqlDriver::QuerySize) && (dao.query().size() > 0));
      if (bSize) { qx::trait::generic_container<T>::reserve(t, dao.query().size()); }
      while (dao.nextRecord()) { insertNewItem(t, dao); if (! dao.isValid()) { return dao.error(); } }
      if (bSize) { qAssert(qx::trait::generic_container<T>::size(t) == static_cast<long>(dao.query().size())); }

      return dao.error();
   }

private:

   static void insertNewItem(T & t, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      typedef typename qx::trait::generic_container<T>::type_item type_item;
      typedef typename type_item::type_value_qx type_value_qx;
      type_item item = qx::trait::generic_container<T>::createItem();
      type_value_qx & item_val = item.value_qx();
      qx::IxDataMember * pId = dao.getDataId();
      QStringList columns = dao.getSqlColumns();
      bool isDistinct = dao.qxQuery().isDistinct();

      qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
      if (pId && (! isDistinct)) { for (int i = 0; i < pId->getNameCount(); i++) { QVariant v = dao.query().value(i); qx::cvt::from_variant(v, item.key(), "", i, qx::cvt::context::e_database); } }
      qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
      qx::dao::detail::QxSqlQueryHelper_FetchAll<type_value_qx>::resolveOutput(item_val, dao.query(), dao.builder(), columns);
      qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
      qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      qx::trait::generic_container<T>::insertItem(t, item);
   }

};

template <class T>
struct QxDao_FetchAll_Ptr
{

   static inline QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   { return (t ? qx::dao::fetch_by_query(query, (* t), pDatabase, columns) : QSqlError()); }

};

template <class T>
struct QxDao_FetchAll
{

   static inline QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_FetchAll_Ptr<T>, qx::dao::detail::QxDao_FetchAll_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_FetchAll_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_FetchAll_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::fetchAll(query, t, pDatabase, columns);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
