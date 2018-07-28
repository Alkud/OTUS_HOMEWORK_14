// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE MAXVAL_REDUCER_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "maxval_reducer.h"



BOOST_AUTO_TEST_SUITE(reducer_test)


BOOST_AUTO_TEST_CASE(simple_reduce_test)
{
  try
  {
    std::list<std::string> testData{};

    for (size_t prefixLength{1}; prefixLength < 21; ++prefixLength)
    {
      for (size_t occurrenceCount{1}; occurrenceCount < 1001; ++occurrenceCount)
      {
        testData.push_back(std::to_string(prefixLength) + "\t" + std::to_string(occurrenceCount));
      }
    }

    std::list<std::string> expectedReducedData{};

    for (size_t prefixLength{1}; prefixLength < 21; ++prefixLength)
    {
      expectedReducedData.push_back(std::to_string(prefixLength) + "\t1000");
    }

    auto actualReducedData {MaxValuReducer{}(testData)};

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
