#pragma once

#include <list>
#include <string>

class MaxValuReducer
{
public:
  std::list<std::string> operator()(const std::list<std::string>& dataToMap);

private:
  std::pair<std::string, std::string> extractKeyValue(const std::string& tabSeparatedData);
};
