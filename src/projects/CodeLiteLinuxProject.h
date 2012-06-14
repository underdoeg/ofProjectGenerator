/*
 * CodeLiteLinuxProject.h
 *
 *  Created on: 28/12/2011
 *      Author: arturo
 */

#ifndef CodeLiteLinuxProject_H_
#define CodeLiteLinuxProject_H_

#include "ofConstants.h"
#include "pugixml.hpp"
#include "ofAddon.h"
#include "ofPgBaseProject.h"

#define OF_TARGET_LINUX_CODELITE 345 //TODO: This is a little bit messy. One shouldn't just define some random int, but PG uses the plattform enum and there is no way to extend that?
#define OF_TARGET_LINUX64_CODELITE 346

class CodeLiteLinuxProject: public ofPgBaseProject {
public:

	enum Arch{
		Linux,
		Linux64
	};

    void setup();

    bool createProjectFile();
    void addInclude(string includeName){};
    void addLibrary(string libraryName, LibType libType = RELEASE_LIB){};

    bool loadProjectFile();
    bool saveProjectFile();
    void addSrc(string srcFile, string folder);


	static string LOG_NAME;

private:

	Arch arch;
};

#endif /* CodeLiteLinuxProject_H_ */
