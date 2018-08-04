// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE PREFIX_MAPPER_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>

#include "prefix_mapper.h"


BOOST_AUTO_TEST_SUITE(mapper_test)


BOOST_AUTO_TEST_CASE(numbers_mapping_test)
{
  try
  {
    PrefixMapper mapper{};

    std::list<std::string> actualMappedData{};

    std::list<std::string> expectedMappedData{};

    for (size_t idx {100}; idx < 1000; ++idx)
    {
      mapper(std::to_string((idx-100) * 3) + "\t" + std::to_string(idx),
             actualMappedData);

      for (int power{2}; power >=0; --power)
      {
        expectedMappedData.push_back(
              std::to_string(3 - power) + "\t"
              + std::to_string(idx / static_cast<int>(std::pow(10, power))));
      }
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(actualMappedData.begin(), actualMappedData.end(),
                                  expectedMappedData.begin(), expectedMappedData.end());

  }
  catch (const std::exception& ex)
  {
    std::cerr << "numbers_mapping_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

std::string extractValue(const std::string& tabSeparatedData)
{
  auto tabPosition{tabSeparatedData.find('\t', 0)};
  auto value {tabSeparatedData.substr(tabPosition + 1)};
  return value;
}

static const char characterSource[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";

BOOST_AUTO_TEST_CASE(strings_mapping_test)
{
  try
  {
    std::srand(std::time(nullptr));

    PrefixMapper mapper{};

    std::list<std::string> mappedData{};

    size_t stringLength{}, listSize{};
    size_t expectedOffset{};

    stringLength = std::rand() % 20 + 1;
    listSize = std::rand() % 1000 + 1;
    for (size_t idx{0}; idx < listSize; ++idx)
    {
      mappedData.clear();

      std::stringstream email{};

      for (size_t idx {0}; idx < stringLength; ++idx)
      {
        email << characterSource[rand() % (sizeof(characterSource) - 1)];
      }

      email << "@";

      for (size_t idx {0}; idx < stringLength; ++idx)
      {
        email << characterSource[rand() % (sizeof(characterSource) - 1)];
      }

      email << ".";
      for (size_t idx {0}; idx < 2; ++idx)
      {
        email << characterSource[rand() % (sizeof(characterSource) - 1)];
      }

      auto emailString {email.str()};

      mapper(std::to_string(expectedOffset)
             + "\t" + emailString, mappedData);

      size_t substrLength{1};
      for (const auto& nextString : mappedData)
      {
        auto testString {std::to_string(substrLength) + "\t" + emailString.substr(0, substrLength)};
        BOOST_CHECK(nextString == testString);
        ++substrLength;
      }

      expectedOffset += emailString.size() + 1;
    }


  }
  catch (const std::exception& ex)
  {
    std::cerr << "strings_mapping_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()

