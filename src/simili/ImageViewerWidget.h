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

	void setImage(const std::string& filePath);
	size_t getOriginalWidth() const;
	size_t getOriginalHeight() const;

	virtual void resizeEvent(QResizeEvent *event);

	virtual void clear();


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    ImageViewerWidget(const ImageViewerWidget& other);

	void displayImage();

private slots:

};

} // namespace simili


#endif
