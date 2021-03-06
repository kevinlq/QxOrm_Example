#ifndef _QX_MODEL_EXPORT_H_
#define _QX_MODEL_EXPORT_H_

#define MY_SQLLITE_DB_NAME "MySqlLiteDbName"
#define MY_DB_NAME  "DevstoneDBName"


#ifdef _BUILDING_QX_MODEL
#define QX_MODEL_DLL_EXPORT QX_DLL_EXPORT_HELPER
#else // _BUILDING_QX_MODEL
#define QX_MODEL_DLL_EXPORT QX_DLL_IMPORT_HELPER
#endif // _BUILDING_QX_MODEL

#ifdef _BUILDING_QX_MODEL
#define QX_REGISTER_HPP_QX_MODEL     QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX_MODEL    QX_REGISTER_CPP_EXPORT_DLL
#else // _BUILDING_QX_MODEL
#define QX_REGISTER_HPP_QX_MODEL     QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX_MODEL    QX_REGISTER_CPP_IMPORT_DLL

#endif // _BUILDING_QX_MODEL

#endif // _QX_MODEL_EXPORT_H_
