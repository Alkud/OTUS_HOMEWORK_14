#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include "mapper_reducer_base.h"

class PrefixFrequencyReducer : public MapperReducerBase
{
public:
  void operator()(const std::string& inputString,
                  std::list<std::string>& destination) override;

private:
  std::pair<std::string, std::map<std::string, size_t>>
  extractKeyValueFrequencies(const std::string& tabSeparatedData);
};
