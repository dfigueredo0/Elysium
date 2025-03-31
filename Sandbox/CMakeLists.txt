#Sandbox

file(GLOB_RECURSE SANDBOX_SRC CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(SandboxApp ${SANDBOX_SRC})

target_link_libraries(SandboxApp PRIVATE ElysiumLib)

target_include_directories(SandboxApp PUBLIC ../Elysium/src)