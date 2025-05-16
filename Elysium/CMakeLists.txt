# Elysium CMakeLists.txt

file(GLOB_RECURSE ELYSIUM_SRC CONFIGURE_DEPENDS "src/**/*.cpp")
file(GLOB_RECURSE ELYSIUM_HEADERS CONFIGURE_DEPENDS "src/**/*.h" "src/**/*.hpp")

set(ALL_ELYSIUM_FILES ${ELYSIUM_SRC} ${ELYSIUM_HEADERS})

add_library(ElysiumLib SHARED ${ALL_ELYSIUM_FILES})

add_subdirectory(vendor/ImGui)

# Link Static Libraries
target_link_libraries(ElysiumLib
    PUBLIC glfw glad 
    PRIVATE opengl32 ImGui  
)

set_target_properties(ImGui PROPERTIES FOLDER "Dependencies")

# Ensure AVX instructions are enabled for MSVC
if (MSVC)
    target_compile_options(ElysiumLib PRIVATE /arch:AVX)
endif()

# Include directories
target_include_directories(ElysiumLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui
)

# Precompiled headers and options
target_compile_options(ElysiumLib PRIVATE /utf-8)
target_precompile_headers(ElysiumLib PRIVATE src/elypch.h)

# Definitions
target_compile_definitions(ElysiumLib PUBLIC ELY_PLATFORM_WINDOWS)
target_compile_definitions(ElysiumLib PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(ElysiumLib PRIVATE ELY_BUILD_DLL)

# Folder Layout
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES ${ALL_ELYSIUM_FILES}
)

