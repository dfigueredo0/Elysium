#Elysium Root CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(ElysiumEngine)
 
# C++ standard setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Output directory structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 
# GLFW Setup
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)

add_subdirectory(Elysium/vendor/GLFW)
add_subdirectory(Elysium/vendor/GLAD)

set_target_properties(glfw PROPERTIES FOLDER "Dependencies")
set_target_properties(glad PROPERTIES FOLDER "Dependencies")

# Add subdirectories for the actual projects
add_subdirectory(Elysium)
add_subdirectory(Sandbox)
