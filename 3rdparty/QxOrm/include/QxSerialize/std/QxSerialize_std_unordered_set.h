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
#ifndef _QX_SERIALIZATION_STD_UNORDERED_SET_H_
#define _QX_SERIALIZATION_STD_UNORDERED_SET_H_

#ifdef _MSC_VER
#pragma once
#endif

#if (BOOST_VERSION >= 105600)

#include <boost/serialization/unordered_set.hpp>

#else // (BOOST_VERSION >= 105600)

#include <unordered_set>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost {
namespace serialization {

template <class Archive, class Key>
inline void save(Archive & ar, const std::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::save_collection< Archive, std::unordered_set<Key> >(ar, t);
}

template <class Archive, class Key>
inline void load(Archive & ar, std::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::load_collection< Archive, std::unordered_set<Key>,
      boost::serialization::stl::archive_input_set< Archive, std::unordered_set<Key> >,
      boost::serialization::stl::no_reserve_imp<std::unordered_set< Key > > >(ar, t);
}

template <class Archive, class Key>
inline void serialize(Archive & ar, std::unordered_set<Key> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

template <class Archive, class Key>
inline void save(Archive & ar, const std::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::save_collection< Archive, std::unordered_multiset<Key> >(ar, t);
}

template <class Archive, class Key>
inline void load(Archive & ar, std::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
#if (BOOST_VERSION >= 104200)
   boost::serialization::stl::load_collection< Archive, std::unordered_multiset<Key>,
      boost::serialization::stl::archive_input_set< Archive, std::unordered_multiset<Key> >,
      boost::serialization::stl::no_reserve_imp< std::unordered_multiset<Key> > >(ar, t);
#else // (BOOST_VERSION >= 104200)
   boost::serialization::stl::load_collection< Archive, std::unordered_multiset<Key>,
      boost::serialization::stl::archive_input_multiset< Archive, std::unordered_multiset<Key> >,
      boost::serialization::stl::no_reserve_imp< std::unordered_multiset<Key> > >(ar, t);
#endif // (BOOST_VERSION >= 104200)
}

template <class Archive, class Key>
inline void serialize(Archive & ar, std::unordered_multiset<Key> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // (BOOST_VERSION >= 105600)
#endif // _QX_SERIALIZATION_STD_UNORDERED_SET_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
