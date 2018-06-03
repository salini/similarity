
#include "ImgDisplayerWidget.h"
#include "ImageViewerWidget.h"
#include "QGIFMovie.h"
#include "QAVIMovie.h"
#include "simili_algorithm/Utils.h"

#include <boost/format.hpp>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

using namespace simili;


#include <iostream>




struct ImgDisplayerWidget::Pimpl {

	QVBoxLayout			layout;
	QLabel				indicator;
	ImageViewerWidget	img;
	QPushButton			delBtn;

	std::string			imgPath;

	QGIFMovie			gifMovie;
	QAVIMovie			aviMovie;

    Pimpl(size_t minWidth, size_t minHeight)
		: indicator("...")
		, delBtn("delete")
		, gifMovie(img)
		, aviMovie(img)
		//, movie(NULL)
	{
		layout.addWidget(&indicator, 0, Qt::AlignHCenter);
		layout.addWidget(&img);
		layout.addWidget(&delBtn, 0, Qt::AlignHCenter);

		indicator.setAlignment(Qt::AlignHCenter);
		indicator.setTextInteractionFlags(Qt::TextSelectableByMouse);
		indicator.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

		img.setAlignment(Qt::AlignCenter);
		img.setMinimumSize(minWidth, minHeight);
		img.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    }

	~Pimpl() {
    }

	void clearPixmapMovie() {
		/*
		self.img.setPixmap(QtGui.QPixmap())
		if self.movie is not None :
			self.movie.stop()
			self.movie = None
			self.img.setMovie(QtGui.QMovie())
			*/
		img.clear();
		gifMovie.clear();
		aviMovie.clear();
	}
	

	void clearImg() {
		imgPath = "";
		indicator.setText("...");
		img.setText(".");
		clearPixmapMovie();
	}

	void setImg(const std::string& filePath) {
		/*
		self.clearImg()
        self.imgPath = imgPath
        ext = os.path.splitext(imgPath)[1]

        if ext in IMG_EXT:
            self.img.setImage(imgPath)
            w,h = self.img.getOriginalSize()

        elif ext in GIF_EXT:
            self.movie = QGIFMovie(self.img, imgPath)
            self.movie.start()
            w, h = self.movie.getOriginalSize()

        elif ext in MOV_EXT:
            self.movie = QFFMPEGMovie(self.img, imgPath)
            self.movie.start()
            w, h = self.movie.getOriginalSize()
        else:
            w,h = 0,0

        self.indicator.setText("{0} [{w}x{h} {1:.2f}Mo]".format(imgPath, os.path.getsize(imgPath)*1e-6, w=w, h=h))
		*/

		clearImg();
		imgPath = filePath;
		std::string ext = extension(imgPath);
		size_t w=0, h=0;

		if (ext == ".gif") {
			gifMovie.setGIF(imgPath);
			gifMovie.start();
			w = gifMovie.getOriginalWidth();
			h = gifMovie.getOriginalHeight();
		}
		else if(ext == ".avi" || ext == ".mp4") {
			aviMovie.setAVI(imgPath);
			aviMovie.start();
			w = aviMovie.getOriginalWidth();
			h = aviMovie.getOriginalHeight();
		}
		else {  //(ext == ".jpg" || ext == ".png")  // we suppose it is a supported image
			img.setImage(imgPath);
			w = img.getOriginalWidth();
			h = img.getOriginalHeight();
		}
		

		indicator.setText(boost::str(boost::format("%s [%ix%i %.2f Mo]") % imgPath % w % h % (simili_algorithm::getFileSize(imgPath)*1e-6) ).c_str());
	}
};


ImgDisplayerWidget::ImgDisplayerWidget(size_t minWidth, size_t minHeight)
    : pimpl( new Pimpl(minWidth, minHeight) )
{ 
	setLayout(&pimpl->layout);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(&pimpl->delBtn, SIGNAL(clicked()), this, SLOT(delBtn_clicked()));
}

ImgDisplayerWidget::~ImgDisplayerWidget() {
    delete pimpl;
}


void ImgDisplayerWidget::delBtn_clicked() {

}

void ImgDisplayerWidget::clearImg() {
	pimpl->clearImg();
}

void ImgDisplayerWidget::setImg(const std::string& filePath) {
	pimpl->setImg(filePath);
}



