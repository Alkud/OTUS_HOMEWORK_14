// engine_test.cpp in OTUS Homework 14 project

#define BOOST_TEST_MODULE ENGINE_TEST

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>

#include "yamr_engine.h"


BOOST_AUTO_TEST_SUITE(yamr_engine_test)

static const char characterSource[] =
  "0123456789"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";


BOOST_AUTO_TEST_CASE(file_split_test)
{
  try
  {
    std::ofstream testFileWrite ("testfile.txt");

    for (size_t idx{0}; idx < 100; ++idx)
    {
      testFileWrite << std::to_string(std::rand() % 100)
                    << "@" << std::to_string(std::rand() % 10000)
                    << "." << std::to_string(std::rand() % 1000) << "\n";
    }

    testFileWrite << "list_end@pochta.ru";

    testFileWrite.close();

    auto splitBounds{YamrEngine::splitFile("testfile.txt", 7)};

    std::ifstream testFileRead ("testfile.txt", std::ifstream::ate | std::ifstream::binary);

    auto fileSize{static_cast<size_t>(testFileRead.tellg())};

    BOOST_CHECK(splitBounds.size() == 7);

    for (const auto& bounds : splitBounds)
    {
      testFileRead.seekg(bounds.first);
      BOOST_CHECK(testFileRead.peek() != '\n');
      testFileRead.seekg(bounds.second);
      BOOST_CHECK(testFileRead.peek() == '\n'
                  || bounds.second == fileSize - 1);
    }

    std::system("rm ./testfile.txt");
  }
  catch (const std::exception& ex)
  {
    std::cerr << "file_split_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(bad_split_test)
{
  try
  {
    std::ofstream oneStringFile ("one_string_file.txt");

    std::stringstream oneLongString{};
    oneLongString << "Quite a long string, containing no email address";
    oneStringFile << oneLongString.str();
    oneStringFile.close();

    auto splitBounds{YamrEngine::splitFile("one_string_file.txt", 12)};

    BOOST_CHECK(splitBounds.size() == 1);
    BOOST_CHECK(splitBounds.back().first == 0);
    BOOST_CHECK(splitBounds.back().second == oneLongString.str().size() - 1);

    std::system("rm ./one_string_file.txt");

    std::ofstream emptyStringsFile ("empty_strings_file.txt");

    emptyStringsFile << "\n\n\n\n\nend of file";
    emptyStringsFile.close();

    splitBounds = YamrEngine::splitFile("empty_strings_file.txt", 6);

    FileBoundsList expectedBounds {{0,2}, {3,4}, {5,15}};

    BOOST_CHECK(splitBounds.size() == 3);
    BOOST_CHECK(splitBounds == expectedBounds);

    std::system("rm ./empty_strings_file.txt");
  }
  catch (const std::exception& ex)
  {
    std::cerr << "bad_split_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

class DummyMapper : public MapperReducerBase
{
  void operator()(const std::string& inputString, StringList& destination) override
  {
    destination.push_back(inputString);
  }
};

BOOST_AUTO_TEST_CASE(multithread_split_test)
{
  try
  {
    std::srand(std::time(nullptr));

    std::ofstream testFile ("testfile.txt");

    StringList expectedMappedData{};

    size_t stringLength{};

    size_t expectedOffset{};
    for (size_t idx{0}; idx < 100; ++idx)
    {
      std::stringstream email{};

      stringLength = std::rand() % 20 + 1;
      for (size_t idx {0}; idx < stringLength; ++idx)
      {
        email << characterSource[rand() % (sizeof(characterSource) - 1)];
      }

      email << "@";
      stringLength = std::rand() % 8 + 1;
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
      testFile << email.str() << "\n";

      std::transform(emailString.begin(), emailString.end(),
                     emailString.begin(), ::tolower);

      expectedMappedData.push_back(std::to_string(expectedOffset)
                                   + "\t" + emailString);
      expectedOffset += emailString.size() + 1;
    }

    expectedMappedData.push_back(std::to_string(expectedOffset)
                                 + "\t" + "list_end@pochta.ru");
    testFile << "list_end@pochta.ru";

    testFile.close();    

    auto dummyMapper {std::make_shared<DummyMapper>()};

    auto testMappedData{YamrEngine::mapData("testfile.txt", 5, dummyMapper)};

    StringList joinedMappedData{};

    for (const auto& nextList : testMappedData)
    {
      for (const auto& nextString : *nextList)
      {
        joinedMappedData.push_back(nextString);
      }
    }

    expectedMappedData.sort();
    joinedMappedData.sort();

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedMappedData.begin(), expectedMappedData.end(),
                                  joinedMappedData.begin(), joinedMappedData.end());

    std::system("rm ./testfile.txt");
  }
  catch (const std::exception& ex)
  {
    std::cerr << "multithread_split_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_CASE(merge_test)
{
  try
  {
    ListSharedStringList testMappedData{};

    ListSharedStringList expectedMergedData{};

    for (size_t idx{0}; idx < 6; ++idx)
    {
      testMappedData.emplace_back(new StringList());
    }

    for (size_t prefixLength{1}; prefixLength <= 7; ++prefixLength)
    {
      expectedMergedData.emplace_back(new StringList());

      std::stringstream mergedStream{};

      mergedStream << std::to_string(prefixLength) << "\t";

      char prefixChar{'A'};
      for (auto& mappedList : testMappedData)
      {
        mappedList->push_back(std::to_string(prefixLength)
                              + "\t"
                              + std::string(prefixLength, prefixChar));

        mergedStream << std::string(prefixLength, prefixChar) << " ";

        ++prefixChar;
      }

      auto mergedString{mergedStream.str()};
      expectedMergedData.back()->push_back(mergedString.substr(0, mergedString.size() - 1));

    }

    auto actualMergedData{YamrEngine::mergeData(testMappedData, 7)};

    StringList joinedActualMergedData{};

    for (const auto& nextList : actualMergedData)
    {
      for (const auto& nextString : *nextList)
      {
        joinedActualMergedData.push_back(nextString);
      }
    }

    joinedActualMergedData.sort();

    StringList joinedExpectedMergedData{};

    for (const auto& nextList : expectedMergedData)
    {
      for (const auto& nextString : *nextList)
      {
        joinedExpectedMergedData.push_back(nextString);
      }
    }

    joinedExpectedMergedData.sort();

    BOOST_CHECK_EQUAL_COLLECTIONS(joinedActualMergedData.begin(),
                                  joinedActualMergedData.end(),
                                  joinedActualMergedData.begin(),
                                  joinedActualMergedData.end());
  }
  catch (const std::exception& ex)
  {
    std::cerr << "merge_test failed. " << ex.what();
    BOOST_FAIL("");
  }
}

BOOST_AUTO_TEST_SUITE_END()
