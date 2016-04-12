#ifndef ParallelDepAnalysis_H
#define ParallelDepAnalysis_H
/////////////////////////////////////////////////////////////////////////////
// ParallelDependencyAnalysis.h - Performs dependency analysis in 2 passes //
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
* Acts as an executive for the application of code analysis using Abstract
* Syntax tree. Expects two arguments :-
*     1) Relative directory   (Eg:  "../../Parser" )
*     2) Search pattern       (Eg: "*.cpp")
*
* Public Interface:
* =================
* MetricAnalyzer m;            //create a new instance
* m.Analyzer(file);            //prints package analysis data for the file passed
//takes the full file path
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

#include <iostream>
#include <vector>
#include "../Parser/ActionsAndRules.h"

namespace Analyzer {

	using partialTypeTable = std::vector<Type>;

	class ParallelDependencyAnalysis {
	public:
		ParallelDependencyAnalysis() ;
		~ParallelDependencyAnalysis() ;

		void DependencyAnalysis(std::string dir, std::string pattern);                //will eventually make it return the result of analysis
	private:
		std::vector<Type> pTypeTable;		
		void Pass1(std::string dir, std::string pattern);
		void Pass2();
		void printTypeTable(std::vector<Type>* pTypeTable);
	};
}

#endif
