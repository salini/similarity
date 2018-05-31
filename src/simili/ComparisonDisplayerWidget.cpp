
#include "ComparisonDisplayerWidget.h"

#include "ImgDisplayerWidget.h"


using namespace simili;


struct ComparisonDisplayerWidget::Pimpl {;

	/*

        hlayout.addWidget(self.backBtn)
        hlayout.addWidget(self.leftImg)
        hlayout.addWidget(VLine())
        hlayout.addWidget(self.rightImg)
        hlayout.addWidget(self.nextBtn)

        self.leftImg.setDeleteAction(self.deleteAction)
        self.rightImg.setDeleteAction(self.deleteAction)

        self.setPairs([])

	*/
	QVBoxLayout layout;
	QLabel		indicator;
	QHBoxLayout	hlayout;

	QPushButton			backBtn;
	ImgDisplayerWidget	leftImg;
	QFrame				vline;
	ImgDisplayerWidget	rightImg;
	QPushButton			nextBtn;

	size_t index;


    Pimpl()
		: backBtn("<<<")
		, leftImg(600, 600)
		, rightImg(600, 600)
		, nextBtn(">>>")
	{
		layout.addWidget(&indicator, 0, Qt::AlignCenter);
		layout.addLayout(&hlayout);

		hlayout.addWidget(&backBtn);
		hlayout.addWidget(&leftImg);
		hlayout.addWidget(&vline);
		hlayout.addWidget(&rightImg);
		hlayout.addWidget(&nextBtn);

		vline.setFrameShape(QFrame::VLine);
		vline.setFrameShadow(QFrame::Sunken);

		indicator.setAlignment(Qt::AlignHCenter);

		backBtn.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
		nextBtn.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    }

	~Pimpl() {
    }
};


ComparisonDisplayerWidget::ComparisonDisplayerWidget()
    : pimpl( new Pimpl() )
{ 
	setLayout(&pimpl->layout);

	connect(&pimpl->backBtn, SIGNAL(clicked()), this, SLOT(displayBack()));
	connect(&pimpl->nextBtn, SIGNAL(clicked()), this, SLOT(displayNext()));
}

ComparisonDisplayerWidget::~ComparisonDisplayerWidget() {
    delete pimpl;
}


void ComparisonDisplayerWidget::displayBack() {

}

void ComparisonDisplayerWidget::displayNext() {

}

