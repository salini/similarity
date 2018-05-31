
#include "FolderSelecterWidget.h"

using namespace simili;

struct FolderSelecterWidget::Pimpl {

	QHBoxLayout		layout;
	QLineEdit		edit;
	QPushButton		browseBtn;

    Pimpl()
		: browseBtn("browse")
	{
		layout.addWidget(&edit);
		layout.addWidget(&browseBtn);

		edit.setText(getenv("USERPROFILE"));
    }

	~Pimpl() {
    }

};


FolderSelecterWidget::FolderSelecterWidget()
    : pimpl( new Pimpl() )
{
	setLayout(&pimpl->layout);

	connect(&pimpl->browseBtn, SIGNAL(clicked()), this, SLOT(browseBtn_clicked()));
}

FolderSelecterWidget::~FolderSelecterWidget() {
    delete pimpl;
}

void FolderSelecterWidget::browseBtn_clicked() {
	QString res = QFileDialog::getExistingDirectory(this, "select folder", pimpl->edit.text());
	if (res.isEmpty()) {
		return;
	}
	else {
		pimpl->edit.setText(res);
	}
}

void FolderSelecterWidget::setFolder(const std::string& folderPath) {
	pimpl->edit.setText(folderPath.c_str());
}

std::string FolderSelecterWidget::getFolder() const {
	return pimpl->edit.text().toStdString();
}

