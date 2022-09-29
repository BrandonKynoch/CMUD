cmake_minimum_required(VERSION 3.14)
project(yolo-nerf C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw)

list(APPEND SOURCES
	src/main.cpp
	src/globals.h
)


add_executable(yolo-nerf MACOSX_BUNDLE WIN32 ${SOURCES})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT yolo-nerf)


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
        "glu32.lib;opengl32.lib"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
    
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lX11"
    )
endif()

target_link_libraries(yolo-nerf glfw ${EXTRA_LIBS})
