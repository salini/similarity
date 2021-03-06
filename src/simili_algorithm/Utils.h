#ifndef _SIMILI_ALGORITHM_UTILS_H_
#define _SIMILI_ALGORITHM_UTILS_H_

#include "DllExport.h"

#include <vector>
#include <string>

namespace simili_algorithm {

typedef std::pair<std::string, std::string> FilePair;
typedef std::vector< FilePair > FilePairs;

SIMILI_ALGORITHM_EXPORT std::vector<std::string> extractFilesFromFolder(const std::string& folderPath);

SIMILI_ALGORITHM_EXPORT size_t getFileSize_tellg(const std::string& filePath);
SIMILI_ALGORITHM_EXPORT size_t getFileSize(const std::string& filePath);

SIMILI_ALGORITHM_EXPORT bool filesAreEqual(const std::string& filePath0, const std::string& filePath1);
SIMILI_ALGORITHM_EXPORT bool filesAreEqual2(const std::string& filePath0, const std::string& filePath1);
} // namespace simili_algorithm


#endif
