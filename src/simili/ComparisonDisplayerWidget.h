#ifndef _SIMILI_COMPARISONDISPLAYERWIDGET_H_
#define _SIMILI_COMPARISONDISPLAYERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT ComparisonDisplayerWidget : public QWidget {
    
Q_OBJECT

public:
    ComparisonDisplayerWidget();
    virtual ~ComparisonDisplayerWidget();


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ComparisonDisplayerWidget(const ComparisonDisplayerWidget& other);

private slots:
	void displayBack();
	void displayNext();
};

} // namespace simili


#endif
