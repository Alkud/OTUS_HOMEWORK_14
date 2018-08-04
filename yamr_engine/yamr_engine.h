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
#include "../mapper_reducer/mapper_reducer_base.h"

using StringList = std::list<std::string>;
using SharedStringList = std::shared_ptr<StringList>;

using ListStringList = std::list<StringList>;
using ListSharedStringList = std::list<SharedStringList>;

using SharedFunctor = std::shared_ptr<MapperReducerBase>;

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

class YamrEngine
{
public:  

  YamrEngine() = delete;
  YamrEngine(size_t newMappingThreadCount,
             size_t newReducingThreadCount,
             const SharedFunctor& newMapper,
             const SharedFunctor& newReducer);

  static FileBoundsList splitFile(const std::string& fileName, const size_t partsCount);

  static ListSharedStringList mapData(const std::string& fileName,
                                      const size_t resultPartsCount,
                                      SharedFunctor mapper);

  const ListSharedStringList getMappedData();

  static ListSharedStringList mergeData(const ListSharedStringList& mappedData,
                                        const size_t resultPartsCount);

  const ListSharedStringList getMergedData();

  static ListSharedStringList reduceData(const ListSharedStringList& mergedData,
                                         SharedFunctor reducer);

  static ListSharedStringList reduceAndSaveData(const ListSharedStringList& mergedData,
                                                SharedFunctor reducer);

  const ListSharedStringList getReducedData();

  static void saveListToFile(const std::string& fileName,
                             const SharedStringList& data);

  void mapReduce(const std::string& fileName);

private:

  struct SortedListsMerger
  {
    void offer(const std::string& nextString);

    SharedStringList getMergedData() const;

  private:
    std::pair<std::string, std::string>
    extractKeyValue(const std::string& tabSeparatedData);

    mutable std::mutex accessLock{};
    SharedStringList destination{nullptr};
    std::map<std::string, std::multiset<std::string>> collector;
  };

  static size_t FNVHash(const std::string& str);

  static int64_t findNewLine(std::ifstream& file,
                             const size_t size,
                             FileReadDirection direction);

  static SharedStringList readAndMap(const std::string& fileName,
                                     const FileBounds bounds,
                                     SharedFunctor mapper,
                                     std::mutex& fileLock);

  static void dispenseSortedLists(const SharedStringList& listToDispense,
                                  const std::vector<std::shared_ptr<SortedListsMerger>>& mergers);
  
  static SharedStringList reduce(const SharedStringList& listToReduce,
                                 SharedFunctor reducer);


  size_t mappingThreadCount;
  size_t reducingThreadCount;

  SharedFunctor mapper;
  SharedFunctor reducer;

  ListSharedStringList splittedMappedData;
  ListSharedStringList mergedMappedData;
  ListSharedStringList reducedData;
};
