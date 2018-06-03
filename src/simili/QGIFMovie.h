#ifndef _SIMILI_QGIFMOVIE_H_
#define _SIMILI_QGIFMOVIE_H_

#include "DllExport.h"
#include <QtWidgets>

namespace simili {

class SIMILI_EXPORT QGIFMovie : public QObject {
    
Q_OBJECT

public:
    QGIFMovie(QLabel& label);
    virtual ~QGIFMovie();

	void setGIF(const std::string& filePath);

	void start();
	void stop();

	void clear();

	size_t getOriginalWidth() const;
	size_t getOriginalHeight() const;


private:
    struct Pimpl;
    Pimpl* pimpl;

	//prevent class copy
    QGIFMovie(const QGIFMovie& other);

private slots:
	void updatePixmap(int);
};

} // namespace simili


#endif
