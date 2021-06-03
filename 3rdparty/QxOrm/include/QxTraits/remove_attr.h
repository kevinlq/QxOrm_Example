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

#ifndef _QX_REMOVE_ATTR_H_
#define _QX_REMOVE_ATTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file remove_attr.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::remove_attr<T>::type : return a type without pointer, const, reference and/or volatile attributes
 */

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::remove_attr<T>::type : return a type without pointer, const, reference and/or volatile attributes
 */
template <typename T, bool bRemovePtr = true, bool bRemoveConst = true, bool bRemoveRef = true, bool bRemoveVolatile = true>
class remove_attr
{

private:

   typedef typename std::conditional<bRemovePtr, typename std::remove_pointer<T>::type, T>::type type_1;
   typedef typename std::conditional<bRemoveConst, typename std::remove_const<type_1>::type, type_1>::type type_2;
   typedef typename std::conditional<bRemoveRef, typename std::remove_reference<type_2>::type, type_2>::type type_3;
   typedef typename std::conditional<bRemoveVolatile, typename std::remove_volatile<type_3>::type, type_3>::type type_4;

public:

   typedef type_4 type;

};

} // namespace trait
} // namespace qx

#endif // _QX_REMOVE_ATTR_H_
