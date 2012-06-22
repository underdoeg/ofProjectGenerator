#ifndef OFPG_H
#define OFPG_H

#include "ofMain.h"
#include "ofPgBaseProject.h"
#include "Utils.h"

class ofPg
{

public:
	ofPg();
	~ofPg();
	void setup();
	void addProject(ofPgBaseProject* project);
	void createProject(string path, ofPgBaseProject* project);
	void createProject(string path, ofPgBaseProjectList projects);
	void generateExamples();
	ofPgBaseProject* getProjectByType(string type);

	ofDirectory addons;
	std::vector<ofPgBaseProject*> projects;
private:
};

#endif // OFPG_H
