// MiniSQL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MiniSQL.h"
#include "interpret.h"
#include "catalog_manager.h"
#include "buffer_manager.h"
#include "API.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;
CCatalogManager Catalog;

using namespace std;

void AddSeperator(char *command)
{
	unsigned len = strlen(command);
	command[len] = ' ';
	command[len + 1] = '\0';
}

short int IsComEnd(char *input)
{
	unsigned int next = strlen(input) - 1;
	char prev = ' ';
	while(next >= 0 && (prev == '\t' || prev ==' '))
	{
		prev = input[next];
		next --;
	}
	if(prev == ';')
	{
		input[next + 1] ='\0';
		return 1;
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		//	CString strHello;
		//	strHello.LoadString(IDS_HELLO);
		//	cout << (LPCTSTR)strHello << endl;
	
		char command[COMLEN] = "";
		char input[INPUTLEN] = "";
		char word[WORDLEN] = "";
		short int ComEnd = 0;
		CInterpret parsetree;
		API A;
		
		

		Catalog.ReadCatalog();
		CBufferManager::initiate_blocks();

		while(1)
		{
			strcpy(command, "");//command����
			ComEnd = 0;
				
			while(!ComEnd)
			{
				printf("mini>> ");
				gets(input);
				if(IsComEnd(input))
					ComEnd = 1;
				strcat(command, input);
				AddSeperator(command);
			}
			parsetree.Parse(command);
			A.Exefrominterprt(parsetree);
			A.Execute();
		}
	}
	return nRetCode;
}

