#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void PrintError( LPCSTR str)
{
    LPVOID lpMessageBuffer;
    int error = GetLastError();
    FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    error,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
    (LPTSTR) &lpMessageBuffer,
    0,
    NULL
    );
    printf("%s: (%d) %s\n\n",str,error,lpMessageBuffer);
    LocalFree( lpMessageBuffer );
}


//const char* ReadSerialLine(const char* com){

int ReadSerialLine(const char* com){

    // open port for I/O
    string myString;
    HANDLE h = CreateFile(com,
    GENERIC_READ|GENERIC_WRITE,
    0,NULL,
    OPEN_EXISTING,0,NULL); // my adruino on com4 but this value can be read from argv

    if(h == INVALID_HANDLE_VALUE) {
    PrintError("E012_Failed to open port");
    return 1;
    } else {

      //  printf("UNO\n");
    // set timeouts
    //COMMTIMEOUTS cto = { 1, 100, 1000, 0, 0 };
    DCB dcb;
    //if(!SetCommTimeouts(h,&cto))
    //PrintError("E013_SetCommTimeouts failed");

    // set DCB
    memset(&dcb,0,sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);
    dcb.BaudRate = 115200;
    dcb.fBinary = 1;
    dcb.fOutxCtsFlow = 1;
    dcb.fRtsControl = DTR_CONTROL_HANDSHAKE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE; // avoid reset of arduino board
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.ByteSize = 8;

    if(!SetCommState(h,&dcb)){PrintError("E014_SetCommState failed");}

        char buf[50];
        buf[19] = '\0';
        DWORD read = 0;

        ReadFile(h,buf,sizeof(buf)-1,&read,NULL); // read is updated with the number of bytes read


        myString = buf;

        CloseHandle(h);

    }
//return myString.c_str();
    printf (myString.c_str());
    return 0;
}

void usage(char* progname) {
    cout<<"Uso: "<< progname <<" PARAMETROS \n";
}

void version(){
    printf("VERSION alpha\n");
}

bool getdata(char* com){

    //cout<<"CERO\n";
    int i=0;

    char* readline;
    for (i=0;;i++) {
        if(ReadSerialLine(com) != 0){
            return 1;
        };

        //printf(readline);

    }

    return 0;
}


int main(int argc, char** argv) {


       int aflag = 0;
       int bflag = 0;
       char *cvalue = NULL;
       char *avalue = NULL;
       int index;
       int c;

       opterr = 0;

       while ((c = getopt (argc, argv, "a:bc:hv")) != -1)
         switch (c)
           {
           case 'h':
             usage(argv[0]);
             return 1;
           case 'v':
             version();
             return 1;
           case 'a':
             aflag = 1;
             avalue = optarg;
             break;
           case 'b':
             bflag = 1;
             break;
           case 'c':
             cvalue = optarg;
             break;
           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
           }

       printf ("aflag = %d, bflag = %d, cvalue = %s\n",
               aflag, bflag, cvalue);

       for (index = optind; index < argc; index++)
         printf ("Non-option argument %s\n", argv[index]);


//  if ( argc != 2 ) // argc should be 2 for correct execution
//    // We print argv[0] assuming it is the program name
//    usage(argv[0]);
//
//  else {
    if(!getdata(cvalue)){return 1;};

//  }
    //}

return 0;
}

