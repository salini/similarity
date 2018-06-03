
#include "SimilarExtraction.h"

#include "SimilarByteComparison.h"

#include "Utils.h"

//#include <boost/format.hpp>
//
//#include <boost/filesystem.hpp>
//#include <boost/range/iterator_range.hpp>
//#include <iostream>
//#include <stdexcept>
//#include <vector>


//using namespace boost::filesystem;

using namespace simili_algorithm;


struct SimilarExtraction::Pimpl {

    
    Pimpl() {
    }

	~Pimpl() {
    }

    
};


SimilarExtraction::SimilarExtraction()
    : pimpl( new Pimpl() )
{ 
}

SimilarExtraction::~SimilarExtraction() {
    delete pimpl;
}


FilePairs SimilarExtraction::extractSimilars(const std::string& folderPath, std::map<std::string, bool>& options) {
	std::vector<std::string> filesFromFolder = extractFilesFromFolder(folderPath);

	//TODO add options!!
	FilePairs similar00 = SimilarByteComparison::extractSimilars(filesFromFolder);

	return similar00;
}