cmake_minimum_required(VERSION 3.14)
project(yolo-nerf C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw)

list(APPEND SOURCES
	src/main.cpp
	src/networking.cpp
	src/networking.h
	src/globals.h
)

if(APPLE)
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )

    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/MacOSXBundleInfo.plist.in
        ${CMAKE_CURRENT_BINARY_DIR}/assets/MacOSXBundleInfo.plist
    )

    set_target_properties(yolo-nerf PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/assets/MacOSXBundleInfo.plist
    )

elseif(WIN32)
    list(APPEND EXTRA_LIBS
        "glu32.lib;opengl32.lib;Ws2_32.lib;pthreadVC2.lib"
    )

    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT yolo-nerf)

    include_directories(lib/pthread)
    link_directories(lib/pthread)

else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lX11"
    )
endif()


add_executable(yolo-nerf MACOSX_BUNDLE WIN32 ${SOURCES})

target_link_libraries(yolo-nerf glfw ${EXTRA_LIBS})
