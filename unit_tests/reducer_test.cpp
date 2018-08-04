// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE MAXVAL_REDUCER_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "prefix_frequency_reducer.h"



BOOST_AUTO_TEST_SUITE(reducer_test)


BOOST_AUTO_TEST_CASE(simple_reduce_test)
{
  try
  {
    std::list<std::string> testData{};

    for (size_t prefixLength{1}; prefixLength < 8; ++prefixLength)
    {
      std::stringstream testStream{};
      testStream << std::to_string(prefixLength) << "\t";
      char testChar {'a'};
      for (size_t idx {0}; idx < 10; ++idx)
      {
        for (size_t occurrenceCount{1}; occurrenceCount < 11; ++occurrenceCount)
        {
          testStream << std::string(prefixLength, testChar) << " ";
        }
        ++testChar;
      }

      auto testString{testStream.str()};

      testData.push_back(testString.substr(0, testString.size() - 1));
    }

    std::list<std::string> expectedReducedData{};

    for (size_t prefixLength{1}; prefixLength < 8; ++prefixLength)
    {
      std::stringstream testStream{};
      testStream << ">>>> PREFIX_LENGTH: " << std::to_string(prefixLength) << "\n";
      char testChar {'a'};
      for (size_t idx {0}; idx < 10; ++idx)
      {
        testStream << std::string(prefixLength, testChar++) << " 10\n";
      }

      auto testString{testStream.str()};

      expectedReducedData.push_back(testString.substr(0, testString.size() - 1));
    }

    std::list<std::string> actualReducedData{};
    PrefixFrequencyReducer testReducer{};

    for (const auto nextString : testData)
    {
      testReducer(nextString, actualReducedData);
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(actualReducedData.begin(), actualReducedData.end(),
                                  expectedReducedData.begin(), expectedReducedData.end());
  }
  catch (const std::exception& ex)
  {
    std::cerr << "simple_reduce_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}


BOOST_AUTO_TEST_SUITE_END()
