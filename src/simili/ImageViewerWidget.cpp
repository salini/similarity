
#include "ImageViewerWidget.h"

using namespace simili;


struct ImageViewerWidget::Pimpl {

	QImageReader	imageReader;
	QPixmap			originalPixmap;

    Pimpl() {;
		imageReader.setDecideFormatFromContent(true);
    }

	~Pimpl() {
    }

	void clear() {
	}

	void setImage(const std::string& filePath) {
		imageReader.setFileName(filePath.c_str());
		originalPixmap = QPixmap::fromImageReader(&imageReader);
	}
};


ImageViewerWidget::ImageViewerWidget()
    : pimpl( new Pimpl() )
{ 
}

ImageViewerWidget::~ImageViewerWidget() {
    delete pimpl;
}


void ImageViewerWidget::setImage(const std::string& filePath) {
	pimpl->setImage(filePath);
	displayImage();
}

size_t ImageViewerWidget::getOriginalWidth() const {
	return pimpl->originalPixmap.width();
}

size_t ImageViewerWidget::getOriginalHeight() const {
	return pimpl->originalPixmap.height();
}

void ImageViewerWidget::displayImage() {
	setPixmap(pimpl->originalPixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}

void ImageViewerWidget::resizeEvent(QResizeEvent *event) {
	displayImage();
}

void ImageViewerWidget::clear() {
	QLabel::clear();
	pimpl->clear();
}