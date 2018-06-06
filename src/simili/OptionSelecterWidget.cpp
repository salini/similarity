
#include "OptionSelecterWidget.h"

#include <vector>
#include <string>

#include <memory>


using namespace simili;


struct OptionSelecterWidget::Pimpl {

	QHBoxLayout layout;

	std::map< std::string, std::unique_ptr<QCheckBox> > checkboxes;

    Pimpl() {
		checkboxes["byte comparison"]          = std::unique_ptr<QCheckBox>(new QCheckBox("byte comparison"));
		checkboxes["img histogram comparison"] = std::unique_ptr<QCheckBox>(new QCheckBox("img histogram comparison"));
		checkboxes["gif histogram comparison"] = std::unique_ptr<QCheckBox>(new QCheckBox("gif histogram comparison"));

		layout.addStretch();
		for (std::map< std::string, std::unique_ptr<QCheckBox> >::iterator it = checkboxes.begin(); it != checkboxes.end(); ++it) {
			layout.addWidget((*it).second.get());
		}
		layout.addStretch();

		checkboxes["byte comparison"]->setChecked(true);
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

	for (std::map< std::string, std::unique_ptr<QCheckBox> >::iterator it = pimpl->checkboxes.begin(); it != pimpl->checkboxes.end(); ++it) {
		options[(*it).first] = (*it).second->isChecked();
	}

	return options;
}
