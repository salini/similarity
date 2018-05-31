#ifndef _SIMILI_FOLDERSELECTERWIDGET_H_
#define _SIMILI_FOLDERSELECTERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT FolderSelecterWidget : public QWidget {
    
Q_OBJECT

public:
    FolderSelecterWidget();
    virtual ~FolderSelecterWidget();

	void setFolder(const std::string& folderPath);
	std::string getFolder() const;


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    FolderSelecterWidget(const FolderSelecterWidget& other);

private slots:
	void browseBtn_clicked();

};

} // namespace simili


#endif
