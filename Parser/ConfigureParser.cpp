/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 2.2                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//  Application:   Prototype for CSE687 Pr1, Sp06                  //
//  Modified by:   Alok Arya  (alarya@syr.edu)                     //
//  Original Author: Jim Fawcett, CST 2-187, Syracuse University   //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"

using namespace Scanner;
using namespace AST;


//-----------------ConfigureParserForPrintingToScreen---------------------------------------
//----< destructor releases all parts >------------------------------
ConfigParseToConsole::~ConfigParseToConsole()
{
  // when Builder goes out of scope, everything must be deallocated

  delete pHandlePush;
  delete pBeginningOfScope;
  delete pAddScopeNode;
  delete pHandlePop;
  delete pEndOfScope;
  delete pMoveToParentNode;
  delete pPrintFunction;
  delete pPushFunction;
  delete pFunctionDefinition;
  delete pAddFunctionNode;
  delete pDeclaration;
  delete pShowDeclaration;
  delete pExecutable;
  delete pShowExecutable;
  delete pRepo;
  delete pParser;
  delete pSemi;
  delete pToker;
  pIn->close();
  delete pIn;
}
//----< attach toker to a file stream or stringstream >------------
bool ConfigParseToConsole::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;
  pIn = new std::ifstream(name);
  if (!pIn->good())
    return false;
  return pToker->attach(pIn);
}
//----< Here's where alll the parts get assembled >----------------
Parser* ConfigParseToConsole::Build()
{
  try
  {
    pToker = new Toker;
    pToker->returnComments(false);
    pSemi = new SemiExp(pToker);
    pParser = new Parser(pSemi);
	pAst = new ASTree();
    pRepo = new Repository(pToker,pAst);

    pBeginningOfScope = new BeginningOfScope();
    pHandlePush = new HandlePush(pRepo);
    pBeginningOfScope->addAction(pHandlePush);
    pParser->addRule(pBeginningOfScope);

    pEndOfScope = new EndOfScope();
    pHandlePop = new HandlePop(pRepo);
    pEndOfScope->addAction(pHandlePop);
    pParser->addRule(pEndOfScope);

	pClassDefinition = new ClassDefinition();
	pAddClassNode = new AddClassNode(pRepo);
	pClassDefinition->addAction(pAddClassNode);
	pParser->addRule(pClassDefinition);
    pFunctionDefinition = new FunctionDefinition;
    pPushFunction = new PushFunction(pRepo);  // no action
    pPrintFunction = new PrintFunction(pRepo);
    pFunctionDefinition->addAction(pPushFunction);
    pFunctionDefinition->addAction(pPrintFunction);
    pParser->addRule(pFunctionDefinition);
    pDeclaration = new Declaration;
    pShowDeclaration = new ShowDeclaration;
    pDeclaration->addAction(pShowDeclaration);
    pParser->addRule(pDeclaration);
    pExecutable = new Executable;
    pShowExecutable = new ShowExecutable;
    pExecutable->addAction(pShowExecutable);
    pParser->addRule(pExecutable);
    return pParser;
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
    return 0;
  }
}


//-----------------ConfigureParserForAST---------------------------------------
//----< destructor releases all parts >----------------------------
ConfigParserForAST::~ConfigParserForAST()
{
	//rules take care of deleting their actions
	delete pBeginningOfScope;
		
	delete pEndOfScope;
	
	delete pNameSpaceDefinition;

	delete pClassDefinition;

	delete pStructDefinition;

	delete pFunctionDefinition;

	delete pOtherScopes;

	delete pRepo;
	delete pParser;
	delete pSemi;
	delete pToker;

	pIn->close();
	delete pIn;
}
//----< attach toker to a file stream or stringstream >------------
bool ConfigParserForAST::Attach(const std::string& name, bool isFile)
{
	if (pToker == 0)
		return false;
	pIn = new std::ifstream(name);
	if (!pIn->good())
		return false;
	return pToker->attach(pIn);
}

