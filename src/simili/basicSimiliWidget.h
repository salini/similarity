#ifndef _SIMILI_BASICSIMILIWIDGET_H_
#define _SIMILI_BASICSIMILIWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>


namespace simili {

class SIMILI_EXPORT basicSimiliWidget : public QWidget {
    
Q_OBJECT

public:
    basicSimiliWidget();
    virtual ~basicSimiliWidget();


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    basicSimiliWidget(const basicSimiliWidget& other);

private slots:

};

} // namespace simili


#endif
