#pragma once

#include <list>
#include <sstream>

class PrefixMapper
{
public:
  std::list<std::string> operator()(const std::list<std::string>& dataToMap);
};
