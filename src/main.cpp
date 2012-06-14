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
	if (ops >> OptionPresent('c', "command line mode")) {
		//run in command line mode
	} else {
		//start the gui
		ofAppGlutWindow window;
		ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

		ofRunApp( new ofPgGui(&pg));
	}
}
