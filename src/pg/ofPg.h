#ifndef OFPG_H
#define OFPG_H

#include "ofMain.h"
#include "ofPgBaseProject.h"
#include "Utils.h"

class ofPg {

public:
	ofPg();
	~ofPg();
	void setup();
	void addProject(ofPgBaseProject* project);
	void createProject(string path, ofPgBaseProject* project);
	void generateExamples();
	
	ofDirectory addons;
private:
	std::vector<ofPgBaseProject*> projects;
};

#endif // OFPG_H
