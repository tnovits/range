cmake_minimum_required(VERSION 3.12)
project(range VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --install-folder=${CMAKE_BINARY_DIR} --build=missing
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE conan_output
        ERROR_VARIABLE conan_output
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(range)
target_sources(range PRIVATE
        main.cpp
        )

add_library(ip_pool ip_pool.h ip_pool.cpp)
target_sources(ip_pool PRIVATE
        ip_pool.cpp
        )

add_executable(test_ip_pool)
target_sources(test_ip_pool PRIVATE
        test_ip_pool.cpp
        )

set_target_properties(test_ip_pool PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(range
        ip_pool
        )

message("BOOST:" ${Boost_LIBRARIES})

target_link_libraries(test_ip_pool
        ${Boost_LIBRARIES}
        ip_pool
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tst
        ${CMAKE_CURRENT_BINARY_DIR}/bin/ip_filter.tst
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv
        ${CMAKE_CURRENT_BINARY_DIR}/bin/ip_filter.tsv
        )

install(TARGETS range RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tnovits@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(ip_filter_tests test_ip_pool)