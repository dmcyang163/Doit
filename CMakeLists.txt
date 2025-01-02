cmake_minimum_required(VERSION 3.4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#工程名称
project(Doit)


#工程包含当前目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(3rdParty_DIR "${PROJECT_SOURCE_DIR}/3rdParty/")

#Qt路径
set(CMAKE_PREFIX_PATH "D:/soft/dev/Qt/6.7.3/msvc2019_64")
MESSAGE(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")

include_directories("${3rdParty_DIR}/zstd-v1.5.6/include")
find_library(zstd_lib NAMES zstd_static PATHS "${3rdParty_DIR}/zstd-v1.5.6/lib")
MESSAGE(STATUS "zstd_lib ${zstd_lib}")
#target_link_libraries(${PROJECT_NAME} ${zstd_lib})
link_libraries(${zstd_lib})


include_directories("${PROJECT_SOURCE_DIR}/Utils")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(RCC_FILES ./${PROJECT_NAME}/QDlgDoit.qrc)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

#源代码文件
file(GLOB UTILS_SRC_FILES "./Utils/*.cpp")
file(GLOB UTILS_HEAD_FILES "./Utils/*.h")
file(GLOB SRC_FILES "./${PROJECT_NAME}/*.cpp")
file(GLOB HEAD_FILES "./${PROJECT_NAME}/*.h")
file(GLOB UI_FILES "./${PROJECT_NAME}/*.ui")


#Ui文件生成对应的头文件
qt6_wrap_ui(WRAP_FILES ${UI_FILES})
#ui文件和生成文件整理在一个文件夹中
source_group("Ui" FILES ${UI_FILES})
source_group("Ui_" FILES ${WRAP_FILES})
source_group("Utils" FILES ${UTILS_SRC_FILES} ${UTILS_HEAD_FILES})

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${HEAD_FILES} ${UTILS_SRC_FILES} ${UTILS_HEAD_FILES} ${RCC_FILES} ${WRAP_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)


if(WIN32)
    if(MSVC)
        option(USE_MP "use multiple" ON)
        option(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP
            "Set The Global Option COMPILE_FLAGS /MP to target." ON)

        if(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP OR USE_MP)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        endif()

        #set(VS_STARTUP_PROJECT ${PROJECT_NAME})
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    endif(MSVC)
endif()