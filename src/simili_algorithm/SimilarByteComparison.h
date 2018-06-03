#ifndef _SIMILI_ALGORITHM_SIMILARBYTECOMPARISON_H_
#define _SIMILI_ALGORITHM_SIMILARBYTECOMPARISON_H_

#include "DllExport.h"
#include "Utils.h"

#include <vector>
#include <string>


namespace simili_algorithm {

class SIMILI_ALGORITHM_EXPORT SimilarByteComparison {
    
public:
    SimilarByteComparison();
    virtual ~SimilarByteComparison();

	static FilePairs extractSimilars(const std::vector<std::string>& comparingFiles);


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    SimilarByteComparison(const SimilarByteComparison& other);

};

} // namespace simili_algorithm


#endif
