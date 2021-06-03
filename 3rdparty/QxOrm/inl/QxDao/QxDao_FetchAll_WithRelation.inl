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
struct QxDao_FetchAll_WithRelation_Generic
{

   typedef qx::dao::detail::QxDao_Helper<T> type_dao_helper;
   typedef qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<T> type_query_helper;

   static QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      type_dao_helper dao(t, pDatabase, "fetch all with relation", new qx::QxSqlQueryBuilder_FetchAll_WithRelation<T>(), (& query));
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         qx::dao::on_before_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         QString json = qx::serialization::json::to_string(t, 1, "mongodb:only_id");
         qx::dao::mongodb::QxMongoDB_Helper::findOne((& dao), dao.getDataMemberX()->getClass(), json, (& query)); if (! dao.isValid()) { return dao.error(); }

         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         qx::serialization::json::from_string(t, json, 1, "mongodb");
         qx::dao::on_after_fetch<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      QStringList columns;
      QString sql = dao.builder().buildSql(columns, dao.getSqlRelationLinked()).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }

      {
         qx::dao::on_before_fetch<T>((& t), (& dao));
         if (! dao.isValid()) { return dao.error(); }
         if (dao.getCartesianProduct()) { fetchAll_Complex(t, dao); }
         else { fetchAll_Simple(t, dao); }
         if (! dao.isValid()) { return dao.error(); }
         qx::dao::on_after_fetch<T>((& t), (& dao));
      }

      return dao.error();
   }

private:

   static inline void fetchAll_Simple(T & t, type_dao_helper & dao)
   {
      if (! dao.nextRecord()) { return; }
      qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
      type_query_helper::resolveOutput(dao.getSqlRelationLinked(), t, dao.query(), dao.builder());
   }

   static inline void fetchAll_Complex(T & t, type_dao_helper & dao)
   {
      while (dao.nextRecord())
      {
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         type_query_helper::resolveOutput(dao.getSqlRelationLinked(), t, dao.query(), dao.builder());
         if (! dao.isValid()) { return; }
      }
   }

};

#ifdef _QX_ENABLE_MONGODB
template <class T>
struct QxDao_FetchAll_WithRelation_MongoDB_Fetcher : public qx::dao::mongodb::QxMongoDB_Fetcher
{

   typedef qx::dao::detail::QxDao_Helper_Container<T> type_dao_helper;
   typedef qx::trait::generic_container<T> type_generic_container;
   typedef typename type_generic_container::type_item type_item;
   typedef typename type_item::type_value_qx type_value_qx;
   typedef typename type_item::type_value type_value;

   T & m_t;
   type_dao_helper & m_dao;

   QxDao_FetchAll_WithRelation_MongoDB_Fetcher(T & t, type_dao_helper & dao) : qx::dao::mongodb::QxMongoDB_Fetcher(), m_t(t), m_dao(dao) { ; }
   virtual ~QxDao_FetchAll_WithRelation_MongoDB_Fetcher() { ; }

   virtual void fetch(const QString & json)
   { fetcherHelper<type_item::is_value_pointer, 0>::insertNewItem(m_t, m_dao, json); }

private:

   template <bool bIsPointer /* = false */, int dummy>
   struct fetcherHelper
   {
      static void insertNewItem(T & t, type_dao_helper & dao, const QString & json)
      {
         type_item item = type_generic_container::createItem();
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);

         if (json.isEmpty()) { return; }
         type_value_qx & item_val_tmp = item.value_qx();
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         qx::serialization::json::from_string(item_val_tmp, json, 1, "mongodb:columns{,_id," + pId->getKey() + ",}");
         for (int i = 0; i < (pId ? pId->getNameCount() : 0); i++)
         {
            QVariant id = pId->toVariant((& item_val_tmp), "", i, qx::cvt::context::e_database);
            qx::cvt::from_variant(id, item.key(), "", i, qx::cvt::context::e_database);
         }
         type_value * pValue = type_generic_container::insertItem(t, item);
         type_value_qx & item_val = (pValue ? (* static_cast<type_value_qx *>(pValue)) : item.value_qx());
         qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         qx::serialization::json::from_string(item_val, json, 1, "mongodb");
         qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      }
   };

   template <int dummy>
   struct fetcherHelper<true, dummy>
   {
      static void insertNewItem(T & t, type_dao_helper & dao, const QString & json)
      {
         type_item item = type_generic_container::createItem();
         type_value_qx & item_val = item.value_qx();
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);

         if (json.isEmpty()) { return; }
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         qx::serialization::json::from_string(item_val, json, 1, "mongodb");
         for (int i = 0; i < (pId ? pId->getNameCount() : 0); i++)
         {
            QVariant id = pId->toVariant((& item_val), "", i, qx::cvt::context::e_database);
            qx::cvt::from_variant(id, item.key(), "", i, qx::cvt::context::e_database);
         }
         qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
         qx::trait::generic_container<T>::insertItem(t, item);
      }
   };

};
#endif // _QX_ENABLE_MONGODB

