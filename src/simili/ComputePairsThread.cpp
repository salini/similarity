
#include "ComputePairsThread.h"

#include "simili_algorithm/SimilarExtraction.h"

#include <boost/format.hpp>

#include <thread>
#include <stdexcept>

using namespace simili;
using namespace simili_algorithm;

struct ComputePairsThread::Pimpl {

	std::string folderPath;
	std::map<std::string, bool> options;

	FilePairs filepairs;

    Pimpl() {
    }

	~Pimpl() {
    }
};


ComputePairsThread::ComputePairsThread()
    : pimpl( new Pimpl() )
{ 
}

ComputePairsThread::~ComputePairsThread() {
    delete pimpl;
}

void ComputePairsThread::init(const std::string& folderPath, std::map<std::string, bool>& options) {
	pimpl->folderPath = folderPath;
	pimpl->options.clear();
	pimpl->options = options;
}


void ComputePairsThread::run() {
	emit progress_update("INIT");
	emit progress_update(0);
	try {
		pimpl->filepairs = SimilarExtraction::extractSimilars(pimpl->folderPath, pimpl->options);
	}
	catch (std::runtime_error& e) {
		emit error_raised(e.what());
	}
	
	emit progress_update(100);

	emit computation_finished();
}

FilePairs ComputePairsThread::getLastResult() {
	return pimpl->filepairs;
}