cmake_minimum_required(VERSION 3.5)

project(case_converter VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Add build directory to include path

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(include)

file(GLOB SOURCES src/*.cpp src/*.ui)
file(GLOB HEADERS include/*.h)
set(RESOURCES res/resources.qrc) # Set Qt resources

set(APPLICATION_NAME "Case Converter")
add_compile_definitions(APPLICATION_NAME="${APPLICATION_NAME}")

# Settings for Windows
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_EXE_LINKER_FLAGS "-static") # Link statically all the libraries to create a standalone executable

    add_compile_definitions(APP_NAME="${PROJECT_NAME}") # Name in Windows properties
    configure_file(version.rc.in version.rc) # Set VERSIONINFO file

    # Set Windows resources
    enable_language("RC")
    set(WIN32_RESOURCES res/resources.rc ${PROJECT_BINARY_DIR}/version.rc)
endif()

# Settings for Mac OS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Set Mac OS resources
    set(MACOSX_BUNDLE_ICON_FILE case_converter_icon.icns)
    set(MACOSX_RESOURCES res/case_converter_icon.icns)
    set_source_files_properties(${MACOSX_RESOURCES} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )

    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0") # Set minimum target to Mac OS Big Sur
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES} ${WIN32_RESOURCES} ${MACOSX_RESOURCES})

configure_file(config.h.in config.h) # Set config header file

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${APPLICATION_NAME}
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME ${APPLICATION_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
)
