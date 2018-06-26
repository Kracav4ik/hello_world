cmake_minimum_required(VERSION 3.2)

if("$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    set(HELLOWORLD_BUILD_NUMBER "0")
else()
    set(HELLOWORLD_BUILD_NUMBER "$ENV{TRAVIS_BUILD_NUMBER}")
endif()

project(helloworld VERSION 0.0.${HELLOWORLD_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

configure_file(version.h.in version.h)

add_executable(hello_world main.cpp)

add_library(helloworld lib.cpp)

add_executable(boost_test boost_test.cpp)
add_executable(gtest gtest.cpp)

set_target_properties(hello_world helloworld boost_test gtest PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

set_target_properties(boost_test PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(hello_world
        helloworld
        )

target_link_libraries(boost_test
        ${Boost_LIBRARIES}
        helloworld
        )

target_link_libraries(gtest
        ${GTEST_LIBRARIES}
        pthread
        helloworld
        )

install(TARGETS hello_world RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT otus.cpp@gmail.com)

include(CPack)

enable_testing()

add_test(boost_test boost_test)
add_test(gtest gtest)
