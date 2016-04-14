#ifndef DEPANALYSIS_H
#define DEPANALYSIS_H
/////////////////////////////////////////////////////////////////////////////
// DependencyAnalysis.h - Find Dependency of specified file                //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2015                             //
// Platform:    ThinkPad L440, Core i7-4712MQ                              //
// Author:      Alok Arya                                                  //
//              (315) 728-0088, alarya@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* Used for finding packages which the specified file depends on for its 
* functions. Requires a Type Table for carrying out the dependency
* analysis
*
* Public Interface:
* =================
* DependencyAnalysis d;        //create a new instance
* d.doAnalysis(file,TypeTable);      //returns the packages file depends on
*
*
* Required Files:
* ===============
* DependencyAnalysis.cpp
* Parser.h, Parser.cpp
* ConfigureParser.h, ConfigureParser.cpp
* ActionsAndRules.h, ActionsAndRules.cpp
*
* Build Command:
* ==============
* Build Command: devenv Project2.sln /rebuild debug
*
* Maintenance History:
* ====================
*
* ver 1.0 : 13 April 2016
* - first release
*/

#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <vector>
#include <mutex>

namespace Analyzer {

using DependencyResult = std::map<std::string, std::vector<std::string>>;

	class DependencyAnalysis {
	public:
		DependencyAnalysis() {};
		~DependencyAnalysis() {};

		DependencyResult doAnalysis(std::string file, std::vector<Type> TypeTable);
	private:
		static std::mutex mtx_; //to sync outputting partial type tables		
	};
}


#endif