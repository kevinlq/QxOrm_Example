<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/kevinlq/QxOrm_Example">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">QxOrm_Example</h3>

  <p align="center">
    QxOrm 常见用法总结
    <br />
    <a href="https://github.com/kevinlq/QxOrm_Example"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/kevinlq/QxOrm_Example">View Demo</a>
    ·
    <a href="https://github.com/kevinlq/QxOrm_Example/issues">Report Bug</a>
    ·
    <a href="https://github.com/kevinlq/QxOrm_Example/issues">Request Feature</a>
  </p>
</p>


# QxOrm_Example
`QxOrm` 常见用法总结

## 编译说明

`3rdparty` 目录是 `QxOrm`动态库和头文件，动态库需要自己编译，我上传的是 `Qt 5.7 Mingw 5.3`编译的

现在编译 `QxOrm` 库非常容易，新的版本完全脱离了 `boost`的限制，几分钟就可以编译完成


 ## 使用说明
 
- 数据库初始化

传入 JSON 格式参数即可，内部自己进行了封装
```
     QString strDataBaseType     = map.value ("strDatabaseType").toString ();
    QString strHostName         = map.value ("strHostName").toString ();
    int nPort                   = map.value ("nPort").toInt ();
    QString strUserName         = map.value ("strUserName").toString ();
    QString strPwd              = map.value ("strPwd").toString ();
    QString strDataBaseName     = map.value ("strDatabaseName").toString ();
```

目前测试了 `QSQLITE`,`QMYSQL` 数据库均可以正常使用，其它数据库后续测试完再补充

- 创建数据表

```
    template<class T >
    QSqlError createTable(QSqlDatabase * pDatabase = nullptr)
    {
        Q_UNUSED(pDatabase);
        return qx::dao::create_table<T>();
    }
```

- 插入数据

```
    template<class T>
    QSqlError insert(T &t,QSqlDatabase *pDatabase = nullptr)
    {
        return qx::dao::insert(t, pDatabase);
    }
```

其它操作类似，详细封装可以看这个类 `QDaoHelpBase`

```
    QPhoneVo phone;
    phone.m_lID = 1;
    phone.m_strName = "xiao mi";

    QPhoneDao::insertInfo(&phone);
```

## 感谢

在此感谢 `QxOrm` 开源的付出

## 更多内容

如果想阅读了解更多内容，欢迎关注微信公众号：devstone

![thanks](https://github.com/kevinlq/LQFramKit/blob/master/screen/qrcode_for_devstone.png)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/kevinlq/QxOrm_Example.svg?style=for-the-badge
[contributors-url]: https://github.com/kevinlq/QxOrm_Example/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kevinlq/QxOrm_Example.svg?style=for-the-badge
[forks-url]: https://github.com/kevinlq/QxOrm_Example/network/members
[stars-shield]: https://img.shields.io/github/stars/kevinlq/QxOrm_Example.svg?style=for-the-badge
[stars-url]: https://github.com/kevinlq/QxOrm_Example/stargazers
[issues-shield]: https://img.shields.io/github/issues/kevinlq/QxOrm_Example.svg?style=for-the-badge
[issues-url]: https://github.com/kevinlq/QxOrm_Example/issues
[license-shield]: https://img.shields.io/github/license/kevinlq/QxOrm_Example.svg?style=for-the-badge
[license-url]: https://github.com/kevinlq/QxOrm_Example/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/kevinlq


