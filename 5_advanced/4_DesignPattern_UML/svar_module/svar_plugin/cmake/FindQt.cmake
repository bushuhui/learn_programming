#find_package(Qt4)

if(QT4_FOUND)
    set(QT_INCLUDES ${QT_INCLUDE_DIR})
    set(QT_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtNetwork Qt4::QtOpenGL Qt4::QtSvg Qt4::QtSql Qt4::QtXml)
    set(QT_FOUND true)
    set(QT4_FOUND true)
    set(QT_VERSION 4)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets Network OpenGL Svg Sql Xml)
    set(QT_INCLUDES ${_qt5Core_install_prefix}/include)
    set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::OpenGL Qt5::Svg Qt5::Sql Qt5::Xml)
    set(QT_FOUND true)
    set(QT5_FOUND true)
    set(QT_VERSION "${PACKAGE_VERSION}")
endif()
