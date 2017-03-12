//---------------------------------------------------------------------------

#ifndef com_portH
#define com_portH
//---------------------------------------------------------------------------
#endif

typedef unsigned long DWORD;

int COMOpen();
void COMClose();
unsigned char* ReadThread();
void WriteThread();
int Read(char* buf,DWORD len);