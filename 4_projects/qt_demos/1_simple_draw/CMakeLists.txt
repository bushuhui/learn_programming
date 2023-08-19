cmake_minimum_required(VERSION 3.10)
project(simple_draw)

# 开启自动编译
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 匹配文件
file(GLOB SOURCE_FILE ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB RESOURCE_FILE ${PROJECT_SOURCE_DIR}/*.qrc)

# 链接可执行文件
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${RESOURCE_FILE})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
