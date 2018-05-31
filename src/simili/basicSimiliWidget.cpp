
#include "basicSimiliWidget.h"
#include "ui_basicSimiliWidget.h"

using namespace simili;


struct basicSimiliWidget::Pimpl {

    Ui_basicSimiliWidget ui;


    Pimpl() {
    }

	~Pimpl() {
    }

    void setup() {
    }
};


basicSimiliWidget::basicSimiliWidget()
    : pimpl( new Pimpl() )
{ 
    pimpl->ui.setupUi(this);
    pimpl->setup();

	connect(pimpl->ui.exitBtn, SIGNAL(clicked()), this, SLOT(exitBtn_clicked()));
	connect(pimpl->ui.toggleBoxBtn, SIGNAL(clicked()), this, SLOT(toggleBoxBtn_clicked()));
	connect(pimpl->ui.displayMsgBtn, SIGNAL(clicked()), this, SLOT(displayMsgBtn_clicked()));
}

basicSimiliWidget::~basicSimiliWidget() {
    delete pimpl;
}


void basicSimiliWidget::exitBtn_clicked() {
	QApplication::quit();
}

void basicSimiliWidget::toggleBoxBtn_clicked() {
	pimpl->ui.checkBox->toggle();
}

void basicSimiliWidget::displayMsgBtn_clicked() {
	QString txt = pimpl->ui.lineEdit->text();
	pimpl->ui.label->setText(txt);
}