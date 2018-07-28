// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE ENGINE_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

#include "yarm_engine.h"


BOOST_AUTO_TEST_SUITE(yarm_engine_test)


BOOST_AUTO_TEST_CASE(file_split_test)
{
  try
  {
    std::ofstream testFile ("testfile.txt");

    for (size_t idx{1000000}; idx < 1000100; ++idx)
    {
      auto splitBounds{YarmEngine::splitFile("testfile.txt", 5)};
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << "file_split_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(unknown_commands_test)
{
  try
  {
  }
  catch (const std::exception& ex)
  {
    std::cerr << "unknown_commands_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(bad_requests_test)
{
  try
  {
  }
  catch (const std::exception& ex)
  {
    std::cerr << "bad_requests_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()
