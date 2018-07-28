// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE PREFIX_MAPPER_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "prefix_mapper.h"


BOOST_AUTO_TEST_SUITE(mapper_test)


BOOST_AUTO_TEST_CASE(list_mapping_test)
{
  try
  {
    std::list<std::string> testList{};

    size_t dummyOffset{};

    for (int idx{6}; idx >= 0; --idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + "a"
                         + std::to_string(idx + 3)
                         + std::to_string(idx + 2)
                         + std::to_string(idx + 1)
                         + std::to_string(idx));

      dummyOffset += testList.back().size() + 1;
    }

    for (int idx{7}; idx >= 0; --idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + "bb"
                         + std::to_string(idx + 2)
                         + std::to_string(idx + 1)
                         + std::to_string(idx));

      dummyOffset += testList.back().size() + 1;
    }

    for (int idx{8}; idx >= 0; --idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + "ccc"
                         + std::to_string(idx + 1)
                         + std::to_string(idx));

      dummyOffset += testList.back().size() + 1;
    }

    for (int idx{9}; idx >= 0; --idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + "dddd" + std::to_string(idx));

      dummyOffset += testList.back().size() + 1;
    }

    PrefixMapper mapper{};

    auto mapResult{mapper(testList)};

    std::list<std::string> expectedResult{"1\t10", "2\t10", "3\t10", "4\t10", "5\t1"};

    BOOST_CHECK_EQUAL_COLLECTIONS(mapResult.begin(), mapResult.end(),
                                  expectedResult.begin(), expectedResult.end());
  }
  catch (const std::exception& ex)
  {
    std::cerr << "list_mapping_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(all_unique_mapping_test)
{
  try
  {
    std::list<std::string> testList{};

    size_t dummyOffset{};

    for (int idx{1000}; idx < 10000; ++idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + std::to_string(idx));

      dummyOffset += testList.back().size() + 1;
    }

    PrefixMapper mapper{};

    auto mapResult{mapper(testList)};

    std::list<std::string> expectedResult{"1\t1000", "2\t100", "3\t10", "4\t1"};

    BOOST_CHECK_EQUAL_COLLECTIONS(mapResult.begin(), mapResult.end(),
                                  expectedResult.begin(), expectedResult.end());

  }
  catch (const std::exception& ex)
  {
    std::cerr << "all_unique_mapping_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(all_equal_mapping_test)
{
  try
  {
    std::list<std::string> testList{};

    size_t dummyOffset{};

    for (int idx{0}; idx < 1000; ++idx)
    {
      testList.push_back(std::to_string(dummyOffset) + "\t"
                         + "AbCdEf");

      dummyOffset += testList.back().size() + 1;
    }

    PrefixMapper mapper{};

    auto mapResult{mapper(testList)};

    std::list<std::string> expectedResult{"1\t1000", "2\t1000", "3\t1000",
                                          "4\t1000", "5\t1000", "6\t1000"};

    BOOST_CHECK_EQUAL_COLLECTIONS(mapResult.begin(), mapResult.end(),
                                  expectedResult.begin(), expectedResult.end());

  }
  catch (const std::exception& ex)
  {
    std::cerr << "all_equal_mapping_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()

