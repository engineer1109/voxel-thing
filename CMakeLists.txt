cmake_minimum_required(VERSION 3.0)
project(game)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(BUILD_SHARED ON)
option(JSON_BuildTests OFF)
set(BUILD_SHARED ON)

add_subdirectory(./vendor/glfw)
add_subdirectory(./vendor/glm)
add_subdirectory(./vendor/json)
add_subdirectory(./vendor/openvr)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
    ./includes/
    ./vendor/json/src/
    ./vendor/glad/include/
    ./vendor/glfw/include/
    ./vendor/glm/glm/
    ./vendor/stb/include/
    ./vendor/imgui/
    ./vendor/imgui_impl_glfw_gl3/
    ./vendor/openvr/headers/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c vendor/stb/src/stb_image.cpp)
file(GLOB PROJECT_HEADERS 
    includes/block.hpp
    includes/block_database.hpp
    includes/chunk.hpp
    includes/chunk_mesh.hpp
    includes/cursor.hpp
    includes/data.hpp
    includes/editor_info_pane.hpp
    includes/editor_state.hpp
    includes/game_state.hpp
    includes/state_switcher.hpp
    includes/tooltip.hpp
    includes/tooltip_renderer.hpp
    includes/vr_state.hpp
    includes/world.hpp
    includes/world_renderer.hpp
    includes/E/application.hpp
    includes/E/camera.hpp
    includes/E/config.hpp
    includes/E/context.hpp
    includes/E/input.hpp
    includes/E/key_manager.hpp
    includes/E/mesh.hpp
    includes/E/render_manager.hpp
    includes/E/renderer.hpp
    includes/E/screen_context.hpp
    includes/E/shader.hpp
    includes/E/state.hpp
    includes/E/texture.hpp
    includes/E/utils.hpp
    includes/E/view.hpp
    includes/E/vr_context.hpp
    ./vendor/openvr/headers/*.h)
file(GLOB PROJECT_SOURCES
    src/main.cpp
    src/block_database.cpp
    src/chunk.cpp
    src/chunk_mesh.cpp
    src/cursor.cpp
    src/editor_info_pane.cpp
    src/editor_state.cpp
    src/game_state.cpp
    src/state_switcher.cpp
    src/tooltip.cpp
    src/tooltip_renderer.cpp
    src/vr_state.cpp
    src/world.cpp
    src/world_renderer.cpp
    src/E/application.cpp
    src/E/camera.cpp
    src/E/config.cpp
    src/E/input.cpp
    src/E/key_manager.cpp
    src/E/mesh.cpp
    src/E/render_manager.cpp
    src/E/screen_context.cpp
    src/E/shader.cpp
    src/E/state.cpp
    src/E/texture.cpp
    src/E/utils.cpp
    src/E/vr_context.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
    README.md
    .gitattributes
    .gitignore
    .gitmodules)

# imgui doesn't like being treated like a normal library. so we're doing this to not
# 'break any rules'.
file(GLOB VENDOR_IMGUI_SOURCES ./vendor/imgui/*.cpp ./vendor/imgui_impl_glfw_gl3/*.cpp)
file(GLOB VENDOR_IMGUI_HEADERS ./vendor/imgui/*.h ./vendor/imgui_impl_glfw_gl3/*.h)

source_group("headers" FILES ${PROJECT_HEADERS} ${VENDOR_IMGUI_HEADERS})
source_group("sources" FILES ${PROJECT_SOURCES} ${VENDOR_IMGUI_SOURCES})
source_group("vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
    ${VENDORS_SOURCES} ${VENDOR_IMGUI_HEADERS} ${VENDOR_IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw glm nlohmann_json
	${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/vendor/openvr/lib/win64/openvr_api.lib)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