/*Configure rules for parser: helper functions*/
BeginningOfScope* configureRuleForStartScope(Parser* pParser, Repository* pRepo)
{
	BeginningOfScope* pBeginningOfScope = new BeginningOfScope();
	HandlePush* pHandlePush = new HandlePush(pRepo);
	AddScopeNode* pAddScopeNode = new AddScopeNode(pRepo);
	pBeginningOfScope->addAction(pHandlePush);
	pBeginningOfScope->addAction(pAddScopeNode);
	pParser->addRule(pBeginningOfScope);
	return pBeginningOfScope;
}
EndOfScope* configureRuleForEndScope(Parser* pParser, Repository* pRepo)
{
	EndOfScope* pEndOfScope = new EndOfScope();
	HandlePop* pHandlePop = new HandlePop(pRepo);
	MoveToParentNode* pMoveToParentNode = new MoveToParentNode(pRepo);
	pEndOfScope->addAction(pHandlePop);
	pEndOfScope->addAction(pMoveToParentNode);
	pParser->addRule(pEndOfScope);
	return pEndOfScope;
}
NameSpaceDefinition* configureRuleForNameSpaces(Parser* pParser, Repository* pRepo)
{
	NameSpaceDefinition* pNameSpaceDefinition = new NameSpaceDefinition();
	PushNamespace* pPushNamespace = new PushNamespace(pRepo);
	AddNamespaceNode* pAddNamespaceNode = new AddNamespaceNode(pRepo);
	pNameSpaceDefinition->addAction(pPushNamespace);
	pNameSpaceDefinition->addAction(pAddNamespaceNode);
	pParser->addRule(pNameSpaceDefinition);
	return pNameSpaceDefinition;
}
ClassDefinition* configureRuleForClass(Parser* pParser, Repository* pRepo)
{
	ClassDefinition* pClassDefinition = new ClassDefinition();
	PushClass* pPushClass = new PushClass(pRepo);
	AddClassNode* pAddClassNode = new AddClassNode(pRepo);
	pClassDefinition->addAction(pPushClass);
	pClassDefinition->addAction(pAddClassNode);
	pParser->addRule(pClassDefinition);
	return pClassDefinition;
}
StructDefinition* configureRuleForStruct(Parser* pParser, Repository* pRepo)
{
	StructDefinition* pStructDefinition = new StructDefinition();
	PushStruct* pPushStruct = new PushStruct(pRepo);
	AddStructNode* pAddStructNode = new AddStructNode(pRepo);
	pStructDefinition->addAction(pPushStruct);
	pStructDefinition->addAction(pAddStructNode);
	pParser->addRule(pStructDefinition);
	return pStructDefinition;
}
FunctionDefinition* configureRuleForFunction(Parser* pParser, Repository* pRepo)
{
	FunctionDefinition* pFunctionDefinition = new FunctionDefinition();
	PushFunction* pPushFunction = new PushFunction(pRepo);
	AddFunctionNode* pAddFunctionNode = new AddFunctionNode(pRepo);
	pFunctionDefinition->addAction(pPushFunction);
	pFunctionDefinition->addAction(pAddFunctionNode);
	pParser->addRule(pFunctionDefinition);
	return pFunctionDefinition;
}
OtherScopes* configureRuleForOtherScope(Parser* pParser, Repository* pRepo)
{
	OtherScopes* pOtherScopes = new OtherScopes();
	PushOtherScopes* pPushOtherScopes = new PushOtherScopes(pRepo);
	AddOtherScopeNode* pAddOtherScopeNode = new AddOtherScopeNode(pRepo);
	pOtherScopes->addAction(pPushOtherScopes);
	pOtherScopes->addAction(pAddOtherScopeNode);
	pParser->addRule(pOtherScopes);
	return pOtherScopes;
}
//----< Here's where all the parts get assembled >----------------
Parser* ConfigParserForAST::Build()
{
	try
	{
		// add Parser's main parts
		pToker = new Toker;
		pToker->returnComments(false);
		pSemi = new SemiExp(pToker);
		pParser = new Parser(pSemi);
		pAst = new ASTree();
		pRepo = new Repository(pToker, pAst);

		// configure to manage scope
		// these must come first - they return true on match
		// so rule checking continues

		pBeginningOfScope = configureRuleForStartScope(pParser, pRepo);
	    pEndOfScope = configureRuleForEndScope(pParser, pRepo);
		pNameSpaceDefinition = configureRuleForNameSpaces(pParser, pRepo);
	    pClassDefinition = configureRuleForClass(pParser, pRepo);
	    pStructDefinition = configureRuleForStruct(pParser, pRepo);
	    pFunctionDefinition = configureRuleForFunction(pParser, pRepo);
		pOtherScopes = configureRuleForOtherScope(pParser, pRepo);

		return pParser;
  }
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what() << "\n\n";
		return 0;
	}
}


