#CmakeList.txt for yamr_engine library in OTUS Homework #14

find_package(Threads)

# set library name and content
add_library(yamr_engine
  yamr_engine.h yamr_engine.cpp
)

target_include_directories(yamr_engine PRIVATE ../mapper_reducer)

target_link_libraries(yamr_engine pthread)
