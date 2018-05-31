#ifndef _SIMILI_OPTIONSELECTERWIDGET_H_
#define _SIMILI_OPTIONSELECTERWIDGET_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT OptionSelecterWidget : public QWidget {
    
Q_OBJECT

public:
    OptionSelecterWidget();
    virtual ~OptionSelecterWidget();

	std::map<std::string, bool> getOptions() const;


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    OptionSelecterWidget(const OptionSelecterWidget& other);

private slots:

};

} // namespace simili


#endif
