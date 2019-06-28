#include "stdafx.h"

class CCustomProcess *CApplicationProcess::Create(CApplication *AApplication, CProcessType AType) {
	return new CProcessSingle(AApplication, AType);
};

int main(int argc, char *argv[])
{
	int exitcode;

	CApplication *Application = CApplication::Create(argc, argv);
	Application->Run();
	exitcode = Application->ExitCode();
	Application->Destroy();

	exit(exitcode);
}
