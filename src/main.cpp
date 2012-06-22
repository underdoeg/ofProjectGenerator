#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofPgGui.h"
#include "getoptpp/getopt_pp.h"
#include "ofPg.h"

using namespace GetOpt;

//========================================================================
int main(int argc, char* argv[])
{
	//the PG
	ofPg pg;
	pg.setup();

	std::string name;
	std::string salute;

	GetOpt_pp ops(argc, argv);
	if (ops >> OptionPresent('h', "help")){
		//list the help
		cout << "Project Generator for Openframeworks" << endl << endl;
		cout << "COMMANDS" << endl;
		cout << "-c: run application in console mode" << endl
		<< "-create NAME: create new project called NAME" << endl
		<< "-update: update an existing project" << endl
		<< "-type typeA typeB typeC: set project type" << endl
		<< "-l: list available project types" << endl
		<< "-path PATH: location of command" << endl << endl;
	}else if (ops >> OptionPresent('c', "command line mode")) {
		//run in command line mode
		if(ops >> OptionPresent('l', "list available projects")) {
			cout << endl << "AVAILABLE PROJECT TYPES" << endl << endl;
			ofPgBaseProjectList::iterator it = pg.projects.begin();
			while(it != pg.projects.end()) {
				cout << (*it)->getType() << endl;
				it++;
			}
			cout << endl;
		}
	} else {
		//start the gui
		ofAppGlutWindow window;
		ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

		ofRunApp( new ofPgGui(&pg));
	}
}
