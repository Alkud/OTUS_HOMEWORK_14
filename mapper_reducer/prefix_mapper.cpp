#include "prefix_mapper.h"

#include <map>

std::list<std::string>
PrefixMapper::operator()(const std::list<std::string>& dataToMap)
{
  size_t minStringSize{2000};

  for(const auto& item : dataToMap)
  {
    if (item.size() < minStringSize)
    {
      auto tabPosition{item.find('\t', 0)};
      auto itemValue = tabPosition == std::string::npos
                       ? item : item.substr(tabPosition+1);
      minStringSize = itemValue.size();
    }
  }

  std::list<std::string> occurrenceCounts{};

  for (size_t prefixLength{1}; prefixLength <= minStringSize; ++prefixLength)
  {
    std::map <std::string, size_t> prefixes{};
    for(const auto& item : dataToMap)
    {
      auto tabPosition{item.find('\t', 0)};
      auto itemValue = tabPosition == std::string::npos
                       ? item : item.substr(tabPosition+1);
      ++prefixes[itemValue.substr(0, prefixLength)];
    }

    size_t maxOccurrenceCount{};
    for (const auto& prefix : prefixes)
    {
      if (prefix.second > maxOccurrenceCount)
      {
        maxOccurrenceCount = prefix.second;
      }
    }

    occurrenceCounts.push_back(std::to_string(prefixLength)
                               + "\t" + std::to_string(maxOccurrenceCount));
  }

  return occurrenceCounts;
}
