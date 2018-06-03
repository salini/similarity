
#include "QGIFMovie.h"

using namespace simili;

#include <iostream>


struct QGIFMovie::Pimpl {

	QLabel&		label;
	QMovie*		vid;

	size_t original_width;
	size_t original_height;

    Pimpl(QLabel& label_)
		: label(label_)
		, vid(NULL)
	{
		setNewMovie("");
    }

	~Pimpl() {
		deleteMovie();
    }

	void deleteMovie() {
		if (vid != NULL) {
			delete vid;
			vid = NULL;
			original_width = 0;
			original_height = 0;
		}
	}

	void setNewMovie(const std::string& filePath) {
		deleteMovie();
		vid = new QMovie(filePath.c_str());
		vid->jumpToNextFrame();  // just to get access to the first frame, to read, width and height
		QPixmap pix = vid->currentPixmap();
		original_width = pix.width();
		original_height = pix.height();
	}
};


QGIFMovie::QGIFMovie(QLabel& label)
    : pimpl( new Pimpl(label) )
{ 
}

QGIFMovie::~QGIFMovie() {
    delete pimpl;
}

void QGIFMovie::setGIF(const std::string& filePath) {
	pimpl->setNewMovie(filePath);
	connect(pimpl->vid, SIGNAL(frameChanged(int)), this, SLOT(updatePixmap(int)));
}

void QGIFMovie::updatePixmap(int frameNumber) {
	int w = pimpl->label.width();
	int h = pimpl->label.height();
	if (pimpl->vid) {
		pimpl->label.setPixmap(pimpl->vid->currentPixmap().scaled(w, h, Qt::KeepAspectRatio));
	}
}

void QGIFMovie::start() {
	if (pimpl->vid) {
		pimpl->vid->start();
	}
}

void QGIFMovie::stop() {
	if (pimpl->vid) {
		pimpl->vid->stop();
	}
}

void QGIFMovie::clear() {
	stop();
	pimpl->deleteMovie();
}

size_t QGIFMovie::getOriginalWidth() const {
	return pimpl->original_width;
}

size_t QGIFMovie::getOriginalHeight() const {
	return pimpl->original_height;
}