#ifndef _SIMILI_COMPUTEPAIRSTHREAD_H_
#define _SIMILI_COMPUTEPAIRSTHREAD_H_

#include "DllExport.h"
#include "LabeledProgressBar.h"

#include "simili_algorithm/Utils.h"

#include <QtWidgets>


namespace simili {

class SIMILI_EXPORT ComputePairsThread : public QThread {
    
Q_OBJECT

public:
    ComputePairsThread();
    virtual ~ComputePairsThread();

	void init(const std::string& folderPath, std::map<std::string, bool>& options);
	virtual void run();

	simili_algorithm::FilePairs getLastResult();  // I didn't register FilePairs in possible Qt data that can be transmitted though signal/slot process

private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ComputePairsThread(const ComputePairsThread& other);

private slots:

signals:
	void progress_update(QString text);
	void progress_update(int value);
	void error_raised(QString error);
	void computation_finished();
};

} // namespace simili


#endif
