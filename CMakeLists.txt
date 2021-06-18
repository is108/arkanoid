cmake_minimum_required(VERSION 2.8)

project(arkanoid)

set (HEADERS 
	src/game.h
	src/brick.h
	src/rectangle.h
	src/platform.h
	src/ball.h
	src/utils.h
    ) 
set (SOURCES 
	src/main.cpp
	src/game.cpp
	src/brick.cpp
	src/rectangle.cpp
	src/platform.cpp
	src/ball.cpp
    ) 

add_executable(arkanoid ${SOURCES} ${HEADERS})
target_link_libraries(arkanoid -lsfml-graphics -lsfml-window -lsfml-system)
