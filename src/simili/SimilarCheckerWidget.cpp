
#include "SimilarCheckerWidget.h"

#include "FolderSelecterWidget.h"
#include "OptionSelecterWidget.h"
#include "ComparisonDisplayerWidget.h"
#include "ComputePairsThread.h"
#include "LabeledProgressBar.h"


using namespace simili;
using namespace simili_algorithm;
using namespace std;


struct SimilarCheckerWidget::Pimpl {

	QVBoxLayout					layout;
	FolderSelecterWidget		folderSelecterWidget;
	OptionSelecterWidget		optionSelecterWidget;
	QPushButton					startBtn;
	ComparisonDisplayerWidget	comparisonDisplayerWidget;

	ComputePairsThread			computePairsThread;
	LabeledProgressBar			progressBar;

    Pimpl()
		: startBtn("start")
	{
		layout.addWidget(&folderSelecterWidget);
		layout.addWidget(&startBtn);
		layout.addWidget(&optionSelecterWidget);
		layout.addWidget(&comparisonDisplayerWidget);
    }

	~Pimpl() {
    }
};


SimilarCheckerWidget::SimilarCheckerWidget()
    : pimpl( new Pimpl() )
{ 
	pimpl->computePairsThread.setParent(this);

	setLayout(&pimpl->layout);

	connect(&pimpl->startBtn, SIGNAL(clicked()), this, SLOT(processFolder()));
	connect(&pimpl->computePairsThread, SIGNAL(progress_update(QString)), this, SLOT(progress_update(QString)));
	connect(&pimpl->computePairsThread, SIGNAL(progress_update(int)), this, SLOT(progress_update(int)));
	connect(&pimpl->computePairsThread, SIGNAL(error_raised(QString)), this, SLOT(error_raised(QString)));
	connect(&pimpl->computePairsThread, SIGNAL(computation_finished()), this, SLOT(computation_finished()));
}

SimilarCheckerWidget::~SimilarCheckerWidget() {
    delete pimpl;
}

void SimilarCheckerWidget::setFolder(const std::string& folderPath) {
	pimpl->folderSelecterWidget.setFolder(folderPath);
}


void SimilarCheckerWidget::processFolder() {
	std::string folderPath = pimpl->folderSelecterWidget.getFolder();
	std::map<std::string, bool> options = pimpl->optionSelecterWidget.getOptions();

	pimpl->computePairsThread.init(folderPath, options);
	pimpl->computePairsThread.start();
	pimpl->progressBar.show();
}


void SimilarCheckerWidget::progress_update(QString text) {
	pimpl->progressBar.setLabel(text);
}

void SimilarCheckerWidget::progress_update(int value) {
	pimpl->progressBar.setValue(value);
}

void SimilarCheckerWidget::error_raised(QString error) {
	QMessageBox::warning(this, "extraction error", error, QMessageBox::StandardButton::Close, QMessageBox::StandardButton::NoButton);
}


void SimilarCheckerWidget::computation_finished() {
	pimpl->progressBar.close();

	FilePairs filePairs = pimpl->computePairsThread.getLastResult();
	pimpl->comparisonDisplayerWidget.setFilePairs(filePairs);
}
