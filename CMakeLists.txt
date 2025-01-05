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

#zstd
include_directories("${3rdParty_DIR}/zstd-v1.5.6/include")
find_library(zstd_static_lib NAMES zstd_static PATHS "${3rdParty_DIR}/zstd-v1.5.6/lib")
MESSAGE(STATUS "zstd_static_lib ${zstd_static_lib}")
#target_link_libraries(${PROJECT_NAME} ${zstd_lib})
link_libraries(${zstd_static_lib})

#zeromq
include_directories("${3rdParty_DIR}/zeromq-4.3.5/include")
find_library(zmq_static_lib NAMES libzmq-v142-mt-4_3_5 PATHS "${3rdParty_DIR}/zeromq-4.3.5/lib")
MESSAGE(STATUS "zmq_static_lib ${zmq_static_lib}")
#link_libraries(${zmq_static_lib})


# 链接 ZeroMQ 库
#target_link_libraries(my_zmq_app ${ZMQ_LIBRARY})



#opencv
set(OpenCV_DIR "D:/soft/dev/opencv-4.10.0")
find_package(OpenCV REQUIRED)
# 包含 OpenCV 头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

#inc
include_directories("${PROJECT_SOURCE_DIR}/utils" "${PROJECT_SOURCE_DIR}/algo" "${PROJECT_SOURCE_DIR}/net")




set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(RCC_FILES ./${PROJECT_NAME}/QDlgDoit.qrc)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

file(GLOB NET_SRC_FILES "./net/*.cpp")
file(GLOB NET_H_FILES "./net/*.h")
file(GLOB ALGO_SRC_FILES "./algo/*.cpp")
file(GLOB ALGO_H_FILES "./algo/*.h")
file(GLOB UTILS_SRC_FILES "./utils/*.cpp")
file(GLOB UTILS_H_FILES "./utils/*.h")
file(GLOB SRC_FILES "./${PROJECT_NAME}/*.cpp")
file(GLOB H_FILES "./${PROJECT_NAME}/*.h")
file(GLOB UI_FILES "./${PROJECT_NAME}/*.ui")


#Ui文件生成对应的头文件
qt6_wrap_ui(WRAP_FILES ${UI_FILES})
#ui文件和生成文件整理在一个文件夹中
source_group("Ui" FILES ${UI_FILES})
source_group("Ui_" FILES ${WRAP_FILES})
source_group("Utils" FILES ${UTILS_SRC_FILES} ${UTILS_H_FILES})
source_group("Algo" FILES ${ALGO_SRC_FILES} ${ALGO_H_FILES})
source_group("Net" FILES ${NET_SRC_FILES} ${NET_H_FILES})



add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${H_FILES} ${ALGO_SRC_FILES} ${ALGO_H_FILES} ${NET_SRC_FILES} ${NET_H_FILES} ${UTILS_SRC_FILES} ${UTILS_H_FILES} ${RCC_FILES} ${WRAP_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets ${OpenCV_LIBS} ${zmq_static_lib})


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