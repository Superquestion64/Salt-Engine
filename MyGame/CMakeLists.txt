add_executable(
	my_game 
	main.cpp 
	MyGameApp.h 
	MyGameApp.cpp 
	Unit.h 
	Villain.h 
	Villain.cpp 
	Background.h 
	Background.cpp 
	SaltSpawner.h 
	SaltSpawner.cpp 
	DemoUnit.h 
	DemoUnit.cpp
	Hero.h
	Hero.cpp
	)
	
target_link_libraries(my_game salt_lib)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.. PROPERTY VS_STARTUP_PROJECT my_game)

include_directories(../Salt)

add_definitions(-DGAME_DEBUG)

file(COPY Assets DESTINATION ../MyGame)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Release)