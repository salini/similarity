#ifndef _SIMILI_LABELEDPROGRESSBAR_H_
#define _SIMILI_LABELEDPROGRESSBAR_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT LabeledProgressBar : public QWidget {
    
Q_OBJECT

public:
    LabeledProgressBar();
    virtual ~LabeledProgressBar();

	void setLabel(const std::string& text);
	void setLabel(const QString& text);
	void setValue(int value);

private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    LabeledProgressBar(const LabeledProgressBar& other);

private slots:

};

} // namespace simili


#endif
