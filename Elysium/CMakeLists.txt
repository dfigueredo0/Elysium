#Elysium

file(GLOB_RECURSE ELYSIUM_SRC CONFIGURE_DEPENDS "src/Elysium/*.cpp" "src/*.cpp")
file(GLOB_RECURSE ELYSIUM_HEADERS CONFIGURE_DEPENDS "src/Elysium/*.h" "src/*.h")

set(ALL_ELYSIUM_FILES ${ELYSIUM_SRC} ${ELYSIUM_HEADERS})

add_library(ElysiumLib SHARED ${ALL_ELYSIUM_FILES})

target_include_directories(ElysiumLib PUBLIC src)

if(MSVC)
    target_precompile_headers(ElysiumLib PRIVATE src/elypch.h)
else()
    target_compile_options(ElysiumLib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Definitions
target_compile_definitions(ElysiumLib PUBLIC ELY_PLATFORM_WINDOWS)
target_compile_definitions(ElysiumLib PRIVATE ELY_BUILD_DLL)

# Add vendors
target_include_directories(ElysiumLib PUBLIC ${CMAKE_SOURCE_DIR}/vendor/spdlog/include)

# Folder Layout
source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES ${ALL_ELYSIUM_FILES}
)