//-------------------ConfigureParserForTypeTable-----------------------------
//---Destructor------------------------------------------------
ConfigParserForTypeTable::~ConfigParserForTypeTable()
{
	//rules take care of deleting their actions
	delete pBeginningOfScope;

	delete pEndOfScope;

	delete pNameSpaceDefinition;

	delete pClassDefinition;

	delete pStructDefinition;

	delete pRepo;
	delete pParser;
	delete pSemi;
	delete pToker;

	pIn->close();
	delete pIn;
}
//----attach toker to a file stream or stringstream------------
bool ConfigParserForTypeTable::Attach(const std::string& name, bool isFile)
{
	if (pToker == 0)
		return false;
	pIn = new std::ifstream(name);
	if (!pIn->good())
		return false;

	pRepo->setFileName(name);

	return pToker->attach(pIn);
}
//----Build the various parts of the parser--------------------
Parser* ConfigParserForTypeTable::Build()
{
	try
	{
		pToker = new Toker;
		pToker->returnComments(false);
		pSemi = new SemiExp(pToker);
		pParser = new Parser(pSemi);
		pTypeTable = new std::vector<Type>();
		pRepo = new Repository(pToker,pTypeTable);

		pBeginningOfScope = new BeginningOfScope();
		pHandlePush = new HandlePush(pRepo);
		pBeginningOfScope->addAction(pHandlePush);
		pParser->addRule(pBeginningOfScope);

		pEndOfScope = new EndOfScope();
		pHandlePop = new HandlePop(pRepo);
		pEndOfScope->addAction(pHandlePop);
		pParser->addRule(pEndOfScope);

		pNameSpaceDefinition = new NameSpaceDefinition();
		pPushNamespace = new PushNamespace(pRepo);
		pNameSpaceDefinition->addAction(pPushNamespace);
		pParser->addRule(pNameSpaceDefinition);

		pClassDefinition = new ClassDefinition();
		pSaveClassToTypeTable = new SaveClassToTypeTable(pRepo);
		pClassDefinition->addAction(pSaveClassToTypeTable);
		pParser->addRule(pClassDefinition);

		pStructDefinition = new StructDefinition();
		pSaveStructToTypeTable = new SaveStructToTypeTable(pRepo);
		pStructDefinition->addAction(pSaveStructToTypeTable);
		pParser->addRule(pStructDefinition);

		return pParser;
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what() << "\n\n";
		return 0;
	}
}


//------------------ConfigureParserForDepAnalysis-----------------------------
//---Destructor-----------------------------------------
ConfigParserForDepAnalysis::~ConfigParserForDepAnalysis()
{
	//rules take care of deleting their actions
	delete pClassDefinition;

	delete pStructDefinition;

	delete pDeclaration;

	delete pExecutable;

	delete pRepo;
	delete pParser;
	delete pSemi;
	delete pToker;

	pIn->close();
	delete pIn;
}
//----attach toker to a file stream or stringstream-----------
bool ConfigParserForDepAnalysis::Attach(const std::string& name, bool isFile)
{
	if (pToker == 0)
		return false;
	pIn = new std::ifstream(name);
	if (!pIn->good())
		return false;

	pRepo->setFileName(name);

	return pToker->attach(pIn);
}
//----Build the various parts of the parser--------------------
Parser* ConfigParserForDepAnalysis::Build()
{
	try
	{
		pToker = new Toker;
		pToker->returnComments(false);
		pSemi = new SemiExp(pToker);
		pParser = new Parser(pSemi);
		pRepo = new Repository(pToker);

		pClassDefinition = new ClassDefinition();
		pStructDefinition = new StructDefinition();
		pDeclaration = new Declaration();
		pExecutable = new Executable();

		pCheckDependencyClass = new CheckDependency(pRepo);
		pCheckDependencyStruct = new CheckDependency(pRepo);
		pCheckDependencyDeclaration = new CheckDependency(pRepo);
		pCheckDependencyExecutable = new CheckDependency(pRepo);
		//pPrintClass = new PrintClass;
		//pPrintStruct = new PrintStruct;
		//pShowDeclaration = new ShowDeclaration;
		//pShowExecutable = new ShowExecutable;

		pClassDefinition->addAction(pCheckDependencyClass);
		pStructDefinition->addAction(pCheckDependencyStruct);
		pDeclaration->addAction(pCheckDependencyDeclaration);
		pExecutable->addAction(pCheckDependencyExecutable);

		//pClassDefinition->addAction(pPrintClass);
		//pStructDefinition->addAction(pPrintStruct);
		//pDeclaration->addAction(pShowDeclaration);
		//pExecutable->addAction(pShowExecutable);

		pParser->addRule(pClassDefinition);
		pParser->addRule(pStructDefinition);
		pParser->addRule(pDeclaration);
		pParser->addRule(pExecutable);

		return pParser;
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what() << "\n\n";
		return 0;
	}
}
//----Set Type table in Repository for Dependency Analysis------------------
void ConfigParserForDepAnalysis::setTypeTable(std::vector<Type>* TypeTable)
{
	pRepo->setTypeTable(TypeTable);
	//This is called to build a Easy type lookup for dependency analysis
	//It is stored locally in the repository and built using mergedTypeTable
	pRepo->buildTypeLookUpFromTypeTable();
}
std::map<std::string, std::vector<std::string>> ConfigParserForDepAnalysis::getDependencies()
{
	return pRepo->getDependencies();
}

