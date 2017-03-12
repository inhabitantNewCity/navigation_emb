//---------------------------------------------------------------------------

#pragma hdrstop

#include "com_port.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma once

#include <Windows.h>
#include <io.h>
#include "com_port.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

#define BUFSIZE 28
unsigned char bufrd[BUFSIZE];	//ïðè¸ìíûé áóôåð
HANDLE COMport;					//äåñêðèïòîð ïîðòà
OVERLAPPED overlapped;			//äëÿ  ÷òåíèÿ
OVERLAPPED overlappedwr;		//äëÿ  çàïèñè
unsigned long counter;			//ñ÷¸ò÷èê ïðèíÿòûõ áàéòîâ, îáíóëÿåòñÿ ïðè êàæäîì îòêðûòèè ïîðòà
bool Connected = true;
/*
ERROR
1  - ok
-1 - îøèáêà îòêðûòèÿ COMport'a
-2 - oøèáêà ïðèìåíåíèÿ íàñòðîåê

*/
int COMOpen()
{
 DCB dcb;               //ñòðóêòóðà äëÿ îáùåé èíèöèàëèçàöèè ïîðòà DCB

 COMport = CreateFile(L"\\\\.\\\COM8",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		//FILE_FLAG_OVERLAPPED,
		FILE_ATTRIBUTE_NORMAL,
		0);
 if (COMport == INVALID_HANDLE_VALUE)
	{
		//MessageBox(0,TEXT("Cannot open the port"),TEXT("Error"),MB_ICONEXCLAMATION);
		Connected = FALSE;
		return -1;
	}
 else
 {
		dcb.BaudRate = CBR_115200;
		dcb.fBinary = true;     /* Binary Mode (skip EOF check)    */
		dcb.fParity = false;     /* Enable parity checking          */
		dcb.fOutxCtsFlow = false; /* CTS handshaking on output       */
		dcb.fOutxDsrFlow = false; /* DSR handshaking on output       */
		dcb.fDtrControl = DTR_CONTROL_ENABLE;  /* DTR Flow control    */
		dcb.fDsrSensitivity = false; /* DSR Sensitivity              */
		dcb.fTXContinueOnXoff = true; /* Continue TX when Xoff sent */
		dcb.fOutX = false;       /* Enable output X-ON/X-OFF        */
		dcb.fInX = false;        /* Enable input X-ON/X-OFF         */
		dcb.fErrorChar = 0;  /* Enable Err Replacement          */
		dcb.fNull = false;       /* Enable Null stripping           */
		dcb.fRtsControl = RTS_CONTROL_DISABLE;  /* Rts Flow control       */
		dcb.fAbortOnError = true; // false; /* Abort all reads and writes on Error */
		dcb.ByteSize = 8;        /* Number of bits/byte, 4-8        */
		dcb.Parity = NOPARITY;          /* 0-4=None,Odd,Even,Mark,Space    */
		dcb.StopBits = ONESTOPBIT;        /* 0,1,2 = 1, 1.5, 2               */

		COMMTIMEOUTS ComTimeouts;
		Connected =(bool) GetCommTimeouts (COMport, &ComTimeouts);
		if (!Connected)
			{
			// dwError = GetLastError();
			//MessageBox(0,TEXT("Cannot get timeouts"),TEXT("Error"),MB_ICONEXCLAMATION);
			}
		ComTimeouts.ReadIntervalTimeout = 0;
		ComTimeouts.ReadTotalTimeoutConstant = 100;
		ComTimeouts.ReadTotalTimeoutMultiplier = 1;
		ComTimeouts.WriteTotalTimeoutConstant = 100;
        ComTimeouts.WriteTotalTimeoutMultiplier = 1;

            if(!SetCommTimeouts(COMport, &ComTimeouts))
            {
                //cout << "Cann't SetCommTimeouts!\n";
                return 0;
            }
           // cout << "SetCommTimeouts\n";

 }
		if (SetCommState(COMport, &dcb))
		{
		return 1;
		}
		else
			return -2;
}

void COMClose()
{
 CloseHandle(COMport);          //çàêðûòü ïîðò
 COMport=0;						//îáíóëèòü ïåðåìåííóþ äëÿ äåñêðèïòîðà ïîðòà
}

