#include "prefix_mapper.h"


void
PrefixMapper::operator()(const std::string& inputString,
                         std::list<std::string>& destination)
{
  auto value{extractKeyValue(inputString).second};

  size_t stringSize{value.size()};

  for (size_t prefixLength{1}; prefixLength <= stringSize; ++prefixLength)
  {
    auto prefix{value.substr(0, prefixLength)};

    std::stringstream lengthInfo{};
    lengthInfo << prefixLength << "\t" << prefix;

    destination.push_back(lengthInfo.str());
  }
}

std::pair<std::string, std::string> PrefixMapper::extractKeyValue(const std::string& tabSeparatedData)
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
