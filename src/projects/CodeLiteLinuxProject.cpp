/*
 * CodeLiteLinuxProject.cpp
 *
 *  Created on: 28/12/2011
 *      Author: arturo
 */

#include "CodeLiteLinuxProject.h"
#include "ofFileUtils.h"
#include "ofLog.h"
#include "Utils.h"

string CodeLiteLinuxProject::LOG_NAME = "CodeLiteLinuxProject";

void CodeLiteLinuxProject::setup() {
	templatePath = ofFilePath::join(getOFRoot(),"scripts/linux/template/"+target+"Codelite");
}

bool CodeLiteLinuxProject::createProjectFile(){
	ofDirectory dir(projectDir);
	if(!dir.exists()) dir.create(true);

    ofFile project(ofFilePath::join(projectDir, projectName + ".codelite.project"));
    string src =  ofFilePath::join(templatePath,"emptyExample_" + target + ".project");
    string dst = project.path();
    bool ret;

    if(!project.exists()){
		ret = ofFile::copyFromTo(src,dst);
		if(!ret){
			ofLogError(LOG_NAME) << "error copying codelite template from " << src << " to " << dst;
			return false;
		}else{
			findandreplaceInTexfile(dst, "emptyExample_"+target, projectName+".codelite");
			findandreplaceInTexfile(dst, "Name=\""+projectName+".codelite", "Name=\""+projectName);
		}
    }

    ofFile workspace(ofFilePath::join(projectDir, projectName + ".codelite.workspace"));
    if(!workspace.exists()){
		src = ofFilePath::join(templatePath,"emptyExample_" + target + ".workspace");
		dst = workspace.path();
		ret = ofFile::copyFromTo(src,dst);
		if(!ret){
			ofLogError(LOG_NAME) << "error copying workspace template from "<< src << " to " << dst;
			return false;
		}else{
			findandreplaceInTexfile(dst, "emptyExample_"+target, projectName+".codelite");
            findandreplaceInTexfile(dst, "Name=\""+projectName+".codelite", "Name=\""+projectName);
		}
    }

    ofFile makefile(ofFilePath::join(projectDir,"Makefile"));
    if(!makefile.exists()){
		src = ofFilePath::join(templatePath,"Makefile");
		dst = makefile.path();
		ret = ofFile::copyFromTo(src,dst);
		if(!ret){
			ofLogError(LOG_NAME) << "error copying Makefile template from " << src << " to " << dst;
			return false;
		}
    }

    ofFile config(ofFilePath::join(projectDir,"config.make"));
    if(!config.exists()){
    	src = ofFilePath::join(templatePath,"config.make");
    	dst = config.path();
    	ret = ofFile::copyFromTo(src,dst);
    	if(!ret){
    		ofLogError(LOG_NAME) << "error copying config.make template from " << src << " to " << dst;
    		return false;
    	}
    }


    // handle the relative roots.
    string relRoot = getOFRelPath(ofFilePath::removeTrailingSlash(projectDir));
    if (relRoot != "../../../"){
        string relPath2 = relRoot;
        relPath2.erase(relPath2.end()-1);
        findandreplaceInTexfile(projectDir + "config.make", "../../..", relPath2);
        findandreplaceInTexfile(ofFilePath::join(projectDir , projectName + ".codelite.workspace"), "../../../", relRoot);
        findandreplaceInTexfile(ofFilePath::join(projectDir , projectName + ".codelite.project"), "../../../", relRoot);
    }

    return true;
}

bool CodeLiteLinuxProject::loadProjectFile(){
    ofFile project(projectDir + projectName + ".codelite.project");
	if(!project.exists()){
		ofLogError(LOG_NAME) << "error loading" << project.path() << "doesn't exist";
		return false;
	}
	pugi::xml_parse_result result = doc.load(project);
	bLoaded =result.status==pugi::status_ok;
	return bLoaded;
}

bool CodeLiteLinuxProject::saveProjectFile(){
    findandreplaceInTexfile(ofFilePath::join(projectDir , projectName + ".codelite.workspace"),"emptyExample",projectName);
    pugi::xpath_node_set title = doc.select_nodes("//Option[@Name]");
    if(!title.empty()){
        if(!title[0].node().attribute("title").set_value(projectName.c_str())){
            ofLogError(LOG_NAME) << "can't set title";
        }
    }
    return doc.save_file((projectDir + projectName + ".codelite.project").c_str());
}

void CodeLiteLinuxProject::addSrc(string srcFile, string folder){
    std::vector<string> path = ofSplitString(folder, "/");
    pugi::xml_node node = doc.child("CodeLite_Project");
    for(unsigned int i=0;i<path.size();i++){
        string folder = path[i];
        if(folder != ".."){
            pugi::xml_node newNode = node.find_child_by_attribute("VirtualDirectory", "Name", folder.c_str());
            if(newNode == NULL){
                newNode = node.append_child();
                newNode.set_name("VirtualDirectory");
                pugi::xml_attribute nameAttr = newNode.append_attribute("Name");
                nameAttr.set_value(folder.c_str());
            }
            node = newNode;
        }
    }

    pugi::xml_node fileNode = node.append_child();
    fileNode.set_name("File");
    pugi::xml_attribute fileAttr = fileNode.append_attribute("Name");
    string fullPath = folder+srcFile;
    fileAttr.set_value(fullPath.c_str());
	/*pugi::xml_node node = appendValue(doc, "Unit", "filename", srcFile);
	if(!node.empty()){
		node.child("Option").attribute("virtualFolder").set_value(folder.c_str());
	}*/
    doc.save_file((projectDir + projectName + ".codelite.project").c_str());
}
