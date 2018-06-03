
#include "Utils.h"

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost::filesystem;

//using namespace simili_algorithm;


std::vector<std::string> simili_algorithm::extractFilesFromFolder(const std::string& folderPath) {
	std::vector<std::string> filesInFolder;
	if (is_directory(folderPath)) {
		for (auto& entry : boost::make_iterator_range(directory_iterator(folderPath), {}))
			if (is_regular_file(entry)) {
				//std::cout << entry << "\n"; ;
				filesInFolder.push_back(entry.path().string());
			}
	}
	else {
		//std::cout << folderPath << " is NOT a directory\n";
		throw std::runtime_error(boost::str(boost::format("'%s' is NOT a directory") % folderPath));
	}
	return filesInFolder;
}


size_t simili_algorithm::getFileSize(const std::string& filePath) {
	std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
