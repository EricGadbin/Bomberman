cmake_minimum_required(VERSION 3.11)


project(oop_indie_studio_2018)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("pas opengl")
endif(NOT OPENGL_FOUND)


include_directories(
	lib/libirrlicht/include/
	${OPENGL_INCLUDE_DIRS}
)

if(WIN32)
	include_directories(
    		lib/SFML/include
	)
endif(WIN32)

if(UNIX)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    if(NOT X11_FOUND)
        message("pas x11")
    endif(NOT X11_FOUND)
endif(UNIX)

set(SRCS ${CMAKE_SOURCE_DIR}/src/)
set(INCS ${CMAKE_SOURCE_DIR}/include/)

if (WIN32)
    set(SRCSD ${CMAKE_SOURCE_DIR}/window/)
elseif(UNIX)
    set(SRCSD ${CMAKE_SOURCE_DIR}/linux/)
endif()

if(UNIX)
	link_directories(${CMAKE_SOURCE_DIR}/lib/libirrlicht/linux/)
elseif(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/lib/libirrlicht/windows/)
endif()

	link_directories(${CMAKE_SOURCE_DIR}/lib/SFML/bin)
	link_directories(${CMAKE_SOURCE_DIR}/lib/SFML/lib)

FILE(GLOB_RECURSE SRCS_FILE ${SRCS}/*.cpp)
FILE(GLOB_RECURSE INCS_FILE ${INCS}/*.hpp)
FILE(GLOB_RECURSE SRCSD_FILE ${SRCSD}/*.cpp)

add_executable(bomberman ${SRCS_FILE} ${INCS} ${SRCSD_FILE})

if (UNIX)
  target_link_libraries(bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm -lpthread)
elseif(WIN32)
  target_link_libraries(bomberman sfml-audio-d)
  target_link_libraries(bomberman sfml-system-d)
endif()

target_link_libraries(bomberman Irrlicht)
target_link_libraries(bomberman ${OPENGL_LIBRARIES})

if(UNIX)
    target_link_libraries(bomberman
    ${X11_LIBRARIES}
    -lXxf86vm
    )
endif(UNIX)

file(COPY ${CMAKE_SOURCE_DIR}/lib/SFML/bin/sfml-audio-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/lib/SFML/bin/openal32.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/lib/SFML/bin/sfml-system-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/lib/libirrlicht/windows/Irrlicht.dll DESTINATION ${CMAKE_BINARY_DIR})
