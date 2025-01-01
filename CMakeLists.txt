#设置cmake版本号
cmake_minimum_required(VERSION 3.4.0)

#将cpp版本限制为c++17这个很关键
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#设置工程名称
project(Doit)



set(CMAKE_PREFIX_PATH D:/soft/dev/Qt/6.7.3/msvc2019_64)


#打开全局moc,设置自动生成moc文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#打开全局rcc，非必须，如需打开，注意修改相应的qrc文件名
set(CMAKE_AUTORCC ON)
set(RCC_FILES ./${PROJECT_NAME}/QDlgDoit.qrc)

#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

#设置工程包含当前目录，非必须
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB SRC_FILES "./${PROJECT_NAME}/*.cpp")
FILE(GLOB HEAD_FILES "./${PROJECT_NAME}/*.h")
FILE(GLOB UI_FILES "./${PROJECT_NAME}/*.ui")

#通过Ui文件生成对应的头文件，一定要添加
qt6_wrap_ui(WRAP_FILES ${UI_FILES})



#将ui文件和生成文件整理在一个文件夹中，非必须
source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )




add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES} ${RCC_FILES} ${WRAP_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
