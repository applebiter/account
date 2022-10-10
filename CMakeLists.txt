cmake_minimum_required(VERSION 3.14)

project(account LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql OpenGL)

add_library(account SHARED
    account_global.h
    account.cpp account.h
    authenticator.h authenticator.cpp
    authorizer.h authorizer.cpp
    carrier.h carrier.cpp
    carrierstable.h carrierstable.cpp
    country.h country.cpp
    countriestable.h countriestable.cpp
    device.h device.cpp
    devicestable.h devicestable.cpp
    objectstore.h objectstore.cpp
    preference.h preference.cpp
    preferencestable.h preferencestable.cpp
    profile.h profile.cpp
    profilestable.h profilestable.cpp
    resource.h resource.cpp
    resourcestable.h resourcestable.cpp
    resourcerole.h resourcerole.cpp
    resourcesrolestable.h resourcesrolestable.cpp
    role.h role.cpp
    rolestable.h rolestable.cpp
    state.h state.cpp
    statestable.h statestable.cpp
    user.h user.cpp
    userstable.h userstable.cpp
    zone.h zone.cpp
    zonestable.h zonestable.cpp
)

target_link_libraries(account PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::OpenGL SimpleMail2Qt6 sodium)

target_compile_definitions(account PRIVATE ACCOUNT_LIBRARY)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU"
    OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(_GCC_COMPATIBLE 1)
endif()

# static library option
if (NOT DEFINED sodium_USE_STATIC_LIBS)
    option(sodium_USE_STATIC_LIBS "enable to statically link against sodium" ON)
endif()
if(NOT (sodium_USE_STATIC_LIBS EQUAL sodium_USE_STATIC_LIBS_LAST))
    unset(sodium_LIBRARY CACHE)
    unset(sodium_LIBRARY_DEBUG CACHE)
    unset(sodium_LIBRARY_RELEASE CACHE)
    unset(sodium_DLL_DEBUG CACHE)
    unset(sodium_DLL_RELEASE CACHE)
    set(sodium_USE_STATIC_LIBS_LAST ${sodium_USE_STATIC_LIBS} CACHE INTERNAL "internal change tracking variable")
endif()

