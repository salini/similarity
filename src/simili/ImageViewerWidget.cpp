
#include "ImageViewerWidget.h"

using namespace simili;


struct ImageViewerWidget::Pimpl {

    Pimpl() {
    }

	~Pimpl() {
    }

    void setup() {
    }
};


ImageViewerWidget::ImageViewerWidget()
    : pimpl( new Pimpl() )
{ 
}

ImageViewerWidget::~ImageViewerWidget() {
    delete pimpl;
}


