#CmakeList.txt for OTUS Homework #14

#Check CMake version
cmake_minimum_required(VERSION 3.2)

#Set project name, set PROJECT_VERSION_MINOR value equal to TRAVIS_BUILD NUMBER
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set (VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})
else ()
  set (VERSION_PATCH 1)
endif()

set(CMAKE_CXX_STANDARD 14)

project(yarm VERSION 0.0.${VERSION_PATCH})

#add library subdirectories
add_subdirectory(mapper_reducer)
add_subdirectory(yarm_engine)

#add tests
add_subdirectory(unit_tests)

set (BOOST_MIN_VERSION "1.54.0")

#Find Boost library components
#find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(Threads)

set(BOOST_DEBUG                ON)
set(Boost_USE_MULTITHREADED    ON)

set(yarm_process
    ${PROJECT_SOURCE_DIR}/yarm_process.h
    ${PROJECT_SOURCE_DIR}/yarm_process.cpp)

#Set executable target
add_executable(yarm yarm.cpp ${yarm_process})

#Enable tests
enable_testing()

#Set properties and compile options for executable target
set_target_properties(yarm
                      PROPERTIES CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#Link
target_link_libraries(yarm pthread yarm_engine mapper_reducer)

target_include_directories(yarm PRIVATE ./yarm_engine ./mapper_reducer)

#Install
install(TARGETS yarm RUNTIME DESTINATION bin)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandr_kudinov@mail.ru)

include(CPack)
