#CmakeList.txt for mapper_reducer library in OTUS Homework #14

# set library name and content
add_library(mapper_reducer
  mapper_reducer_base.h
  prefix_mapper.h prefix_mapper.cpp
  prefix_frequency_reducer.h prefix_frequency_reducer.cpp
)
