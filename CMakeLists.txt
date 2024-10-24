CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
PROJECT(Base64URL VERSION 1.0.0 LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

OPTION(BUILD_TESTS "Build tests" OFF)

INCLUDE(FetchContent)

INCLUDE_DIRECTORIES(lib/headers)

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/sources/*.cpp")
FILE(GLOB_RECURSE TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc")

ADD_LIBRARY(zen_algorithms_base64url STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(zen_algorithms_base64url PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/headers>
        $<INSTALL_INTERFACE:include>
)

INSTALL(DIRECTORY lib/headers/ DESTINATION include)

INSTALL(TARGETS zen_algorithms_base64url
        EXPORT Base64URLTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

INSTALL(EXPORT Base64URLTargets
        FILE Base64URLTargets.cmake
        NAMESPACE zen_algorithms::
        DESTINATION lib/cmake/ZenAlgorithms
)

INCLUDE(CMakePackageConfigHelpers)
CONFIGURE_PACKAGE_CONFIG_FILE(
        cmake/Base64URLConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/Base64URLConfig.cmake
        INSTALL_DESTINATION lib/cmake/ZenAlgorithms
)

INSTALL(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/Base64URLConfig.cmake
        DESTINATION lib/cmake/ZenAlgorithms
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (BUILD_TESTS)
    FETCHCONTENT_DECLARE(
            googletest
            URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
    )
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FETCHCONTENT_MAKEAVAILABLE(googletest)
    ENABLE_TESTING()
    ADD_EXECUTABLE(tests ${SOURCES} ${TESTS})
    TARGET_LINK_LIBRARIES(tests GTest::gtest_main zen_algorithms_base64url)
    INCLUDE(GoogleTest)
    GTEST_DISCOVER_TESTS(tests)
endif()

