#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofPgGui.h"
#include "getoptpp/getopt_pp.h"

using namespace GetOpt;

//========================================================================
int main(int argc, char* argv[])
{
	std::string name;
    std::string salute;

    GetOpt_pp ops(argc, argv);

    std::cout << salute << " " << name << "!" << std::endl;
	
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofPgGui());
}
