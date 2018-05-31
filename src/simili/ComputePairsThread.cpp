
#include "ComputePairsThread.h"

#include <boost/format.hpp>

#include <thread>


using namespace simili;


struct ComputePairsThread::Pimpl {

	std::string folderPath;
	std::map<std::string, bool> options;

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
	for (size_t idx = 0; idx < 5; idx++) {
		emit progress_update(QString(boost::str(boost::format("AAA '%i'") % idx).c_str()), idx * 20);
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000));
	}
	emit computation_finished();
}