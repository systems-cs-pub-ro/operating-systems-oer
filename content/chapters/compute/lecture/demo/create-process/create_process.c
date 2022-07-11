// SPDX-License-Identifier: BSD-3-Clause

#undef _UNICODE
#undef UNICODE

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(void)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL bRet;
	DWORD dwRet;

	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	bRet = CreateProcess(NULL, "cmd /c dir", NULL, NULL, FALSE, 0, NULL,
		NULL, &si, &pi);
	DIE(bRet == FALSE, "CreateProcess");

	printf("[parent] PID = %d; child PID = %d; Waiting...\n",
		GetCurrentProcessId(), pi.dwProcessId);

	dwRet = WaitForSingleObject(pi.hProcess, INFINITE);
	DIE(dwRet == WAIT_FAILED, "WaitForSingleObject");

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;
}
