cmake_minimum_required(VERSION 3.5)

project (camera)
set(APP_TARGET camera)
set(APP_Test_TARGET camera_test)
set(APP_ModelLoad_TARGET camera_model_load)

#if you want a double-precision
#set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -DUSING_FLOAT64")

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

########################################
# complie options
########################################

# -Wextra warning: unused variables
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")




#include_directories(3rdparty/glad
include_directories(3rdparty/)
include_directories(3rdparty/stb_image)

file(GLOB GLADC
"3rdparty/glad/glad.c"
)

file(GLOB STBIMAGECPP
"3rdparty/stb_image/src/*.cpp"
)





file(GLOB Apps_SRC
"src/Apps/main.cpp"
)

file(GLOB Apps_Test_SRC
"src/Apps/test.cpp"
)

file(GLOB Apps_ModelLoad_SRC
"src/Apps/model_load.cpp"
)


file(GLOB GLCamera_SRC
"src/GLCamera/*.cpp"
"src/GLCamera/*.h"
"src/GLCamera/*.hpp"
)

file(GLOB Geometry_SRC
"src/Geometry/*.cpp"
"src/Geometry/*.h"
"src/Geometry/*.hpp"
)

file(GLOB Tools_SRC
"src/Tools/*.cpp"
"src/Tools/*.h"
"src/Tools/*.hpp"
)

list(APPEND SOURCES
    ${GLCamera_SRC}
    ${Geometry_SRC}
    ${Tools_SRC}
    ${Apps_SRC}
    ${GLADC}
    ${STBIMAGECPP}
    )

list(APPEND SOURCES_Test
    ${GLCamera_SRC}
    ${Geometry_SRC}
    ${Tools_SRC}
    ${Apps_Test_SRC}
    ${GLADC}
    ${STBIMAGECPP}
    )

list(APPEND SOURCES_Model
    ${GLCamera_SRC}
    ${Geometry_SRC}
    ${Tools_SRC}
    ${Apps_ModelLoad_SRC}
    ${GLADC}
    ${STBIMAGECPP}
    )




########################################
# find the required packages
########################################
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
include_directories(${GLFW_INCLUDE_DIRS})

find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OPENGL_INCLUDE_DIR}")
include_directories(${OPENGL_INCLUDE_DIRS})

########################################
# generate exetuable and link libraries
########################################
add_executable(${APP_TARGET} ${SOURCES})
target_link_libraries(${APP_TARGET} ${GLFW3_LIBRARY} GLU GL Xrandr Xi Xinerama Xcursor X11 rt dl ${ASSIMP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})


add_executable(${APP_Test_TARGET} ${SOURCES_Test})
target_link_libraries(${APP_Test_TARGET} ${GLFW3_LIBRARY} GLU GL Xrandr Xi Xinerama Xcursor X11 rt dl ${ASSIMP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

add_executable(${APP_ModelLoad_TARGET} ${SOURCES_Model})
target_link_libraries(${APP_ModelLoad_TARGET} ${GLFW3_LIBRARY} GLU GL Xrandr Xi Xinerama Xcursor X11 rt dl ${ASSIMP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})


