#ifndef _SIMILI_IMAGEVIEWERWIDGET_H_
#define _SIMILI_IMAGEVIEWERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT ImageViewerWidget : public QLabel {
    
Q_OBJECT

public:
    ImageViewerWidget();
    virtual ~ImageViewerWidget();


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ImageViewerWidget(const ImageViewerWidget& other);

private slots:

};

} // namespace simili


#endif
