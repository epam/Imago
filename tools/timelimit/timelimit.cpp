
#include <Windows.h>
#include <string>

size_t ExecuteProcess(std::wstring FullPathToExe, std::wstring Parameters, size_t MilliSecondsToWait) 
{ 
    size_t iMyCounter = 0, iReturnVal = 0, iPos = 0; 
    DWORD dwExitCode = 0; 
    std::wstring sTempStr = L""; 

    /* - NOTE - You should check here to see if the exe even exists */ 

    /* Add a space to the beginning of the Parameters */ 
    if (Parameters.size() != 0) 
    { 
        if (Parameters[0] != L' ') 
        { 
            Parameters.insert(0,L" "); 
        } 
    } 

    /* The first parameter needs to be the exe itself */ 
    sTempStr = FullPathToExe; 
    iPos = sTempStr.find_last_of(L"\\"); 
    sTempStr.erase(0, iPos +1); 
    Parameters = sTempStr.append(Parameters); 

     /* CreateProcessW can modify Parameters thus we allocate needed memory */ 
    wchar_t * pwszParam = new wchar_t[Parameters.size() + 1]; 
    if (pwszParam == 0) 
    { 
        return 1; 
    } 
    const wchar_t* pchrTemp = Parameters.c_str(); 
    wcscpy_s(pwszParam, Parameters.size() + 1, pchrTemp); 

    /* CreateProcess API initialization */ 
    STARTUPINFOW siStartupInfo; 
    PROCESS_INFORMATION piProcessInfo; 
    memset(&siStartupInfo, 0, sizeof(siStartupInfo)); 
    memset(&piProcessInfo, 0, sizeof(piProcessInfo)); 
    siStartupInfo.cb = sizeof(siStartupInfo); 

    if (CreateProcessW(const_cast<LPCWSTR>(FullPathToExe.c_str()), 
                            pwszParam, 0, 0, false, 
                            CREATE_DEFAULT_ERROR_MODE, 0, 0, 
                            &siStartupInfo, &piProcessInfo) != false) 
    { 
        DWORD dwStartTime = GetTickCount();
        dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, MilliSecondsToWait); 
		if (WAIT_TIMEOUT == dwExitCode)
		{
			printf("...timelimit exceeded\n");
			TerminateProcess(piProcessInfo.hProcess, 0);
		}
		else
		{
			printf("...process exited (%i ms)\n", GetTickCount() - dwStartTime);
		}
    } 
    else 
    { 
        /* CreateProcess failed */ 
        iReturnVal = GetLastError(); 
    } 

    /* Free memory */ 
    delete[]pwszParam; 
    pwszParam = 0; 

    /* Release handles */ 
    CloseHandle(piProcessInfo.hProcess); 
    CloseHandle(piProcessInfo.hThread); 

    return iReturnVal; 
} 

int wmain(int argc, wchar_t* argv[])
{
	if (argc < 3)
	{
		printf("Usage: TimeLimit time_in_seconds application [parameters]\n");
	}
	else
	{
		std::wstring limit = argv[1];
		std::wstring application = argv[2];		
		std::wstring parameters;
		DWORD limit_ms = (int)(1000 * _wtof(limit.c_str()));

		for (int c = 3; c < argc; c++)
		{
			std::wstring temp = argv[c];
			bool space = false;
			for (size_t i = 0; i < temp.size(); i++)
				if (temp[i] == L' ')
					space = true;			
			if (space && temp.size() > 2 && (temp[0] != L'"' || temp[temp.size()-1] != L'"'))
				temp = std::wstring(L"\"") + temp + L"\"";
			parameters += std::wstring(L" ") + temp;
		}

		wprintf(L"Running %s with %ums timelimit...\n", application.c_str(), limit_ms);
		return ExecuteProcess(application, parameters, limit_ms);

	}
	return 0;
}

