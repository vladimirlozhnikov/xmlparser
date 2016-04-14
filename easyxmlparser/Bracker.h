#pragma once
#include "../Interface/IBrackerDispatcher.h"

class Node
{
	public:
		string GetName();
		string GetContent();
		string GetAttribute();

		bool IsCorrect();

		const Node& operator [] (string nodeName);
	private:
		friend class Bracker;
		Node();

		bool isCorrect_;
		string xmlDocument_;
		XMLObject* XMLO_;
};

class BrackerDispatcher;
class Bracker
{
	public:
		const Node& operator [] (string nodeName);

	private:
		friend class BrackerDispatcher;

		Bracker();
		virtual ~Bracker();
		bool Parse(string _xmlDocument);

		string xmlDocument_;
		XMLObject* XMLO_;
};