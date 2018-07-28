#include "yarm_engine.h"
#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <iterator>

YarmEngine::YarmEngine(
    size_t newMappingThreadCount,
    size_t newReducingThreadCount) :
  mappingThreadCount{newMappingThreadCount},
  reducingThreadCount{newReducingThreadCount},
  splittedMappedData{}, mergedMappedData{nullptr}
{

}

FileBoundsList YarmEngine::splitFile(const std::string& fileName, const size_t partsCount)
{
  std::ifstream fileToSplit{fileName, std::ifstream::ate | std::ifstream::binary};

  if (!fileToSplit)
  {
    throw std::invalid_argument{"File not found"};
  }

  if (partsCount <= 1)
  {
    throw std::invalid_argument{"Wrong number of parts"};
  }

  auto fileSize{static_cast<size_t>(fileToSplit.tellg())};

  FileBoundsList sectionBounds{};

  if (0 == fileSize)
  {
    return sectionBounds;
  }

  auto averageSectionSize{fileSize / partsCount};

  if (0 == averageSectionSize)
  {
    averageSectionSize = 1;
  }

  int64_t sectionBegin{0};
  int64_t sectionEnd{-1};

  for (size_t idx {1}; idx < partsCount; ++idx)
  {
    auto currentSeekPosition{idx * averageSectionSize};

    size_t previousSectionEnd{};
    if (sectionBounds.empty() != true)
    {
      previousSectionEnd = sectionBounds.back().second;
    }

    if (currentSeekPosition <= previousSectionEnd
        && previousSectionEnd < fileSize - 2)
    {
      currentSeekPosition = previousSectionEnd + 1;
    }

    fileToSplit.seekg(currentSeekPosition);    

    if (fileToSplit.peek() != '\n')
    {
      auto nextNewLinePosition{findNewLine(fileToSplit, fileSize, FileReadDirection::forward)};
      fileToSplit.seekg(currentSeekPosition);
      auto previousNewLinePosition{findNewLine(fileToSplit, fileSize, FileReadDirection::backward)};

      if (-1 == nextNewLinePosition)
      {
        /* next '\n' not found */
        if(-1 != previousNewLinePosition)
        {
          sectionEnd = previousNewLinePosition;
        }
      }
      else
      {
        /* previous '\n' not found */
        if(-1 == previousNewLinePosition)
        {
          sectionEnd = nextNewLinePosition;
        }
        else
        {
          sectionEnd =
              (currentSeekPosition - previousNewLinePosition)
              > (nextNewLinePosition - currentSeekPosition)
              ? nextNewLinePosition : previousNewLinePosition;
        }
      }
    }
    else
    {
      sectionEnd = currentSeekPosition;
    }

    if (-1 == sectionEnd)
    {
      break;
    }

    if (sectionEnd != static_cast<int64_t>(previousSectionEnd))
    {
      sectionBounds.push_back(std::make_pair(sectionBegin, sectionEnd));
      if (sectionEnd < static_cast<int64_t>(fileSize - 2))
      {
        sectionBegin = sectionEnd + 1;
      }
    }
  }

  sectionBounds.push_back(std::make_pair(sectionBegin, fileSize - 1));

  return sectionBounds;
}

ListSharedStringList YarmEngine::mapData(const std::string& fileName,
                                         const size_t resultPartsCount,
                                         MapReduceFunction mapper)
{
  auto sectionBounds{splitFile(fileName, resultPartsCount)};

  std::vector<std::future<SharedStringList>> mappingResults{};

  std::mutex fileLock{};

  for (const auto& bounds : sectionBounds)
  {
    mappingResults.push_back(std::async(std::launch::async,
                                        &YarmEngine::readAndMap,
                                        std::ref(fileName), bounds,
                                        mapper, std::ref(fileLock)));
  }

  ListSharedStringList mappedData{};

  for (auto& result : mappingResults)
  {
    if (result.valid())
    {
      auto nextList{result.get()};
      nextList->sort();
      mappedData.push_back(nextList);
    }
  }

  return mappedData;
}

const ListSharedStringList YarmEngine::getMappedData()
{
  return splittedMappedData;
}

ListSharedStringList YarmEngine::mergeData(const ListSharedStringList& mappedData,
                                           const size_t resultPartsCount)
{
  std::vector<std::thread> shufflingThreads{};

  std::vector<std::shared_ptr<SortedListsMerger>> mergers{};

  ListSharedStringList mergedData{};

  for (size_t idx{}; idx < resultPartsCount; ++idx)
  {
    mergers.emplace_back(new SortedListsMerger{});
  }

  for (const auto& listToMerge : mappedData)
  {
    shufflingThreads.push_back(std::thread{&YarmEngine::dispenseSortedLists,
                                        std::ref(listToMerge),
                                        mergers});
  }

  for (auto& thread : shufflingThreads)
  {
    if (thread.joinable())
    {
      thread.join();
    }
  }

  std::vector<std::future<SharedStringList>> mergingResults{};

  for (const auto& merger : mergers)
  {
    mergingResults.push_back(std::async(std::launch::async,
                                        [merger](){return merger->getMergedData();}));
  }

  for (auto& result : mergingResults)
  {
    if (result.valid())
    {
      mergedData.push_back(result.get());
    }
  }

  return mergedData;
}

