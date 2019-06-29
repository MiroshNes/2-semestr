#pragma once

typedef enum ProcessType {
	ptMain, ptSingle, ptMaster, ptSignaller, ptWorker
} CProcessType;

class CApplication;
class CProcessSingle;
//--------------------------------------------------------------------------------------------------------------

extern CApplication *Application;
//--------------------------------------------------------------------------------------------------------------

class CCustomApplication {
private:

	int                 m_argc;
	char              **m_argv;

protected:

	int                 m_exitcode;

public:

	CCustomApplication(int argc, char *const *argv) : m_exitcode(0) {
		m_argc = argc;
		m_argv = (char **)argv;
	};

	~CCustomApplication() {};

	int ExitCode() { return m_exitcode; };
	void ExitCode(int Status) { m_exitcode = Status; };

	int argc() { return m_argc; };

}; // class CCustomApplication
//--------------------------------------------------------------------------------------------------------------

// Задание № 1
class CCustomProcess {
private:

	CCustomProcess *m_pParent;

	CProcessType m_Type;

	DWORD m_Pid;

	int m_Status;

protected:

	void SetPid(DWORD Value) { m_Pid = Value; };

	void SetStatus(int Value) { m_Status = Value; };

public:

	// Задание № 2
	CCustomProcess() : m_Type(ptMain), m_pParent(nullptr) {
	};

	// Задание № 2
	CCustomProcess(const CCustomProcess& Value) : m_Type(ptMain), m_pParent(nullptr) {
		Assign((CCustomProcess *) &Value);
	};

	// Задание № 2
	explicit CCustomProcess(CProcessType AType) : m_Type(AType), m_pParent(nullptr) {
	};

	// Задание № 2
	explicit CCustomProcess(CProcessType AType, CCustomProcess *AParent) : m_Type(AType), m_pParent(AParent) {
		m_Pid = GetCurrentProcessId();
		m_Status = 0;
	};

	// Задание № 2
	~CCustomProcess() {};

	// Задание № 1
	// Задание № 9
	virtual void Run() = 0;

	// Задание № 9
	virtual void Assign(CCustomProcess *AProcess) {
		m_Type = AProcess->Type();
		m_Pid = AProcess->Pid();
		m_Status = AProcess->Status();
	};

	CProcessType Type() { return m_Type; };

	DWORD Pid() { return m_Pid; };
	void Pid(DWORD Value) { SetPid(Value); };

	CCustomProcess *Parent() { return m_pParent; };

	int Status() { return m_Status; };
	void Status(int Value) { SetStatus(Value); };

}; // class CCustomProcess
//--------------------------------------------------------------------------------------------------------------

// Задание № 8
class CApplicationProcess : public CCustomProcess {
private:

	CApplication *m_pApplication;

protected:

public:

	// Задание № 10
	class CProcessSingle : public CCustomProcess {
	public:

		CProcessSingle(CCustomProcess* AParent, CProcessType AType) :
			CCustomProcess(AType, AParent) {
		};

		~CProcessSingle() {};

		// Задание № 7
		void Run() override {
			printf("Current process Id: %u", Pid());
		};

	};
	//--------------------------------------------------------------------------------------------------------------

	explicit CApplicationProcess(CCustomProcess* AParent, CApplication *AApplication, CProcessType AType) : CCustomProcess(),
		m_pApplication(AApplication) {
	};

	~CApplicationProcess() {};

	// Задание № 3
	static class CCustomProcess *Create(CApplication *AApplication, CProcessType AType);

	// Задание № 7
	void Assign(CCustomProcess *AProcess) override {
		CCustomProcess::Assign(AProcess);
	};

	CApplication *Application() { return m_pApplication; };

}; // class CApplicationProcess
//--------------------------------------------------------------------------------------------------------------

class CProcessManager {
public:

	explicit CProcessManager() {};

	void Start(CCustomProcess *AProcess) {
		AProcess->Run();
	};

	void Stop(int Index) {
	};

}; // class CProcessManager
//--------------------------------------------------------------------------------------------------------------

// Задание № 8
class CApplication : public CProcessManager, public CCustomApplication, public CApplicationProcess {
	// Задание № 6
	friend CCustomProcess;

private:

	CProcessType m_ProcessType;

protected:

	void SetProcessType(CProcessType Value) {
		m_ProcessType = Value;
	};

	void StartProcess() {
		// Задание № 5
		Start(CApplicationProcess::Create(this, m_ProcessType));
	};

public:

	CApplication(int argc, char *const *argv) : CApplicationProcess(nullptr, this, ptMain), CCustomApplication(argc, argv), CProcessManager() {
		m_ProcessType = ptSingle;
	};

	static class CApplication *Create(int argc, char *const *argv) {
		return new CApplication(argc, argv);
	};

	void Destroy() { delete this; };

	~CApplication() {};

	// Задание № 7
	void Run() override {
		StartProcess();
	};

	CProcessType ProcessType() { return m_ProcessType; };
	void ProcessType(CProcessType Value) { SetProcessType(Value); };

}; // class CApplication
	 //--------------------------------------------------------------------------------------------------------------

