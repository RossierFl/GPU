#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "cppTest+.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

bool runTestConsole(string titre, Test::Suite& test)
    {
    cout << "\n[" << titre << "]\n" << endl;

    Test::TextOutput output(Test::TextOutput::Verbose); // Try Verbose or Terse
    return test.run(output);
    }

bool runTestHtml(string titre, Test::Suite& test)
    {
    cout << "\n[Output HTML] : " << titre << endl << endl;

    string fileName=titre+".html";

   const char* fileNameC=fileName.c_str();

    ofstream file;
    file.open(fileNameC);

    if (file.bad())
	{
	return false;
	}
    else
	{
	//file << "Test"<<std::endl;
	Test::HtmlOutput output;
	bool isOk = test.run(output);

	output.generate(file);
	file.close();

	return isOk;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

