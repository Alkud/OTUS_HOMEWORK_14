#CmakeList.txt for yarm_engine library in OTUS Homework #14

find_package(Threads)

# set library name and content
add_library(yarm_engine
  yarm_engine.h yarm_engine.cpp
)

target_link_libraries(yarm_engine pthread)
