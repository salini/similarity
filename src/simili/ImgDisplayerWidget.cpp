
#include "ImgDisplayerWidget.h"
#include "ImageViewerWidget.h"

using namespace simili;


struct ImgDisplayerWidget::Pimpl {

	QVBoxLayout			layout;
	QLabel				indicator;
	ImageViewerWidget	img;
	QPushButton			delBtn;

	QMovie*				movie;
	std::string			imgPath;

    Pimpl(size_t minWidth, size_t minHeight)
		: indicator("...")
		, delBtn("delete")
		, movie(NULL)
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

    void setup() {
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

