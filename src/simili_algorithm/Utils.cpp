
#include "Utils.h"

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include <sys/stat.h>


using namespace boost::filesystem;
namespace io = boost::iostreams;


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


size_t simili_algorithm::getFileSize_tellg(const std::string& filePath) {
	std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

size_t simili_algorithm::getFileSize(const std::string& filePath)
{
	struct stat stat_buf;
	int rc = stat(filePath.c_str(), &stat_buf);
	return stat_buf.st_size;
	//return rc == 0 ? stat_buf.st_size : -1;
}


////http://www.cplusplus.com/forum/general/94032/
#include <iostream> //TODO remove
bool simili_algorithm::filesAreEqual(const std::string& filePath0, const std::string& filePath1) {
	io::mapped_file_source f1(filePath0);
	io::mapped_file_source f2(filePath1);

	if (f1.size() == f2.size() && std::equal(f1.data(), f1.data() + f1.size(), f2.data())) {
		return true;
	}
	else {
		return false;
	}
}

bool simili_algorithm::filesAreEqual2(const std::string& filePath0, const std::string& filePath1) {
	static int BUFFER_SIZE = 1000000;
	std::ifstream lFile(filePath0.c_str(), std::ifstream::in | std::ifstream::binary);
	std::ifstream rFile(filePath1.c_str(), std::ifstream::in | std::ifstream::binary);
	std::streamsize numberOfRead;

	if (!lFile.is_open() || !rFile.is_open())
	{
		return false;
	}

	char *lBuffer = new char[BUFFER_SIZE]();
	char *rBuffer = new char[BUFFER_SIZE]();

	do {
		lFile.read(lBuffer, BUFFER_SIZE);
		rFile.read(rBuffer, BUFFER_SIZE);
		numberOfRead = lFile.gcount();//I check the files with the same size

		if (std::memcmp(lBuffer, rBuffer, numberOfRead) != 0)
		{
			memset(lBuffer, 0, numberOfRead);
			memset(rBuffer, 0, numberOfRead);
			return false;
		}
	} while (lFile.good() || rFile.good());

	delete[] lBuffer;
	delete[] rBuffer;
	return true;
}



