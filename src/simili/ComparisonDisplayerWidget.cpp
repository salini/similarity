
#include "ComparisonDisplayerWidget.h"

#include "ImgDisplayerWidget.h"

#include <boost/format.hpp>

using namespace simili;
using namespace simili_algorithm;


struct ComparisonDisplayerWidget::Pimpl {;
	/*
        self.leftImg.setDeleteAction(self.deleteAction)
        self.rightImg.setDeleteAction(self.deleteAction)
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
	FilePairs filePairs;

    Pimpl()
		: backBtn("<<<")
		, leftImg(400, 400)
		, rightImg(400, 400)
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

	void setEnableButton() {
		if (filePairs.size() != 0) {
			backBtn.setEnabled(0 < index);
			nextBtn.setEnabled(index + 1 < filePairs.size());
		}
		else {
			backBtn.setEnabled(false);
			nextBtn.setEnabled(false);
		}
	}

	void displayPair(size_t new_index) {
		if (filePairs.size() == 0) {
			indicator.setText("0/0");
			leftImg.clearImg();
			rightImg.clearImg();
			setEnableButton();
			return;
		}

		if (index < 0) {
			index = 0;
		}
		if (index > filePairs.size() - 1) {
			index = filePairs.size() - 1;
		}

		indicator.setText(boost::str(boost::format("%i/%i") % (index + 1) % filePairs.size()).c_str());
		setEnableButton();

		FilePair& fp = filePairs[index];
		leftImg.setImg(fp.first);
		rightImg.setImg(fp.second);
	}
};


ComparisonDisplayerWidget::ComparisonDisplayerWidget()
    : pimpl( new Pimpl() )
{
	setLayout(&pimpl->layout);

	connect(&pimpl->backBtn, SIGNAL(clicked()), this, SLOT(displayBack()));
	connect(&pimpl->nextBtn, SIGNAL(clicked()), this, SLOT(displayNext()));

	connect(&pimpl->leftImg, SIGNAL(fileDeleted(QString)), this, SLOT(fileDeleted(QString)));
	connect(&pimpl->rightImg, SIGNAL(fileDeleted(QString)), this, SLOT(fileDeleted(QString)));
}

ComparisonDisplayerWidget::~ComparisonDisplayerWidget() {
    delete pimpl;
}


void ComparisonDisplayerWidget::displayBack() {
	displayPair(--pimpl->index);
}

void ComparisonDisplayerWidget::displayNext() {
	displayPair(++pimpl->index);
}


void ComparisonDisplayerWidget::setFilePairs(const FilePairs& filePairs) {
	pimpl->filePairs = filePairs;
	pimpl->index = 0;
	displayPair(0);
}

void ComparisonDisplayerWidget::displayPair(size_t pair_index) {
	pimpl->displayPair(pair_index);
}

#include <iostream> //TODO to delete
void ComparisonDisplayerWidget::fileDeleted(QString filePath) {
	std::string fPath = filePath.toStdString();
	std::string substitute;

	FilePair& fp = pimpl->filePairs[pimpl->index];
	if (fPath == fp.first) {
		substitute = fp.second;
	}
	else if (fPath == fp.second) {
		substitute = fp.first;
	}
	else {
		std::cout << "Cannot find element in pair; cannot substitute\n";
	}

	for (FilePairs::iterator it = pimpl->filePairs.begin(); it != pimpl->filePairs.end(); it++) {
		if ((*it).first == fPath) {
			(*it).first = substitute;
		}
		if ((*it).second == fPath) {
			(*it).second = substitute;
		}
	}

	pimpl->filePairs.erase(pimpl->filePairs.begin()+pimpl->index);
	displayPair(pimpl->index);
}
