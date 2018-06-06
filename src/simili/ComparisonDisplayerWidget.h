#ifndef _SIMILI_COMPARISONDISPLAYERWIDGET_H_
#define _SIMILI_COMPARISONDISPLAYERWIDGET_H_

#include "DllExport.h"
#include "simili_algorithm/Utils.h"

#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT ComparisonDisplayerWidget : public QWidget {
    
Q_OBJECT

public:
    ComparisonDisplayerWidget();
    virtual ~ComparisonDisplayerWidget();

	void setFilePairs(const simili_algorithm::FilePairs& filePairs);
	void displayPair(size_t pair_index);


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ComparisonDisplayerWidget(const ComparisonDisplayerWidget& other);

private slots:
	void displayBack();
	void displayNext();
	void fileDeleted(QString FilePath);
};

} // namespace simili


#endif
