#ifndef  ASTNode_H
#define ASTNode_H
/////////////////////////////////////////////////////////////////////////////
// TypeTable.h -  Type Table used to store user defined types in a file    //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio Enterprise 2015                  //
// Platform:    ThinkPad L440, Core i7-4712MQ                              //
// Author:      Alok Arya                                                  //
//              (315) 728-0088, alarya@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================

*
* Public Interface:
* =================

*
*
* Required Files:
* ===============
* ASTNode.cpp
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
#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <memory>


struct Type
{

};
class ASTNode {
		using NodePtr = ASTNode*;
		using Children = std::vector <NodePtr>;
		using Parent = NodePtr;
public:
		ASTNode();
		~ASTNode();
		bool addChild(NodePtr& child);
		void removeChild(NodePtr child);
		NodePtr parent();
		Children children();
		void showNodeInfo();
		void printChildren();
		void setNodeType(std::string _type) { type = _type; }
		void setNodeName(std::string _name) { name = _name; }
		void setLineStart(size_t _start) { startLineCount = _start; }
		void setLineEnd(size_t _end) { endLineCount = _end; }
		void setNoOfDescendants(int _no) { noOfDescendants = _no; }
		std::string nodeType() { return type; }
		std::string nodeName() { return name; }
		size_t startLine() { return startLineCount; }
		size_t endLine() { return endLineCount; }
		int getNoOfDescendants() { return noOfDescendants; }
		int noOfChildren();
private:
		std::string type;
		std::string name;
		size_t startLineCount = 0;
		size_t endLineCount = 0;
		int noOfDescendants = 0;
		std::string show()
		{
			std::ostringstream temp;
			temp << "(";
			temp << type;
			temp << ", ";
			temp << name;
			temp << ", ";
			temp << startLineCount;
			temp << ", ";
			temp << endLineCount;
			temp << ")";
			return temp.str();
		}
		Children _children;
		Parent _parent;
	};

}
#endif 

