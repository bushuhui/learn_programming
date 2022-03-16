# Install qt5 for Linux
#   sudo apt-get install qt5-doc qt5-default libqt5opengl5 libqt5svg5-dev

set(CMAKE_PREFIX_PATH D:/Qt/Qt5.9.4/5.9.4/msvc2017_64) # enable this line to decide which version of Qt to find
#set(CMAKE_PREFIX_PATH /home/bushuhui/pis/RTMapper3/dev_soft/third_party/qt-4.8.5_install)

find_package(Qt5)

if(QT4_FOUND)
    set(QT_INCLUDES ${QT_INCLUDE_DIR})
    set(QT_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtNetwork Qt4::QtOpenGL Qt4::QtSvg Qt4::QtSql Qt4::QtXml)
    set(QT_FOUND true)
    set(QT4_FOUND true)
    set(QT_VERSION 4)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets Network OpenGL Svg Sql Xml REQUIRED)
    set(QT_INCLUDES ${_qt5Core_install_prefix}/include)
    set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::OpenGL Qt5::Svg Qt5::Sql Qt5::Xml)
    set(QT_FOUND true)
    set(QT5_FOUND true)
    set(QT_VERSION "${PACKAGE_VERSION}")
endif()
