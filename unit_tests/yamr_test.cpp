// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE YAMR_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "yamr_engine.h"
#include "prefix_mapper.h"
#include "prefix_frequency_reducer.h"


BOOST_AUTO_TEST_SUITE(yamr_process_test)


BOOST_AUTO_TEST_CASE(full_process_test)
{
  try
  {
    std::ofstream testFile ("testfile.txt");

    char testCharLower {'a'};
    char testCharUpper {'T'};

    for (size_t idx{0}; idx < 20; ++idx)
    {
      std::string lowerString (9, testCharLower);
      std::string upperString (9, testCharUpper);

      testFile << lowerString << "\n";
      testFile << upperString << "\n";

      ++testCharLower;
      --testCharUpper;
    }

    testFile << std::string(9, 'u') << "\n";
    testFile << std::string(9, 'U');

    testFile.close();

    SharedFunctor testMapper{ new PrefixMapper()};
    SharedFunctor testReducer{ new PrefixFrequencyReducer()};

    YamrEngine testEngine{4, 9, testMapper, testReducer};

    testEngine.mapReduce("testfile.txt");

    StringList joinedReducedData{};

    for (size_t idx{1}; idx <= 9; ++idx)
    {
      std::string fileName{std::string{"reduced_data_"}
                           + std::to_string(idx)
                           + "_of_9.txt"};

      std::ifstream nextFile{fileName};

      BOOST_CHECK(static_cast<bool>(nextFile) == true);

      std::string nextString{};

      while(std::getline(nextFile, nextString))
      {
        joinedReducedData.push_back(nextString);
      }
    }

    joinedReducedData.sort();

    StringList expectedReducedData{};

    for (size_t length{1}; length <= 9; ++length)
    {
      std::stringstream expectedStream{};

      expectedStream << ">>>> PREFIX_LENGTH: " << std::to_string(length);

      auto expectedString{expectedStream.str()};

      expectedReducedData.push_back(expectedString);

      char testChar {'a'};
      for (size_t idx{0}; idx < 21; ++idx)
      {
        expectedStream.str("");

        expectedStream << std::string(length, testChar) << " 2";
        ++testChar;

        expectedString = expectedStream.str();
        expectedReducedData.push_back(expectedString);
      }
    }

    expectedReducedData.sort();

    BOOST_CHECK_EQUAL_COLLECTIONS(joinedReducedData.begin(),
                                  joinedReducedData.end(),
                                  expectedReducedData.begin(),
                                  expectedReducedData.end());

    for (size_t idx{1}; idx <= 9; ++idx)
    {
      std::string fileName{std::string{"reduced_data_"}
                           + std::to_string(idx)
                           + "_of_9.txt"};

      std::string command{"rm ./"+ fileName};
      std::system(command.c_str());
    }

    std::system("rm ./testfile.txt");
  }
  catch (const std::exception& ex)
  {
    std::cerr << "full_process_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

static const char characterSource[] =
  "0123456789"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";

BOOST_AUTO_TEST_CASE(random_list_test)
{
  try
  {
    std::srand(std::time(nullptr));

    std::ofstream testFile ("testfile.txt");

    size_t stringLength{}, listSize{};

    listSize = std::rand() % 1000 + 1;
    for (size_t idx{0}; idx < listSize; ++idx)
    {
      std::stringstream email{};

      stringLength = std::rand() % 20 + 1;
      for (size_t idx {0}; idx < stringLength; ++idx)
      {
        email << characterSource[rand() % (sizeof(characterSource) - 1)];
      }

      email << "@";

      stringLength = std::rand() % 20 + 1;
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

      testFile << emailString << "\n";
    }

    testFile << "list_end@pochta.ru";

    testFile.close();

    SharedFunctor testMapper{ new PrefixMapper()};
    SharedFunctor testReducer{ new PrefixFrequencyReducer()};

    YamrEngine testEngine{23, 17, testMapper, testReducer};

    testEngine.mapReduce("testfile.txt");

    std::set<std::string> joinedReducedData{};

    for (size_t idx{1}; idx <= 17; ++idx)
    {
      std::string fileName{std::string{"reduced_data_"}
                           + std::to_string(idx)
                           + "_of_17.txt"};

      std::ifstream nextFile{fileName};

      BOOST_CHECK(static_cast<bool>(nextFile) == true);

      std::string nextString{};

      while(std::getline(nextFile, nextString))
      {
        BOOST_CHECK(joinedReducedData.insert(nextString).second == true);
      }
    }

    for (size_t idx{1}; idx <= 17; ++idx)
    {
      std::string fileName{std::string{"reduced_data_"}
                           + std::to_string(idx)
                           + "_of_17.txt"};

      std::string command{"rm ./"+ fileName};
      std::system(command.c_str());
    }

    std::system("rm ./testfile.txt");
  }
  catch (const std::exception& ex)
  {
    std::cerr << "random_list_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()
