cmake_minimum_required( VERSION 2.8 )

project( ProjectName )

find_package( PNG REQUIRED )
include_directories( ${PNG_INCLUDE_DIRS} )
set( CMAKE_VERBOSE_MAKEFILE ON )
add_executable( RotateImage
    RotateImage.cpp
)
target_link_libraries( RotateImage ${PNG_LIBRARIES} )

install( TARGETS RotateImage
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
file( WRITE .includes_list "" )
get_directory_property( includelist DIRECTORY ${PROJECT_SOURCE_DIR} INCLUDE_DIRECTORIES )
foreach(inc ${includelist})
	file( APPEND .includes_list "${inc}\n" )
endforeach()
#set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
