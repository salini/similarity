#ifndef _SIMILI_ALGORITHM_SIMILAREXTRACTION_H_
#define _SIMILI_ALGORITHM_SIMILAREXTRACTION_H_

#include "DllExport.h"
#include "Utils.h"

#include <map>
#include <string>


namespace simili_algorithm {

class SIMILI_ALGORITHM_EXPORT SimilarExtraction {
    
public:
    SimilarExtraction();
    virtual ~SimilarExtraction();

	static FilePairs extractSimilars(const std::string& folderPath, std::map<std::string, bool>& options);

private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    SimilarExtraction(const SimilarExtraction& other);

};

} // namespace simili_algorithm


#endif
