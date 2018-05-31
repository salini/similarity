#ifndef _SIMILI_SIMILARCHECKERWIDGET_H_
#define _SIMILI_SIMILARCHECKERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT SimilarCheckerWidget : public QWidget {
    
Q_OBJECT

public:
    SimilarCheckerWidget();
    virtual ~SimilarCheckerWidget();

	void setFolder(const std::string& folderPath);


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    SimilarCheckerWidget(const SimilarCheckerWidget& other);

private slots:
	void processFolder();

	void progress_update(QString text, int value);
	void computation_finished();
};

} // namespace simili


#endif
