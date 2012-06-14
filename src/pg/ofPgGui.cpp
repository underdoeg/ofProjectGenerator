#include "ofPgGui.h"

ofPgGui::ofPgGui(ofPg* _pg)
{
	pg = _pg;
}

ofPgGui::~ofPgGui()
{
}

void ofPgGui::setup()
{
	ofSetFrameRate(60);
	
	panelAddons.setup();
	for(int i=0; i<(int)pg->addons.size(); i++) {
		string addon = pg->addons.getName(i);
		if(addon.find("ofx")==0) {
			ofxToggle * toggle = new ofxToggle();
			panelAddons.add(toggle->setup(addon,false,300));
		}
	}

	panelOptions.setup("","settings.xml",ofGetWidth()-panelAddons.getWidth()-10,120);
	panelOptions.add(createProject.setup("create project",300));
	panelOptions.add(updateProject.setup("update project",300));
	panelOptions.add(createAndOpen.setup("create and open project",300));
	panelOptions.add(changeOFRoot.setup("change OF path",300));

}

void ofPgGui::update()
{

}

void ofPgGui::draw()
{
	panelAddons.draw();
	panelOptions.draw();
	//examplesPanel.draw();

	ofSetColor(0,0,0,100);

	//ofRect(ofPathRect);

    /*ofDrawBitmapString("press 'm' to make all files\npress ' ' to make a specific file", ofPoint(30,30));*/
	ofSetColor(255);
    //ofDrawBitmapString(drawableOfPath, ofPathDrawPoint);
}
