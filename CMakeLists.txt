cmake_minimum_required(VERSION 3.22)
project(jintercept)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/minhook)

find_package(OpenGL REQUIRED)

file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp)

add_link_options(-static)
include_directories(${OPENGL_INCLUDE_DIRS} vendor/imgui vendor/imgui/backends vendor/glfw/include vendor/minhook/include)
add_library(jintercept SHARED ${IMGUI_SOURCES} gui/window_manager.cpp gui/window.cpp gui/main_window.cpp main.cpp class/package_manager.cpp class/klass.cpp  hooks/defineclass.cpp hooks/defineclasswithsource.cpp hooks/hooks.cpp)
target_link_libraries(jintercept glfw ${GLFW_LIBRARIES} OpenGL::GL minhook)