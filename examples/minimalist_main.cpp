
#include <iostream>

#include <exception>

#include <QtWidgets>

class MinimalistWidget : public QWidget {
public: 
};


void myPause() {
    std::cout << "Press enter to continue ...";
    std::cin.get();
}


int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	MinimalistWidget w;
	w.show();
	std::cout << "222\n";
	return app.exec();
}

