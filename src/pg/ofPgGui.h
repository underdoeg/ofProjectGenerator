#ifndef OFPGGUI_H
#define OFPGGUI_H

#include "ofMain.h"
#include "ofPg.h"
#include "ofxGui.h"


class ofPgGui: public ofBaseApp
{

public:
	ofPgGui(ofPg* pg);
	~ofPgGui();
	void setup();
	void update();
	void draw();
	
	void createProjectPressed(bool & pressed);
	void updateProjectPressed(bool & pressed);
	void createAndOpenPressed(bool & pressed);
	void changeOFRootPressed(bool & pressed);
	
private:
	ofPg* pg;
	ofxPanel panelAddons, panelOptions;
	ofxButton createProject, updateProject, createAndOpen, changeOFRoot;
};
#endif // OFPGGUI_H
