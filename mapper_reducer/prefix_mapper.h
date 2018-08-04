#pragma once

#include <list>
#include <map>
#include <sstream>
#include "mapper_reducer_base.h"

class PrefixMapper : public MapperReducerBase
{
public:
  void operator()(const std::string& inputString,
                  std::list<std::string>& destination) override;

private:
  std::pair<std::string, std::string>
  extractKeyValue(const std::string& tabSeparatedData);
};
