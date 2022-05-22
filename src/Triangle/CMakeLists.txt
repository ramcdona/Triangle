# triangle is the legacy interface:
add_library(triangle STATIC
   acute.c
   eps_writer.c
   predicates.c
   triangle.c
   triangle_io.c
   )
add_library(Triangle::triangle ALIAS triangle)

set_target_properties(triangle
   PROPERTIES
   CXX_VISIBILITY_PRESET hidden
   POSITION_INDEPENDENT_CODE TRUE
   )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-ffp-model=strict")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-ffp-model=strict")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-frounding-math -fsignaling-nans")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    if (WIN32)
        set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-fp:strict")
    else()
        set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-fp-model=strict")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties( triangle PROPERTIES COMPILE_FLAGS "-fp:strict")
else()
    message("Compiler not recognized")
    message(${CMAKE_CXX_COMPILER_ID})
endif()

target_link_libraries(triangle PRIVATE -lm)
target_include_directories(triangle
   PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>
	PRIVATE private
   )

if(NOT TRIANGLE_ENABLE_ACUTE)
   message(STATUS "Building without aCute...")
	target_compile_options(triangle PUBLIC -DNO_ACUTE)
else()
   message(STATUS "Building with aCute...")
endif()

set_property(TARGET triangle PROPERTY VERSION ${Triangle_VERSION})
set_property(TARGET triangle PROPERTY SOVERSION 1)

# triangle-api is the "modern" interface:
add_library(triangle-api
   triangle_api.c
   triangle_helper.c
   )
add_library(Triangle::triangle-api ALIAS triangle-api)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-ffp-model=strict")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-ffp-model=strict")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-frounding-math -fsignaling-nans")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    if (WIN32)
        set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-fp:strict")
    else()
        set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-fp-model=strict")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties( triangle-api PROPERTIES COMPILE_FLAGS "-fp:strict")
else()
    message("Compiler not recognized")
    message(${CMAKE_CXX_COMPILER_ID})
endif()

target_link_libraries(triangle-api
	PUBLIC
   Triangle::triangle
   )
target_include_directories(triangle-api
   PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
   $<INSTALL_INTERFACE:include>
	PRIVATE private
   )

set_property(TARGET triangle-api PROPERTY VERSION ${Triangle_VERSION})
set_property(TARGET triangle-api PROPERTY SOVERSION 1)
set_property(TARGET triangle-api PROPERTY C_VISIBILITY_PRESET hidden)

configure_file(triangle_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/triangle_version.h @ONLY)

include(GenerateExportHeader)
generate_export_header(triangle-api BASE_NAME triangle)

install(
   TARGETS triangle triangle-api
   EXPORT TriangleTargets
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
   RUNTIME DESTINATION bin
   INCLUDES DESTINATION include
   )

install(
   FILES
	# triangle
	#acute.h
   #eps_writer.h
   #predicates.h
   triangle_config.h
   triangle.h
	# triangle-api
   triangle_api.h
   ${CMAKE_CURRENT_BINARY_DIR}/triangle_version.h
   ${CMAKE_CURRENT_BINARY_DIR}/triangle_export.h
   DESTINATION include
   COMPONENT Devel
   )
export( TARGETS triangle triangle-api
   FILE "${CMAKE_CURRENT_BINARY_DIR}/Triangle/TriangleTargets.cmake"
   NAMESPACE Triangle::
   )
