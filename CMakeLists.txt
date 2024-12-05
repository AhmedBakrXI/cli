cmake_minimum_required(VERSION 3.16)

project(cli LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort)

add_executable(cli
  main.cpp
  PhysicalLayerManager.h PhysicalLayerManager.cpp
  DataTransferLayerManager.h DataTransferLayerManager.cpp
  Slip.h Slip.cpp
  AbstractCommand.h AbstractCommand.cpp
  CommandManager.h CommandManager.cpp
  CommandRegistry.h CommandRegistry.cpp
  NetworkNodeListCommand.h NetworkNodeListCommand.cpp
  NodeEntryDto.h NodeEntryDto.cpp
  CommandParser.h CommandParser.cpp
  CommandResponseError.h
  NetworkNodeDiscoveryCommand.h NetworkNodeDiscoveryCommand.cpp

)

target_link_libraries(cli Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialPort)

include(GNUInstallDirs)
install(TARGETS cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