template <class T>
struct QxDao_FetchAll_WithRelation_Container
{

   typedef qx::dao::detail::QxDao_Helper_Container<T> type_dao_helper;
   typedef qx::dao::detail::QxDao_FetchAll_WithRelation_Container<T> type_this;
   typedef qx::trait::generic_container<T> type_generic_container;
   typedef typename type_generic_container::type_item type_item;
   typedef typename type_item::type_value_qx type_value_qx;
   typedef typename type_item::type_value type_value;
   typedef qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<type_value_qx> type_query_helper;

   static QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      type_generic_container::clear(t);
      type_dao_helper dao(t, pDatabase, "fetch all with relation", new qx::QxSqlQueryBuilder_FetchAll_WithRelation<type_value_qx>(), (& query));
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         QStringList & itemsAsJson = dao.itemsAsJson();
         QxDao_FetchAll_WithRelation_MongoDB_Fetcher<T> fetcher(t, dao);
         qx::dao::mongodb::QxMongoDB_Helper::findMany((& dao), dao.getDataMemberX()->getClass(), itemsAsJson, (& query), (& fetcher));
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      bool bComplex = dao.getCartesianProduct(); QVariant vId; QStringList columns;
      QString sql = dao.builder().buildSql(columns, dao.getSqlRelationLinked()).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      bool bSize = (dao.hasFeature(QSqlDriver::QuerySize) && (dao.query().size() > 0));
      if (bSize) { type_generic_container::reserve(t, dao.query().size()); }
      bool isDistinct = dao.qxQuery().isDistinct();

      while (dao.nextRecord())
      {
         if (! dao.isValid()) { return dao.error(); }
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
         if (pId && (! isDistinct)) { QString sId; for (int i = 0; i < pId->getNameCount(); i++) { sId += dao.query().value(i).toString() + "|"; }; vId = sId; }
         void * pItemTmp = (bComplex ? dao.builder().existIdX(0, vId, vId) : NULL);
         if (! pItemTmp) { insertHelper<type_item::is_value_pointer, 0>::insertNewItem(t, dao); continue; }
         type_value_qx * pItem = static_cast<type_value_qx *>(pItemTmp);
         type_query_helper::resolveOutput(dao.getSqlRelationLinked(), (* pItem), dao.query(), dao.builder());
      }

      if (bSize) { type_generic_container::reserve(t, type_generic_container::size(t)); }
      return dao.error();
   }

private:

   template <bool bIsPointer /* = false */, int dummy>
   struct insertHelper
   {
      static void insertNewItem(T & t, type_dao_helper & dao)
      {
         type_item item = type_generic_container::createItem();
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
         bool isDistinct = dao.qxQuery().isDistinct();

         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         if (pId && (! isDistinct)) { for (int i = 0; i < pId->getNameCount(); i++) { QVariant v = dao.query().value(i); qx::cvt::from_variant(v, item.key(), "", i, qx::cvt::context::e_database); } }
         type_value * pValue = type_generic_container::insertItem(t, item);
         type_value_qx & item_val = (pValue ? (* static_cast<type_value_qx *>(pValue)) : item.value_qx());
         qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         type_query_helper::resolveOutput(dao.getSqlRelationLinked(), item_val, dao.query(), dao.builder()); if (! dao.isValid()) { return; }
         qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      }
   };

   template <int dummy>
   struct insertHelper<true, dummy>
   {
      static void insertNewItem(T & t, type_dao_helper & dao)
      {
         type_item item = type_generic_container::createItem();
         type_value_qx & item_val = item.value_qx();
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
         bool isDistinct = dao.qxQuery().isDistinct();

         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_build_instance);
         if (pId && (! isDistinct)) { for (int i = 0; i < pId->getNameCount(); i++) { QVariant v = dao.query().value(i); qx::cvt::from_variant(v, item.key(), "", i, qx::cvt::context::e_database); } }
         qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         type_query_helper::resolveOutput(dao.getSqlRelationLinked(), item_val, dao.query(), dao.builder()); if (! dao.isValid()) { return; }
         qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
         type_generic_container::insertItem(t, item);
         qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      }
   };

};

template <class T>
struct QxDao_FetchAll_WithRelation_Ptr
{

   static inline QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   { return (t ? qx::dao::fetch_by_query_with_relation(relation, query, (* t), pDatabase) : QSqlError()); }

};

template <class T>
struct QxDao_FetchAll_WithRelation
{

   static inline QSqlError fetchAll(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      QStringList lst;
      if (! relation.isEmpty()) { lst = relation.split("|"); }
      return QxDao_FetchAll_WithRelation<T>::fetchAll(lst, query, t, pDatabase);
   }

   static inline QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Ptr<T>, qx::dao::detail::QxDao_FetchAll_WithRelation_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::fetchAll(relation, query, t, pDatabase);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
