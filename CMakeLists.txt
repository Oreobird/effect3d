cmake_minimum_required(VERSION 2.8.4)

project(effect3d)

# Build options
option(BUILD_DEBUG "Build Debug version" OFF)

# Use C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
message(STATUS "C++14 support has been enabled by default.")

add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/ncnn)

aux_source_directory(src effect3d_src_files)

if (BUILD_DEBUG)
	add_definitions(-DDEBUG)
endif (BUILD_DEBUG)

if (BUILD_FACE_ID)
    message(STATUS "Build with face id.")
    find_package(OpenCV)
    if (NOT OpenCV_FOUND)
        message(WARNING "OpenCV not found. Test will not be built.")
    else()
		include_directories(${OpenCV_INCLUDE_DIRS} build)
		link_directories(/usr/local/lib/)
		set(required_libs ${OpenCV_LIBS})

		add_executable(effect3d ${effect3d_src_files})
		target_link_libraries(effect3d ${required_libs} ncnn -lrt -pthread)
    endif()
endif()
