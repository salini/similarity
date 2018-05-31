#ifndef _SIMILI_IMGDISPLAYERWIDGET_H_
#define _SIMILI_IMGDISPLAYERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT ImgDisplayerWidget : public QWidget {
    
Q_OBJECT

public:
    ImgDisplayerWidget(size_t minWidth=600, size_t minHeight=600);

    virtual ~ImgDisplayerWidget();


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ImgDisplayerWidget(const ImgDisplayerWidget& other);

private slots:
void delBtn_clicked();
};

} // namespace simili


#endif
