#ifndef ParallelDepExecutive_H
#define ParallelDepExecutive_H
/////////////////////////////////////////////////////////////////////////////
// ParallelDependencyExecutive.h - Executive package for the Application   //
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
* Acts as an executive for the application of Parallel Dependency 
* Analysis of Packages
*     1) Relative directory   (Eg:  "../../Parser" )
*     2) Search pattern       (Eg: "*.cpp")
*
* Public Interface:
* =================
* No interface.
* Acts as a starting point for the application
*
* Required Files:
* ===============
* 
*
* Build Command:
* ==============
* Build Command: devenv Project3.sln /rebuild debug
*
* Maintenance History:
* ====================
*
* ver 1.0 : 13 April 2016
* - first release
*/



namespace Executive {

	class ParallelDependencyExecutive
	{
	public:
		ParallelDependencyExecutive() {};
		~ParallelDependencyExecutive() {};

	private:
	};

}

#endif
