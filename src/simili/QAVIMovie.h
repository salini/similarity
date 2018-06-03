#ifndef _SIMILI_QAVIMOVIE_H_
#define _SIMILI_QAVIMOVIE_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT QAVIMovie : public QObject {
    
Q_OBJECT

public:
    QAVIMovie(QLabel& label);
    virtual ~QAVIMovie();

	void setAVI(const std::string& filePath);

	void start();
	void stop();

	void clear();

	size_t getOriginalWidth() const;
	size_t getOriginalHeight() const;


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    QAVIMovie(const QAVIMovie& other);

private slots:
	void updatePixmap();
};

} // namespace simili


#endif
