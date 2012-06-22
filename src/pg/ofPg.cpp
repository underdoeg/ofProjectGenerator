#include "CodeLiteLinuxProject.h"
#include "xcodeProject.h"
#include "visualStudioProject.h"
#include "CBWinProject.h"
#include "CBLinuxProject.h"
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
	
	addProject(new CBLinuxProject());
	addProject(new CBWinProject());
	addProject(new visualStudioProject());
	addProject(new xcodeProject());
	addProject(new CodeLiteLinuxProject());
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
