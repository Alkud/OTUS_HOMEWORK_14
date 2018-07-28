#pragma once

#include <string>
#include <functional>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <future>
#include <memory>
#include <fstream>

using StringList = std::list<std::string>;
using SharedStringList = std::shared_ptr<StringList>;

using ListStringList = std::list<StringList>;
using ListSharedStringList = std::list<SharedStringList>;

using MapReduceFunction = std::function<StringList(const StringList&)>;

using FileBounds = std::pair<size_t, size_t>;
using FileBoundsList = std::list<FileBounds>;

using PriorityStringQueue = std::priority_queue<std::string,
                                                std::deque<std::string>,
                                                std::greater<std::string>>;

enum class FileReadDirection
{
  forward,
  backward
};

class YarmEngine
{
public:  

  YarmEngine() = delete;
  YarmEngine(size_t newMappingThreadCount, size_t newReducingThreadCount);

  static FileBoundsList splitFile(const std::string& fileName, const size_t partsCount);

  static ListSharedStringList mapData(const std::string& fileName,
                                      const size_t resultPartsCount,
                                       MapReduceFunction mapper);

  const ListSharedStringList getMappedData();

  static ListSharedStringList mergeData(const ListSharedStringList& mappedData,
                                        const size_t resultPartsCount);

  const ListSharedStringList getMergedData();

  static ListSharedStringList reduceData(const ListSharedStringList& mappedData,
                                         MapReduceFunction reducer);

  const ListSharedStringList getReducedData();

  static void saveListToFile(const std::string& fileName, const SharedStringList& data);

private:

  struct SortedListsMerger
  {
    void offer(const std::string& nextString);

    SharedStringList getMergedData() const;

  private:
    std::mutex accessLock{};
    SharedStringList destination{nullptr};
    mutable PriorityStringQueue buffer;
  };

  static size_t FNVHash(const std::string& str);

  static int64_t findNewLine(std::ifstream& file,
                             const size_t size,
                             FileReadDirection direction);

  static SharedStringList readAndMap(const std::string& fileName,
                                     const FileBounds bounds,
                                     MapReduceFunction mapper,
                                     std::mutex& fileLock);

  static void dispenseSortedLists(const SharedStringList& listToDispense,
                                  const std::vector<std::shared_ptr<SortedListsMerger>>& mergers);


  size_t mappingThreadCount;
  size_t reducingThreadCount;

  ListSharedStringList splittedMappedData;
  ListSharedStringList mergedMappedData;
  ListSharedStringList reducedData;
};
