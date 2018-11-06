
#include <iostream>

#include "simili/SimilarCheckerWidget.h"

#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <fstream>
namespace po = boost::program_options;

using namespace std;

void myPause() {
    std::cout << "Press enter to continue ...";
    std::cin.get();
}


int main(int argc, char* argv[]) {

	// Declare the supported options.
	po::options_description desc("Possible options");
	desc.add_options()
		("help,h", "produce help message")
		("config", po::value<string>()->default_value("similarity.conf"), "init config file")
		("init_folder", po::value<string>()->default_value(""), "init folder")
		;

	po::variables_map vm;

	po::store(po::parse_command_line(argc, argv, desc), vm);

	std::ifstream file;
	file.open(vm["config"].as<string>());
	if (file.is_open()) {
		std::cout << boost::str(boost::format("READING CONFIGURATION FROM FILE: '%s'...\n") % vm["config"].as<string>());
		po::store(po::parse_config_file(file, desc, true), vm);
	}
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}


	QApplication app(argc, argv);
	simili::SimilarCheckerWidget similarCheckerWidget;

	if (vm["init_folder"].as<string>() != "") {
		similarCheckerWidget.setFolder(vm["init_folder"].as<string>());
	}
	similarCheckerWidget.move(50, 50);
	similarCheckerWidget.showMaximized();

	return app.exec();
}

