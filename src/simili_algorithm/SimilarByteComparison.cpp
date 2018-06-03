
#include "SimilarByteComparison.h"

#include "Utils.h"

#include <algorithm>    // std::sort
#include <map>
#include <utility>      // std::make_pair


using namespace std;

using namespace simili_algorithm;


struct SimilarByteComparison::Pimpl {

    
    Pimpl() {
    }

	~Pimpl() {
    }
};


SimilarByteComparison::SimilarByteComparison()
    : pimpl( new Pimpl() )
{ 
}

SimilarByteComparison::~SimilarByteComparison() {
    delete pimpl;
}


struct FileSizeStruct
{
	std::string filePath;
	size_t		size;

	inline bool operator< (const FileSizeStruct& other) {
		return (this->size < other.size);
	}
};


#include <iostream> //TODO to delete
FilePairs SimilarByteComparison::extractSimilars(const std::vector<std::string>& comparingFiles) {
	std::vector<FileSizeStruct> results;

	for (std::vector<std::string>::const_iterator it = comparingFiles.begin(); it != comparingFiles.end(); it++) {
		results.push_back({(*it), getFileSize((*it))});
	}

	std::sort(results.begin(), results.end());

	/*
	for (std::vector<FileSizeStruct>::const_iterator it = results.begin(); it != results.end(); it++) {
		std::cout << (*it).size << " // " << (*it).filePath << std::endl;
	}
	*/
	
	FilePairs filePairs;
	for (std::vector<FileSizeStruct>::const_iterator it = results.begin(); it != results.end()-1; it++) {
		if ((*it).size == (*(it + 1)).size) {
			filePairs.push_back(std::make_pair((*it).filePath, (*(it + 1)).filePath));
		}
	}
	return filePairs;
}

