
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
}

basicSimiliWidget::~basicSimiliWidget() {
    delete pimpl;
}


