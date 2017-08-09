project(webserver_mjpeg)

cmake_minimum_required(VERSION 2.8)
if(WIN32)
    # Fix stupid macro problem
    add_definitions(-DNOMINMAX)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_NO_ASYNCRTIMP)
endif(WIN32)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/modules" ${CMAKE_MODULE_PATH})

set(QT5_CMAKES CACHE PATH "QT5 Cmake files (qtbase/lib/cmake)")

set(CMAKE_PREFIX_PATH ${QT5_CMAKES})

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

find_package(Tufao1 REQUIRED)
include_directories(${TUFAO_INCLUDE_DIRS})
message(STATUS "TUFAO [DEBUG]: ${TUFAO_INCLUDE_DIRS}, ${TUFAO_LIB}")



find_package(Qt5 COMPONENTS Core Widgets Gui NetworkAuth Network REQUIRED)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)


###### OpenCV
find_package(OpenCV REQUIRED)


set(SOURCES
	main.cpp
	mainwindow.cpp
	basichandler.cpp
	router.cpp
	pleer.cpp
	VideoHandler.cpp
	TCPServer.cpp
	Worker.cpp
)

set(HEADERS
	mainwindow.h
	basichandler.h
	router.h
	pleer.h
	VideoHandler.h
	TCPServer.h
	Worker.h
)
set(RESOURCES)


source_group("Resource Files" FILES ${RESOURCES})



# RC files need to be processed by Qt wrapper to generate RC sources.
qt5_add_resources(RESOURCES_SOURCES ${RESOURCES})


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
qt5_use_modules(${PROJECT_NAME} Core Network)
target_link_libraries(${PROJECT_NAME} ${TUFAO_LIBRARIES}   ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::NetworkAuth Qt5::Widgets Qt5::Gui)
