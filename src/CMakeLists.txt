project(youyo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(
  ${QCEF_WIDGET_SDK_INC_OUT}
)

find_package(Qt5 COMPONENTS Core Widgets Gui Charts Network REQUIRED )


FILE(GLOB_RECURSE HEADER_FILES "*.h")
FILE(GLOB_RECURSE SRC_FILES "*.cpp")
FILE(GLOB_RECURSE UI_FILES "*.ui")
FILE(GLOB_RECURSE RESOURCE_FILES "*.qrc")
FILE(GLOB_RECURSE WIN_RC "*.rc")

# 告诉IDE怎么看项目文件结构
source_group("" FILES ${HEADER_FILES} ${SRC_FILES} ${UI_FILES} ${RESOURCE_FILES} ${WIN_RC})

# 设置输出exe文件的位置
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}/${PROJECT_NAME}")

# 执行对象
add_executable(${PROJECT_NAME} WIN32
    ${HEADER_FILES}
    ${SRC_FILES}
    ${UI_FILES}
    ${RESOURCE_FILES}
    ${WIN_RC}
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Charts Qt5::Network )
target_link_libraries(${PROJECT_NAME} ${QCEF_WIDGET_DLL})

if (MSVC)
  if (CMAKE_MAJOR_VERSION LESS 3)
    message(WARNING "CMake version 3.0 or newer is required use build variable TARGET_FILE")
  else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND mt.exe -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\${PROJECT_NAME}.manifest\" -inputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\" -outputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\"
    )
  endif()
endif(MSVC)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/imageformats/
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QSvgPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>/imageformats/
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${QCEF_WIDGET_SDK_BIN_OUT} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
