#include "maxval_reducer.h"

#include <map>
#include <set>
#include <iostream>

std::list<std::string>
MaxValuReducer::operator()(const std::list<std::string>& dataToMap)
{
  std::map<size_t, std::set<size_t>> keyCombinedData{};

  for (const auto& nextString : dataToMap)
  {
    auto nextKeyValuePair{extractKeyValue(nextString)};

    try
    {
      auto nextKey{std::stoull(nextKeyValuePair.first)};
      auto nextValue{std::stoull(nextKeyValuePair.second)};

      keyCombinedData[nextKey].insert(nextValue);
    }
    catch (...)
    {
      std::cerr << "Invalid data: " << nextString << "\n";
      throw;
    }
  }

  std::list<std::string> result{};

  for (const auto& item : keyCombinedData)
  {
    result.push_back(std::to_string(item.first) + "\t"
                     + std::to_string(*item.second.rbegin()));
  }

  return result;
}

std::pair<std::string, std::string> MaxValuReducer::extractKeyValue(const std::string& tabSeparatedData)
{
  auto tabPosition{tabSeparatedData.find('\t', 0)};
  if (tabPosition == std::string::npos
      || tabPosition == tabSeparatedData.size() - 1)
  {
    return std::make_pair(tabSeparatedData, std::string{});
  }
  auto key {tabSeparatedData.substr(0, tabPosition)};
  auto value {tabSeparatedData.substr(tabPosition + 1)};
  return std::make_pair(key, value);
}
