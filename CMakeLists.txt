cmake_minimum_required(VERSION 3.17)
project(a89_917OctaviaSuceava)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

include_directories(domain)
include_directories(gui_admin)
include_directories(gui_user)
include_directories(main)
include_directories(repository)
include_directories(service)
include_directories(validators)

add_executable(a89_917OctaviaSuceava
        domain/domain.cpp
        domain/domain.h
        gui_admin/gui_admin.cpp
        gui_admin/gui_admin.h
        gui_user/gui_user.cpp
        gui_user/gui_user.h
        main/mainnn.cpp
        main/mainwindow.cpp
        main/mainwindow.h
        repository/file_repo.cpp
        repository/file_repo.h
        repository/repository.cpp
        repository/repository.h
        service/service.cpp
        service/service.h
        validators/validators.cpp
        validators/validators.h)

target_link_libraries(a89_917OctaviaSuceava Qt5::Core)
target_link_libraries(a89_917OctaviaSuceava Qt5::Widgets)
target_link_libraries(a89_917OctaviaSuceava Qt5::Quick)
