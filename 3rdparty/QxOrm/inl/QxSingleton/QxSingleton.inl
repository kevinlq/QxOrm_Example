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

template <class T> T * QxSingleton<T>::m_pSingleton = NULL;
template <class T> QMutex QxSingleton<T>::m_oMutexSingleton;

template <class T>
T * QxSingleton<T>::getSingleton()
{
   if (m_pSingleton)
      return m_pSingleton;

   IxSingleton::initQxSingletonX();
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingleton) : NULL);
   if (! m_pSingleton) { m_pSingleton = new T(); }

   return m_pSingleton;
}

template <class T>
void QxSingleton<T>::deleteSingleton()
{
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingleton) : NULL);
   if (! m_pSingleton) { return; }

   delete m_pSingleton;
   m_pSingleton = NULL;
}

} // namespace qx
