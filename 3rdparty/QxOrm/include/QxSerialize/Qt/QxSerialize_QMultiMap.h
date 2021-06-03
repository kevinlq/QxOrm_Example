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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _QX_SERIALIZE_QMULTIMAP_H_
#define _QX_SERIALIZE_QMULTIMAP_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>

#include <QtCore/qmap.h>

namespace boost {
namespace serialization {

template <class Archive, typename Key, typename Value>
inline void save(Archive & ar, const QMultiMap<Key, Value> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = t.count();
   ar << boost::serialization::make_nvp("count", lCount);

   QMapIterator<Key, Value> itr(t);
   while (itr.hasNext())
   {
      itr.next();
      std::pair<Key, Value> pair_key_value = std::make_pair(itr.key(), itr.value());
      ar << boost::serialization::make_nvp("item", pair_key_value);
   }
}

template <class Archive, typename Key, typename Value>
inline void load(Archive & ar, QMultiMap<Key, Value> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = 0;
   ar >> boost::serialization::make_nvp("count", lCount);

   t.clear();
   std::pair<Key, Value> pair_key_value;

   for (long l = 0; l < lCount; l++)
   {
      ar >> boost::serialization::make_nvp("item", pair_key_value);
      t.insert(pair_key_value.first, pair_key_value.second);
   }
}

template <class Archive, typename Key, typename Value>
inline void serialize(Archive & ar, QMultiMap<Key, Value> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QMULTIMAP_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
