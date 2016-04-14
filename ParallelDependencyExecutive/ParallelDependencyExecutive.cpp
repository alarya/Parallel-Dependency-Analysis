/////////////////////////////////////////////////////////////////////////////
// ParallelDependencyExecutive.cpp - Executive package for the Application //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2015                             //
// Platform:    ThinkPad L440, Core i7-4712MQ                              //
// Author:      Alok Arya                                                  //
//              (315) 728-0088, alarya@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////


#include "../ParallelDependencyAnalysis/ParallelDependencyAnalysis.h"
#include<iostream>
#include<io.h>

using namespace Analyzer;

int main(int argc, char* argv[])
{
if (argc < 3)
{
std::cout << "Usage: \n ";
std::cout << argv[0] << " -dir -{pattern1, pattern2,...}";
return 0;
}

std::cout << "Directory: " << argv[1] << "\n";
std::cout << "Patterns: ";
for (int i = 2; i < argc; i++)
	std::cout << " " << argv[i];


//check if directory exists
if (_access(argv[1], 0) != 0)
{
std::cout << "\n The directory does not exist";
return 0;
}

FileSpec filespec;
filespec.dir = argv[1];
for (int i = 2; i < argc; i++)
	filespec.patterns.push_back(argv[i]);

ParallelDependencyAnalysis parallelDepAnalyzer;

try {
	parallelDepAnalyzer.DependencyAnalysis(filespec);
}
catch (std::exception& e)
{
std::cout << e.what() << "\n";
return 0;
}

return 0;
}