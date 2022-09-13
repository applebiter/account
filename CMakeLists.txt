cmake_minimum_required(VERSION 3.14)

project(account LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_library(account SHARED
  account_global.h
  account.cpp account.h
  authenticate.h authenticate.cpp
  authorize.h authorize.cpp
  carrier.h carrier.cpp
  carrierstable.h carrierstable.cpp
  country.h country.cpp
  countriestable.h countriestable.cpp
  device.h device.cpp
  devicestable.h devicestable.cpp
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

target_link_libraries(account PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

target_compile_definitions(account PRIVATE ACCOUNT_LIBRARY)
