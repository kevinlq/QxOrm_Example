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
#ifndef _QX_EXPORT_DLL_BOOST_ARCHIVE_H_
#define _QX_EXPORT_DLL_BOOST_ARCHIVE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#if _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON
#if (! _QX_BUILDING_QX_ORM)

#include <QxSerialize/boost/QxImportDllBoostArchive.h>

#if (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::archive_serializer_map, Archive)
#else // (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION > 103800)

#if (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_HPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_serializer_map, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_serializer_map, ArchiveOut)
#else // (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_HPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_pointer_iserializer, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_pointer_oserializer, ArchiveOut)
#endif // (BOOST_VERSION > 103800)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::save_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::save_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::save_non_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::save_non_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::save_enum_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::save_enum_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::save_array_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::save_array_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::load_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::load_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::load_non_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::load_non_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::load_enum_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::load_enum_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::archive::detail::load_array_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::load_array_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_HPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_IARCHIVE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::interface_iarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::interface_iarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_OARCHIVE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::interface_oarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::interface_oarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_IARCHIVE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::common_iarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::common_iarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_OARCHIVE_HPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::common_oarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::archive::detail::common_oarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_IARCHIVE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_OARCHIVE_HPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_IARCHIVE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_OARCHIVE_HPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_HPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_HPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_HPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_HPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_HPP(ArchiveIn, ArchiveOut)

#if _QX_SERIALIZE_POLYMORPHIC
   QX_BOOST_EXPORT_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_HPP(boost::archive::polymorphic_binary_iarchive, boost::archive::polymorphic_binary_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_HPP(boost::archive::polymorphic_text_iarchive, boost::archive::polymorphic_text_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_HPP(boost::archive::polymorphic_xml_iarchive, boost::archive::polymorphic_xml_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_HPP(eos::portable_iarchive, eos::portable_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_BOOST_EXPORT_ARCHIVE_ALL_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#if _QX_USE_SERIALIZE_POLYMORPHIC_PATCH
namespace boost { namespace archive {
template <>
inline void xml_iarchive_impl<naked_xml_iarchive>::load(std::basic_string< unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> > & s)
{ Q_UNUSED(s); qAssert(false); }
template <>
inline void xml_oarchive_impl<xml_oarchive>::save(std::basic_string< unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> > const & s)
{ Q_UNUSED(s); qAssert(false); }
} } // namespace boost::archive
#endif // _QX_USE_SERIALIZE_POLYMORPHIC_PATCH

#endif // (! _QX_BUILDING_QX_ORM)
#endif // _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON
#endif // _QX_EXPORT_DLL_BOOST_ARCHIVE_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
