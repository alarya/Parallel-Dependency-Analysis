#ifndef TYPEANALYSIS_H
#define TYPEANALYSIS_H
/////////////////////////////////////////////////////////////////////////////
// TypeAnalysis.h - Build Type Table for a specified file                  //
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
* builds a type table of the user types defined in a package.
* The types captured are dependent on what rules are configured in the parser
*
* Public Interface:
* =================
* TypeAnalysis ta;             //create a new instance
* ta.doAnalysis(file);         //returns the type table built for the package specified
*
* Required Files:
* ===============
* MetricAnalyzer.cpp
* FileMgr.h, FileMgr.cpp, Parser.h, Parser.cpp
* ConfigureParser.h, ConfigureParser.cpp
* FileSystem.h, FileSystem.cpp
*
* Build Command:
* ==============
* Build Command: devenv Project2.sln /rebuild debug
*
* Maintenance History:
* ====================
*
* ver 1.0 : 12 March 2016
* - first release
*/

#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <vector>
#include <mutex>

namespace Analyzer {
	

class TypeAnalysis {
	public:
		TypeAnalysis() {};
		~TypeAnalysis() {};

		std::vector<Type> doAnalysis(std::string file);
	private:
		static std::mutex mtx_; //to sync outputting partial type tables
		static void printTypeTable(std::vector<Type>* pTypeTable, std::string file);
	};
}


#endif