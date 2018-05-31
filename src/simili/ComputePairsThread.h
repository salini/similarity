#ifndef _SIMILI_COMPUTEPAIRSTHREAD_H_
#define _SIMILI_COMPUTEPAIRSTHREAD_H_

#include "DllExport.h"
#include <QtWidgets>

#include "LabeledProgressBar.h"


namespace simili {

class SIMILI_EXPORT ComputePairsThread : public QThread {
    
Q_OBJECT

public:
    ComputePairsThread();
    virtual ~ComputePairsThread();

	void init(const std::string& folderPath, std::map<std::string, bool>& options);
	virtual void run();

private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ComputePairsThread(const ComputePairsThread& other);

private slots:

signals:
	void progress_update(QString text, int value);
	void computation_finished();
};

} // namespace simili


#endif
