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
	if(argc > 1) {
		if (ops >> OptionPresent('h', "help")) {
			//list the help
			cout << endl << "--------------------------------------------------------" << endl;
			cout << "Project Generator for Openframeworks" << endl;
			cout << "--------------------------------------------------------" << endl << endl;
			cout << "Usage: ofProjectGenerator [OPTIONS] [PATH]" << endl << endl;
			cout << "COMMANDS" << endl
			     << "-e --all-examples" << endl
			     << "-a --all-types" << endl
			     << "-c --create NAME: create new project called NAME" << endl
			     << "-u --update: update an existing project" << endl
			     << "-h --help: show this help message" << endl
			     << "-l --list: list available project types" << endl
			     << "-q --quiet: no output" << endl
			     << "-v --version: show versions of the Project Generator and openFrameworks" << endl << endl;
			
			cout << "AVAILABLE PROJECT TYPES" << endl;
			ofPgBaseProjectList::iterator it = pg.projects.begin();
			while(it != pg.projects.end()) {
				cout << "--" << (*it)->getType() << endl;
				it++;
			}
			cout << endl << endl;
		} else if(ops >> OptionPresent('l', "list")) { //LIST PROJECTS?
			cout << endl << "AVAILABLE PROJECT TYPES" << endl << endl;
			ofPgBaseProjectList::iterator it = pg.projects.begin();
			while(it != pg.projects.end()) {
				cout << (*it)->getType() << endl;
				it++;
			}
			cout << endl;
		} else { //SOMETHING MORE COMPLICATED
		
			//grab the correct projects, except when --all-types is set
			ofPgBaseProjectList projects;
			if(ops >> OptionPresent('a', "all-types")) {
				projects = pg.projects;
			} else {
				ofPgBaseProjectList::iterator it = pg.projects.begin();
				while(it != pg.projects.end()) {
					if(ops >> OptionPresent('x', (*it)->getType())) {
						projects.push_back(*it);
					}
					it++;
				}
			}
			
			//get the provided path
			string path = argv[argc-1];
			
			if(ops >> OptionPresent('c', "create")) {
				/*cout << "HELL YESS! Let's make a new project (";
				for(unsigned int i=0; i<projects.size(); i++) {
					cout << projects[i]->getType() << ",";
				}
				cout << ") in " << path << endl;*/
				string projectName;
				ops >> Option('c', "create", projectName, "unnamedProject" );
				pg.createProject(projectName, path, projects);
			}
		}
	} else {
		//start the gui
		ofAppGlutWindow window;
		ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

		ofRunApp( new ofPgGui(&pg));
	}
}
