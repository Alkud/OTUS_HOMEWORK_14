project(unit_tests)

find_package(Boost COMPONENTS filesystem unit_test_framework REQUIRED)
find_package(Threads)

add_executable(mapper_test  mapper_test.cpp)
add_executable(reducer_test reducer_test.cpp)
add_executable(engine_test engine_test.cpp)
add_executable(yarm_test yarm_test.cpp)

target_include_directories(mapper_test PRIVATE ${Boost_INCLUDE_DIR} ../mapper_reducer)
target_include_directories(reducer_test PRIVATE ${Boost_INCLUDE_DIR} ../mapper_reducer)
target_include_directories(engine_test PRIVATE ${Boost_INCLUDE_DIR} ../yarm_engine)
target_include_directories(yarm_test PRIVATE ${Boost_INCLUDE_DIR} ../mapper_reducer ../yarm_engine)

set_target_properties(mapper_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

set_target_properties(reducer_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

set_target_properties(engine_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

set_target_properties(yarm_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)


target_link_libraries(mapper_test
  pthread
  mapper_reducer
  ${Boost_LIBRARIES}
)

target_link_libraries(reducer_test
  pthread
  mapper_reducer
  ${Boost_LIBRARIES}
)

target_link_libraries(engine_test
  pthread
  yarm_engine
  ${Boost_LIBRARIES}
)

target_link_libraries(yarm_test
  pthread
  mapper_reducer
  yarm_engine
  ${Boost_LIBRARIES}
)

enable_testing()

add_test(NAME TEST_MAPPER
         COMMAND mapper_test)

add_test(NAME TEST_REDUCER
         COMMAND reducer_test)

add_test(NAME TEST_ENGINE
         COMMAND engine_test)

add_test(NAME TEST_YARM
         COMMAND yarm_test)


