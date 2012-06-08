#ifndef OFPG_H
#define OFPG_H

#include "ofMain.h"
#include "ofPgBaseProject.h"

class ofPg {

public:
	ofPg();
	~ofPg();
	void addProject(ofPgBaseProject* project);
	void createProject(string path, ofPgBaseProject* project);
	void generateExamples();
private:
	std::vector<ofPgBaseProject*> projects;
};

#endif // OFPG_H