#ifdef TEST_CONFIGUREPARSER

#include <queue>
#include <string>


//----------print the type table generated by parsing--------------//
void printTypeTable(std::vector<Type>* pTypeTable)
{
	std::cout << "Type \t\t\t Name \t\t\t Namespace \t\t\t File \n";
	for each ( auto Type in *pTypeTable)
	{
		std::cout << Type.type << "\t\t\t" << Type.name << "\t\t\t";
		std::string _ns = "";
		for each(auto ns in Type.namespaces)
		{
			_ns += ns + "::";
		}
		std::cout << _ns.substr(0,_ns.size()-2);
		std::cout <<  "\t\t\t" << Type.file << "\n";		
	}
	
}

//---------test configParserForTypeTable--------------------------//
int testConfigParserForTypeTable(int argc, char* argv[])
{
	std::cout << "\n  Testing ConfigureParserForTypeTable \n "
		<< std::string(32, '=') << std::endl;

	// collecting tokens from files, named on the command line

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	for (int i = 1; i<argc; ++i)
	{
		std::cout << "\n  Processing file " << argv[i];
		std::cout << "\n  " << std::string(16 + strlen(argv[i]), '-');

		ConfigParserForTypeTable configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(argv[i]))
				{
					std::cout << "\n  could not open file " << argv[i] << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it
			while (pParser->next())
				pParser->parse();
			std::cout << "\n\n";

			std::vector<Type>* pTypeTable = configure.TypeTable();
			printTypeTable(pTypeTable);
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		std::cout << "\n\n";
	}
	return 0;
}

//-----------------test configparser for dependency analysis------//
int testConfigParserDepAnalysis()
{	
	std::string file = "../../Parser/ActionsAndRules.h";

	std::cout << "\n  Testing ConfigParserforDepAnalysis on file: " << file << "\n "
		<< std::string(50, '=') << std::endl;

	ConfigParserForDepAnalysis configure;
	Parser* pParser = configure.Build();
	try
	{
		if (pParser)
		{
			if (!configure.Attach(file))
			{
				std::cout << "\n  could not open file " << file << std::endl;
			}

			else
			{
				std::vector<Type> typeTable;

				Type type;
				type.file = "Tokenizer.h"; type.name = "Toker"; type.type = "class"; type.namespaces.push_back("Global"); type.namespaces.push_back("Scanner");
				typeTable.push_back(type);
				Type type1;
				type1.file = "Tokenizer.h"; type1.name = "Toker"; type1.type = "class"; type1.namespaces.push_back("Global"); type1.namespaces.push_back("Scanner");
				typeTable.push_back(type1);
				Type type2;
				type2.file = "Parser.h"; type2.name = "IRule"; type2.type = "struct"; type2.namespaces.push_back("Global");
				typeTable.push_back(type2);
				Type type3;
				type3.file = "ASTNode.h"; type3.name = "ASTNode"; type3.type = "class"; type3.namespaces.push_back("Global");
				typeTable.push_back(type3);

				configure.setTypeTable(&typeTable);

				//now that parser is built, use it
				while (pParser->next())
					pParser->parse();
				std::cout << "\n\n";

				std::map<std::string, std::vector<std::string>> dependencies = configure.getDependencies();

				//print dependencies found
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
		}
		else
		{
			std::cout << "\n\n  Parser not built\n\n";
			return 1;
		}
			
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	std::cout << "\n\n";

	return 0;
}

//--------test configParserToConsole------------------------------//
int testConfigParserToConsole(int argc, char* argv[])
{
	std::cout << "\n  Testing ConfigureParserToConsole \n "
		<< std::string(32, '=') << std::endl;

	// collecting tokens from files, named on the command line

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	for (int i = 1; i<argc; ++i)
	{
		std::cout << "\n  Processing file " << argv[i];
		std::cout << "\n  " << std::string(16 + strlen(argv[i]), '-');

		ConfigParseToConsole configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(argv[i]))
				{
					std::cout << "\n  could not open file " << argv[i] << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it
			while (pParser->next())
				pParser->parse();
			std::cout << "\n\n";

		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		std::cout << "\n\n";
	}
	return 0;
}

int main(int argc, char* argv[])
{
	//testConfigParserToConsole(argc,argv);

	//testConfigParserForTypeTable(argc, argv);

	testConfigParserDepAnalysis();
}

#endif
