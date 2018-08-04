#pragma once

#include <string>
#include <list>

class MapperReducerBase
{
public:

  virtual void
  operator()(const std::string& inputString,
             std::list<std::string>& destination) = 0;
};
