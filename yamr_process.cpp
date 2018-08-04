#include "yamr_process.h"
#include "yamr_engine.h"
#include "prefix_mapper.h"
#include "prefix_frequency_reducer.h"

int yamrRun(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "Usage: yamr <src> <mnum> <rnum>\n";
    return 1;
  }

  std::string sourceName{argv[1]};
  std::ifstream sourceFile{sourceName};
  if (!sourceFile)
  {
    std::cout << "Wrong source name!\n";
    return 1;
  }
  sourceFile.close();

  int  mapThreadCount{}, reduceThreadCount{};
  try
  {
    mapThreadCount = std::stoll(argv[2]);
    reduceThreadCount = std::stoll(argv[3]);
  }
  catch (...)
  {
    std::cout << "<mnum> and <rnum> should be integer\n";
    return 1;
  }

  if (mapThreadCount < 1
      || reduceThreadCount < 1)
  {
    std::cout << "<mnum> and <rnum> should be greater than 0\n";
    return 1;
  }

  SharedFunctor mapper{ new PrefixMapper() };
  SharedFunctor reducer{ new PrefixFrequencyReducer() };
  YamrEngine engine{static_cast<size_t>(mapThreadCount),
                    static_cast<size_t>(reduceThreadCount),
                    mapper, reducer};

  engine.mapReduce(sourceName);

  return 0;
}
