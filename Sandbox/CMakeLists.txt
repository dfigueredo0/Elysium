file(GLOB_RECURSE SANDBOX_SRC CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(SandboxApp ${SANDBOX_SRC})

if(MSVC)
    target_compile_options(SandboxApp PRIVATE /utf-8)
endif()

target_link_libraries(SandboxApp PRIVATE ElysiumLib)

target_include_directories(SandboxApp PRIVATE ../Elysium/src)