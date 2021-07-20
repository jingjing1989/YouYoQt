cmake_minimum_required(VERSION 3.5)

project(youyoRoot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Append the QT dir to CMAKE_PREFIX_PATH
###############################################################
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_SDK_DIR})
###############################################################

# Include the local config files
###############################################################
include(config.cmake)
###############################################################

configure_file (
  "${PROJECT_SOURCE_DIR}/QCef/QCefWidget/Include/QCefVersion.h.in"
  "${PROJECT_SOURCE_DIR}/QCef/QCefWidget/Include/QCefVersion.h"
)
configure_file (
  "${PROJECT_SOURCE_DIR}/QCef/QCefWidget/Include/QCefUserDefined.h.in"
  "${PROJECT_SOURCE_DIR}/QCef/QCefWidget/Include/QCefUserDefined.h"
)

#--------cef---------------------------------------------------
set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CEFWrapper")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
# Load the CEF configuration.Execute FindCEF.cmake which must exist in CMAKE_MODULE_PATH.
find_package(CEF REQUIRED)
# ceflib for C++ wrapper
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH})
#给cef俩重要的变量起个名字
set(CEF_LIB_FILE "${CEF_BINARY_DIR}/libcef.lib")
set(CEF_DLL_WRAPPER "libcef_dll_wrapper")
# qt cefWrapper outPut
set(QCEF_WIDGET_SDK_OUT ${BUILD_PATH}/${QCEF_WIDGET_DLL})
set(QCEF_WIDGET_SDK_BIN_OUT ${QCEF_WIDGET_SDK_OUT}/bin)
set(QCEF_WIDGET_SDK_LIB_OUT ${QCEF_WIDGET_SDK_OUT}/lib)
set(QCEF_WIDGET_SDK_INC_OUT ${QCEF_WIDGET_SDK_OUT}/include)

include_directories(${CEF_ROOT} QCef/QCefProto)

PRINT_CEF_CONFIG()

# cefsimple cefOriginExample
#add_subdirectory(cefsimple)

add_subdirectory(QCef/QCefWing)

add_subdirectory(QCef/QCefWidget)

# Add demo
add_subdirectory(test/QCefWidgetTest)
#--------cef-------------------------------------------------------

#--------QT项--------
add_subdirectory(src)
