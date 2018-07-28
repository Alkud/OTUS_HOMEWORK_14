#CmakeList.txt for mapper_reducer library in OTUS Homework #14

# set library name and content
add_library(mapper_reducer
  prefix_mapper.h prefix_mapper.cpp
  maxval_reducer.h maxval_reducer.cpp
)
