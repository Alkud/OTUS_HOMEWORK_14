#include "prefix_frequency_reducer.h"

#include <map>
#include <set>
#include <iostream>
#include <sstream>

void
PrefixFrequencyReducer::operator()(const std::string& inputString,
                           std::list<std::string>& destination)
{
  auto keyFrequencies{extractKeyValueFrequencies(inputString)};
  auto key {keyFrequencies.first};
  auto frequencies{keyFrequencies.second};

  std::stringstream resultStream;

  resultStream << ">>>> PREFIX_LENGTH: " << key << "\n";

  for (const auto& valueFrequncy : frequencies)
  {
    resultStream << valueFrequncy.first << " " << valueFrequncy.second << "\n";
  }

  auto resultString {resultStream.str()};

  destination.push_back(resultString.substr(0, resultString.size() - 1));
}

std::pair<std::string, std::map<std::string, size_t>>
PrefixFrequencyReducer::extractKeyValueFrequencies(const std::string& tabSeparatedData)
{
  std::map<std::string, size_t> valueFrequencies{};

  auto tabPosition{tabSeparatedData.find('\t', 0)};
  if (tabPosition == std::string::npos
      || tabPosition == tabSeparatedData.size() - 1)
  {
    return std::make_pair(tabSeparatedData, std::map<std::string, size_t>{});
  }

  auto key {tabSeparatedData.substr(0, tabPosition)};
  auto values {tabSeparatedData.substr(tabPosition + 1)};

  std::stringstream valueStream{values};

  std::string nextValue{};

  while (valueStream)
  {
    if (valueStream >> nextValue)
    {
      ++valueFrequencies[nextValue];
    }
    valueStream.peek();
  }

  return std::make_pair(key, valueFrequencies);
}
