cmake_minimum_required(VERSION 3.0)
project(game)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(JSON_BuildTests OFF)

add_subdirectory(./vendor/glfw)
add_subdirectory(./vendor/glm)
add_subdirectory(./vendor/json)

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
    ./vendor/imgui_impl_glfw_gl3/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c vendor/stb/src/stb_image.cpp)
file(GLOB PROJECT_HEADERS ./includes/*.hpp)
file(GLOB PROJECT_SOURCES ./src/*.cpp)
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
    ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
