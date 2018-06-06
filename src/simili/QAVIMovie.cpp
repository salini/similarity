
#include "QAVIMovie.h"

#include "opencv2/opencv.hpp"

using namespace simili;


struct MovieHandler {
	cv::VideoCapture	vid;
	double				fps;
	cv::Mat				frame;
	QPixmap				pix;
	std::string			filePath;

	MovieHandler(const std::string& filePath_)
		: vid(filePath_)
		, fps(0.0)
		, filePath(filePath_)
	{
		if (isValid()) {
			fps = vid.get(cv::CAP_PROP_FPS);
			jumpToNextFrame();
		}
	};

	~MovieHandler() {
		if (isValid()) {
			vid.release();
		}
	}

	bool isValid() {
		return vid.isOpened();
	}

	void jumpToNextFrame() {
		vid >> frame;
		if (frame.empty()) {
			vid.release();
			vid.open(filePath);
			vid >> frame;
		}
		pix = QPixmap::fromImage(QImage((unsigned char*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped());

		//static int idx;
		//std::cout << idx++ <<"\n";
	}

	QPixmap currentPixmap() {
		return pix;
	}

	size_t width() {
		return pix.width();
	}

	size_t height() {
		return pix.height();
	}
};

struct QAVIMovie::Pimpl {

	QLabel&				label;
	MovieHandler*		vid;
	QTimer				timer;

	size_t original_width;
	size_t original_height;
	double fps;

    Pimpl(QLabel& label_)
		: label(label_)
		, vid(NULL)
		, timer(&label)
	{
    }

	~Pimpl() {
		deleteMovie();
    }

	void deleteMovie() {
		if (vid != NULL) {
			delete vid;
			vid = NULL;
		}
		original_width = 0;
		original_height = 0;
		fps = 1;
	}


	void setNewMovie(const std::string& filePath) {
		deleteMovie();
		vid = new MovieHandler(filePath);
		if (!vid->isValid()) {
			std::cout << "Error opening video stream or file" << endl;
			deleteMovie();
		}
		else {
			original_width = vid->width();
			original_height = vid->height();
			fps = vid->fps;
			timer.setInterval(1000.0 / fps);
		}
	}

	void start() {
		timer.start();
	}

	void stop() {
		timer.stop();
	}
};


QAVIMovie::QAVIMovie(QLabel& label)
    : pimpl( new Pimpl(label) )
{ 
	connect(&pimpl->timer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
}

QAVIMovie::~QAVIMovie() {
    delete pimpl;
}


void QAVIMovie::setAVI(const std::string& filePath) {
	pimpl->setNewMovie(filePath);
}

void QAVIMovie::updatePixmap() {
	int w = pimpl->label.width();
	int h = pimpl->label.height();
	if (pimpl->vid) {
		pimpl->vid->jumpToNextFrame();
		pimpl->label.setPixmap(pimpl->vid->currentPixmap().scaled(w, h, Qt::KeepAspectRatio));
	}
}

void QAVIMovie::start() {
	if (pimpl->vid) {
		pimpl->start();
	}
}

void QAVIMovie::stop() {
	if (pimpl->vid) {
		pimpl->stop();
	}
}

void QAVIMovie::clear() {
	stop();
	pimpl->deleteMovie();
}

size_t QAVIMovie::getOriginalWidth() const {
	return pimpl->original_width;
}

size_t QAVIMovie::getOriginalHeight() const {
	return pimpl->original_height;
}

