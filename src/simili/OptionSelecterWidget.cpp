
#include "OptionSelecterWidget.h"

#include <vector>
#include <string>

#include <memory>


using namespace simili;


struct OptionSelecterWidget::Pimpl {

	QHBoxLayout layout;

	std::vector< std::unique_ptr<QCheckBox> > checkboxes;

    Pimpl() {
		checkboxes.push_back(std::unique_ptr<QCheckBox>(new QCheckBox("byte comparison")));
		checkboxes.push_back(std::unique_ptr<QCheckBox>(new QCheckBox("img histogram comparison")));
		checkboxes.push_back(std::unique_ptr<QCheckBox>(new QCheckBox("gif histogram comparison")));

		layout.addStretch();
		for (std::vector< std::unique_ptr<QCheckBox> >::iterator it = checkboxes.begin(); it != checkboxes.end(); ++it) {
			layout.addWidget((*it).get());
		}
		layout.addStretch();
    }

	~Pimpl() {
    }
};


OptionSelecterWidget::OptionSelecterWidget()
    : pimpl( new Pimpl() )
{
	setLayout(&pimpl->layout);
}

OptionSelecterWidget::~OptionSelecterWidget() {
    delete pimpl;
}

std::map<std::string, bool> OptionSelecterWidget::getOptions() const {
	std::map<std::string, bool> options;

	for (std::vector< std::unique_ptr<QCheckBox> >::iterator it = pimpl->checkboxes.begin(); it != pimpl->checkboxes.end(); ++it) {
		options[(*it)->text().toStdString()] = (*it)->isChecked();
	}

	return options;
}
