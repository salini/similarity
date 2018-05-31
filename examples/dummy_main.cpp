
#include <iostream>

#include "simili/basicSimiliWidget.h"


void myPause() {
    std::cout << "Press enter to continue ...";
    std::cin.get();
}


int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	simili::basicSimiliWidget w;
	w.show();

	return app.exec();
}