const ListSharedStringList YarmEngine::getMergedData()
{
  return mergedMappedData;
}

ListSharedStringList YarmEngine::reduceData(const ListSharedStringList& mappedData,
                                            MapReduceFunction reducer)
{

}

const ListSharedStringList YarmEngine::getReducedData()
{

}

void YarmEngine::saveListToFile(const std::string& fileName, const SharedStringList& data)
{
  std::ofstream outputFile{fileName};

  if (!outputFile)
  {
    std::cerr << "Can not create file " << fileName << "\n";
    throw std::ios_base::failure {"File creation error"};
  }

  for (const auto& nextString : *data)
  {
    outputFile << nextString << "\n";
  }

  outputFile.close();

  std::ifstream checkFile{fileName};

  if (!checkFile)
  {
    std::cerr << "Can not write to file " << fileName << "\n";
    throw std::ios_base::failure {"File writing error"};
  }
}

size_t YarmEngine::FNVHash(const std::string& str)
{
  const size_t fnv_prime {1099511628211u};
  size_t hash {14695981039346656037u};
  auto stringLength {str.length()};

  for (size_t idx{0}; idx < stringLength; ++idx)
  {
    hash *= fnv_prime;
    hash ^= (str[idx]);
  }

  return hash;
}


int64_t YarmEngine::findNewLine(std::ifstream& file, const size_t fileSize, FileReadDirection direction)
{
  auto currentPosition {static_cast<size_t>(file.tellg())};
  if (FileReadDirection::forward == direction)
  {
    while(currentPosition < fileSize - 1)
    {
      ++currentPosition;
      file.seekg(currentPosition);
      if (file.peek() == '\n')
      {
        return currentPosition;
      }
    }

    return -1;
  }
  else
  {
    while(currentPosition > 0)
    {
      --currentPosition;
      file.seekg(currentPosition);
      if (file.peek() == '\n')
      {
        return currentPosition;
      }
    }

    return -1;
  }
}


SharedStringList YarmEngine::readAndMap(const std::string& fileName,
                                        const FileBounds bounds,
                                        MapReduceFunction mapper,
                                        std::mutex& fileLock)
{
  try
  {
    const auto startPosition{bounds.first};
    const auto endPosition{bounds.second};

    StringList localData{};

    {
      std::lock_guard<std::mutex> lockFile{fileLock};
      std::ifstream inputFile{fileName};

      if (!inputFile)
      {
        return nullptr;
      }

      inputFile.seekg(startPosition);

      auto currentPosition{startPosition};

      std::string nextString{};

      while(inputFile
            && inputFile.tellg() < static_cast<std::ofstream::pos_type>(endPosition))
      {
        if (std::getline(inputFile, nextString))
        {
          std::transform(nextString.begin(), nextString.end(),
                         nextString.begin(), ::tolower);

          localData.push_back(std::to_string(currentPosition) + "\t" + nextString);
          currentPosition = inputFile.tellg();
        }
      }
    }

    return std::make_shared<StringList>(mapper(localData));
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what();
    return nullptr;
  }
}



void YarmEngine::dispenseSortedLists(const SharedStringList& listToDispense,
                                     const std::vector<std::shared_ptr<SortedListsMerger> >& mergers)
{
  try
  {
    size_t mergerCount{mergers.size()};
    size_t mergerIndex{};
    size_t nextHash{};

    while(listToDispense->empty() != true)
    {
      auto nextString{listToDispense->front()};
      listToDispense->pop_front();

      auto tabPosition{nextString.find('\t', 0)};
      auto nextKey {tabPosition != std::string::npos
                    ? nextString.substr(0, tabPosition) : nextString};

      nextHash = FNVHash(nextKey);

      mergerIndex = nextHash % mergerCount;

      mergers[mergerIndex]->offer(nextString);
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what();
    return;
  }
}



void YarmEngine::SortedListsMerger::offer(const std::string& nextString)
{
  std::lock_guard<std::mutex> lockAccess{accessLock};
  buffer.push(nextString);
}

SharedStringList YarmEngine::SortedListsMerger::getMergedData() const
{
  try
  {
    auto result{std::make_shared<StringList>()};

    while(buffer.empty() != true)
    {
      result->push_back(buffer.top());
      buffer.pop();
    }

    return result;
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what();
    return nullptr;
  }
}

