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
* This package is used to find dependencies among a set of files 
* It employs a 2 pass strategy. In the 1st pass it builds a Type Table containing
* Types from all the files in the set. In the 2nd Pass it does dependency analysis
* using the complete type table.
* The module also uses Threads to do the analysis parallely.
*
*
*
* Public Interface:
* =================
* ParallelDependencyAnalysis p;            //create a new instance
* p.DependencyAnalysis(filespec);          //start dependency analsysis based on the filespec
*										   //The file spec contains a root directory and a set of patterns				
*
* Required Files:
* ===============
* ParallelDependencyAnalysis.cpp
* TypeAnalysis.h, TypeAnalysis.cpp
* DependencyAnalysis.h, DependencyAnalysis.cpp
* FileMgr.h, FileMgr.cpp, Parser.h, Parser.cpp
* QueuedWorkItems.h QueuedWorkItems.cpp
* ConfigureParser.h, ConfigureParser.cpp
* FileMgr.h, FileMgr.cpp
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

#include <iostream>
#include <vector>
#include "../Parser/ActionsAndRules.h"

namespace Analyzer {

	using partialTypeTable = std::vector<Type>;
	using TypeTable = std::vector<Type>;

	struct FileSpec {
		std::string dir;
		std::vector<std::string> patterns;
	};

	class ParallelDependencyAnalysis {
	public:
		ParallelDependencyAnalysis() ;
		~ParallelDependencyAnalysis() ;

		void DependencyAnalysis(FileSpec filespec);                
	private:
		std::vector<Type> pTypeTable;		
		void Pass1(FileSpec filespec);
		void Pass2(TypeTable mergedTypeTable,FileSpec filespec);
		void printTypeTable(std::vector<Type>* pTypeTable);
	};


}
#endif
