
#include "SimilarExtraction.h"

#include "SimilarByteComparison.h"

#include "Utils.h"

#include <set>

#include <ciso646> // to use "and"
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

    
	static FilePairs getSetOfFilePairs(const FilePairs& unsortedFilePairs) {
		std::set< std::pair<std::string, std::string> > similarSet;
		for (FilePairs::const_iterator it = unsortedFilePairs.begin(); it != unsortedFilePairs.end(); it++) {
			if ((*it).first > (*it).second) {
				similarSet.insert(std::make_pair((*it).second, (*it).first) );
			}
			else {
				similarSet.insert((*it));
			}
		}
		FilePairs similars;
		similars.insert(similars.end(), similarSet.begin(), similarSet.end());
		return similars;
	}
};


SimilarExtraction::SimilarExtraction()
    : pimpl( new Pimpl() )
{ 
}

SimilarExtraction::~SimilarExtraction() {
    delete pimpl;
}


#include <iostream> //TODO to delete
FilePairs SimilarExtraction::extractSimilars(const std::string& folderPath, std::map<std::string, bool>& options) {
	std::vector<std::string> filesFromFolder = extractFilesFromFolder(folderPath);

	FilePairs similarAll;
	if (options.count("byte comparison") > 0 and options["byte comparison"] == true) {
		FilePairs similar00 = SimilarByteComparison::extractSimilars(filesFromFolder);
		similarAll.insert(similarAll.end(), similar00.begin(), similar00.end());
	}

	//TODO to delete, just to test another
	if (options.count("byte comparison") > 0 and options["byte comparison"] == true) {
		FilePairs similar00 = SimilarByteComparison::extractSimilars(filesFromFolder);
		similarAll.insert(similarAll.end(), similar00.begin(), similar00.end());
	}

	return Pimpl::getSetOfFilePairs(similarAll);
}

