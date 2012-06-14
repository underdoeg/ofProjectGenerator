#include "ofPg.h"

ofPg::ofPg()
{
}

ofPg::~ofPg()
{
}

void ofPg::setup(){
	while(!checkConfigExists()){
		askOFRoot();
	}
	setOFRoot(getOFRootFromConfig());

	addons.open(ofFilePath::join(getOFRoot(),"addons"));
	addons.listDir();
}

void ofPg::addProject(ofPgBaseProject* project){
	projects.push_back(project);
}