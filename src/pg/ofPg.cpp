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

void ofPg::generateExamples()
{
}

void ofPg::createProject(string path, ofPgBaseProject* project)
{
	ofLogNotice() << "creating project in " << path;
}

void ofPg::createProject(string path, ofPgBaseProjectList projects)
{
	ofPgBaseProjectList::iterator it = projects.begin();
	while(it != projects.end()){
		createProject(path, *it);
		it++;
	}
}
