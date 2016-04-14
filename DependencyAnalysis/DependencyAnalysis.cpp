/////////////////////////////////////////////////////////////////////////////
// DependencyAnalysis.h - Find Dependency of specified file                //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2015                             //
// Platform:    ThinkPad L440, Core i7-4712MQ                              //
// Author:      Alok Arya                                                  //
//              (315) 728-0088, alarya@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////


#include "../Parser/Parser.h"
#include "../Parser/ConfigureParser.h"
#include "DependencyAnalysis.h"
#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <vector>


using namespace Analyzer;

//---------------To print dependency results--------------------------------------------//
void printDependencies(DependencyResult dependencies)
{
	for (auto file : dependencies)
	{
		std::cout << "File: " << file.first << "\n";
		auto dependsOnFiles = file.second;
		for (auto dependsOnfile : dependsOnFiles)
		{
			std::cout << "\t" << dependsOnfile << "\n";
		}
	}
}

//-------------does analysis on a single file and returns it's type table---------------//
DependencyResult DependencyAnalysis::doAnalysis(std::string file, std::vector<Type> TypeTable)
{
	ConfigParserForDepAnalysis builder;
	Parser* _parser;

	_parser = builder.Build();
	if (builder.Attach(file, true))
	{
		builder.setTypeTable(&TypeTable);

		//std::cout << "\n\n\n\nFile: " << fileName << "\n";
		while (_parser->next())
		{
			_parser->parse();
		}
	}
	else
	{
		std::cout << "\n Could not attach file to parser \n";
	}

	DependencyResult dependencies = builder.getDependencies();

	return dependencies;
}


#ifdef TEST_DEPENDENCYANALYSIS
int main(int argc, char* argv[])
{

	std::vector<Type> typeTable;

	Type type;
	type.file = "Tokenizer.h"; type.name = "Toker"; type.type = "class"; type.namespaces.push_back("Global"); type.namespaces.push_back("Scanner");
	typeTable.push_back(type);
	Type type1;
	type1.file = "Tokenizer.h"; type1.name = "Toker"; type1.type = "class"; type1.namespaces.push_back("Global"); type1.namespaces.push_back("Scanner2");
	typeTable.push_back(type1);
	Type type2;
	type2.file = "Parser.h"; type2.name = "IAction"; type2.type = "struct"; type2.namespaces.push_back("Global");
	typeTable.push_back(type2);
	Type type3;
	type3.file = "ASTNode.h"; type3.name = "ASTNode"; type3.type = "class"; type3.namespaces.push_back("Global");
	typeTable.push_back(type3);

	DependencyAnalysis dependencyAnalysis;
	DependencyResult dependencies =  dependencyAnalysis.doAnalysis("../../Parser/ActionsAndRules.h",typeTable);

	for (auto file : dependencies)
	{
		std::cout << "File: " << file.first << "\n";
		auto dependsOnFiles = file.second;
		for (auto dependsOnfile : dependsOnFiles)
		{
			std::cout << "\t" << dependsOnfile << "\n";
		}
	}
}
#endif