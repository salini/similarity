
#include "LabeledProgressBar.h"

using namespace simili;


struct LabeledProgressBar::Pimpl {

	QVBoxLayout layout;
	QLabel label;
	QProgressBar progressBar;


    Pimpl() {
		layout.addWidget(&label);
		layout.addWidget(&progressBar);

		label.setMinimumWidth(300);
		progressBar.setMinimumWidth(300);
    }

	~Pimpl() {
    }
};


LabeledProgressBar::LabeledProgressBar()
    : pimpl( new Pimpl() )
{ 
	setLayout(&pimpl->layout);
}

LabeledProgressBar::~LabeledProgressBar() {
    delete pimpl;
}


void LabeledProgressBar::setLabel(const std::string& text) {
	pimpl->label.setText(text.c_str());
}

void LabeledProgressBar::setLabel(const QString& text) {
	pimpl->label.setText(text);
}


void LabeledProgressBar::setValue(int value) {
	pimpl->progressBar.setValue(value);
}