//ôóíêöèÿ ðåàëèçóåò ïðè¸ì áàéòîâ èç COM-ïîðòà
 unsigned char* ReadThread()
{
 COMSTAT comstat;		//ñòðóêòóðà òåêóùåãî ñîñòîÿíèÿ ïîðòà, â äàííîé ïðîãðàììå èñïîëüçóåòñÿ äëÿ îïðåäåëåíèÿ êîëè÷åñòâà ïðèíÿòûõ â ïîðò áàéòîâ
 DWORD btr, temp,mask, signal;	//ïåðåìåííàÿ temp èñïîëüçóåòñÿ â êà÷åñòâå çàãëóøêè
 overlapped.hEvent = CreateEvent(NULL, true, true, NULL);	//ñîçäàòü ñèãíàëüíûé îáúåêò-ñîáûòèå äëÿ àñèíõðîííûõ îïåðàöèé
  SetCommMask(COMport, EV_RXCHAR);                   	        //óñòàíîâèòü ìàñêó íà ñðàáàòûâàíèå ïî ñîáûòèþ ïðè¸ìà áàéòà â ïîðò
 while(1)						//ïîêà ïîòîê íå áóäåò ïðåðâàí, âûïîëíÿåì öèêë
  {
   //cout<<"COM0 "<<endl;
   WaitCommEvent(COMport, &mask, &overlapped);               	//îæèäàòü ñîáûòèÿ ïðè¸ìà áàéòà (ýòî è åñòü ïåðåêðûâàåìàÿ îïåðàöèÿ)
   //cout<<"COM1 "<<endl;
   signal = WaitForSingleObject(overlapped.hEvent, INFINITE);	//ïðèîñòàíîâèòü ïîòîê äî ïðèõîäà áàéòà
    //cout<<"COM2 "<<endl;
   if(signal == WAIT_OBJECT_0)				        //åñëè ñîáûòèå ïðèõîäà áàéòà ïðîèçîøëî
    {
     if(GetOverlappedResult(COMport, &overlapped, &temp, true)) //ïðîâåðÿåì, óñïåøíî ëè çàâåðøèëàñü ïåðåêðûâàåìàÿ îïåðàöèÿ WaitCommEvent
      if((mask & EV_RXCHAR)!=0)					//åñëè ïðîèçîøëî èìåííî ñîáûòèå ïðèõîäà áàéòà
       {
        ClearCommError(COMport, &temp, &comstat);		//íóæíî çàïîëíèòü ñòðóêòóðó COMSTAT
        btr = comstat.cbInQue;                          	//è ïîëó÷èòü èç íå¸ êîëè÷åñòâî ïðèíÿòûõ áàéòîâ
        if(btr)                         			//åñëè äåéñòâèòåëüíî åñòü áàéòû äëÿ ÷òåíèÿ
        {
         ReadFile(COMport, bufrd, btr, &temp, &overlapped);     //ïðî÷èòàòü áàéòû èç ïîðòà â áóôåð ïðîãðàììû
         counter+=btr;  //óâåëè÷èâàåì ñ÷¸ò÷èê áàéòîâ
         return bufrd; 		//âûçûâàåì ôóíêöèþ äëÿ âûâîäà äàííûõ íà ýêðàí è â ôàéë
        }
       }
    }
  }
 CloseHandle(overlapped.hEvent);		//ïåðåä âûõîäîì èç ïîòîêà çàêðûòü îáúåêò-ñîáûòèå
}

void WriteThread()
{
 DWORD temp;
 BYTE b=0;
 b='0';
 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);
 WriteFile(COMport, &b, 1, &temp,&overlappedwr); // ïåðåäàòü 0 â ïîðò
 //cout<<"WriteFile "<<temp<<endl;
 CloseHandle(overlappedwr.hEvent);
}
//-----------------------------------------------------------------------
int Read(char* buf,DWORD len)
{
 if(!Connected)
        return 0;

 DWORD read=1;
 BYTE a=0;
 BYTE b=0;

 memset(buf,0,sizeof(BYTE)*len);
 b='0';
 WriteFile(COMport,&b,1,&read,0);

 b=0;
 memset(buf,0,sizeof(BYTE)*len);
 while(read>0)
 {
	b=0;
	ReadFile(COMport,&b,1,&read,0);
	if(b!=0xFF)
		continue;
	buf[0]=b;

	b=0;
	ReadFile(COMport,&b,1,&read,0);
	if(b!=0xFF)
		continue;
	buf[1]=b;

	b=0;
	ReadFile(COMport,&b,1,&read,0);
	if(b!=0xFF)
		continue;
	buf[2]=b;

	b=0;
	ReadFile(COMport,&b,1,&read,0);
	if(b!=0xFF)
		continue;
	buf[3]=b;

	b=0;
	break;
	}

    if(read==0)
	 return 0;

    for(DWORD i=4;i<len;i++)
	{
	 ReadFile(COMport,&b,1,&read,0);

	 if(read==0)
	 {
		read=i;
		break;
	 }
	 else
	 {
		read=i+1;
		buf[i]=b;
	 }
	}
 return read;
}
//-----------------------------------------------------------------------