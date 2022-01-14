#------------------------------------------------------------------------------
# General build settings
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.4...3.18)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OSX deployment version")
project(pyasge)
set(ASGE_BUILD_DEMOS ON CACHE BOOL "Disable ASGE demos")
set(ASGE_ENABLE_DOXYGEN ON CACHE BOOL "Enable ASGE doxygen")

#------------------------------------------------------------------------------
# Add the dependencies
#------------------------------------------------------------------------------
add_subdirectory(libs/pybind11)
add_subdirectory(libs/asge)


#------------------------------------------------------------------------------
# The magic python module and the files to compile
#------------------------------------------------------------------------------
pybind11_add_module(
        ${PROJECT_NAME}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PyBind.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Camera.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Colours.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Font.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Game.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/GamePad.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/GameSettings.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/GameTime.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Input.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/InputEvents.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Keys.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Logger.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Mouse.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/PixelBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Point2D.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Renderer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/RenderTarget.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Resolution.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Shader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Sprite.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/SpriteBounds.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Texture2D.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Text.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Tile.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Value.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/bindings/Viewport.cpp")


#------------------------------------------------------------------------------
# Set C++ version definition
#------------------------------------------------------------------------------
if (${PYASGE_VERSION_INFO})
    target_compile_definitions(
            ${PROJECT_NAME}
            PRIVATE
            VERSION_INFO=${PYASGE_VERSION_INFO})
endif ()


#------------------------------------------------------------------------------
# Add ASGE non-public search paths to the PyASGE project
#------------------------------------------------------------------------------
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        "${CMAKE_SOURCE_DIR}/libs/asge/engine/include/Engine"
        "${CMAKE_SOURCE_DIR}/libs/asge/engine/src"
        "${CMAKE_SOURCE_DIR}/libs/asge/engine/libs/glm")


#------------------------------------------------------------------------------
# Allow linking to the game engine and its libraries
#------------------------------------------------------------------------------
get_target_property(ASGE_ARCHIVE_OUTPUT_DIRECTORY asge ARCHIVE_OUTPUT_DIRECTORY)
target_link_directories(${PROJECT_NAME} PRIVATE ${ASGE_ARCHIVE_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE asge)


#------------------------------------------------------------------------------
# Builds the docs using make and sphinx
#------------------------------------------------------------------------------
find_program(sphinx NAMES sphinx-build)
if (sphinx)

    # set input and output files #
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/Makefile
            ${CMAKE_CURRENT_BINARY_DIR}/docs/Makefile @ONLY)
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/index.rst
            ${CMAKE_CURRENT_BINARY_DIR}/docs/index.rst @ONLY)
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in
            ${CMAKE_CURRENT_BINARY_DIR}/docs/conf.py @ONLY)

    # link to the pages to render #
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/_pages
            ${CMAKE_CURRENT_BINARY_DIR}/docs/_pages
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            OUTPUT_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    # link to the pages to render #
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/_static
            ${CMAKE_CURRENT_BINARY_DIR}/docs/_static
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            OUTPUT_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    # create a target for building the docs #
    add_custom_target(
            ${PROJECT_NAME}_docs
            COMMAND pip install ${CMAKE_SOURCE_DIR}
            COMMAND make html SOURCEDIR="." BUILDDIR=${CMAKE_CURRENT_BINARY_DIR}/docs
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
            #DEPENDS ${PROJECT_NAME}
            VERBATIM)
endif ()
