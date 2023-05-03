#include <windows.h>
#include <Wininet.h>
#include <stdlib.h>

struct DlHandle_t
{
    HINTERNET hInet;
    HINTERNET hUrl;
    char* buffer;
    int buffersize;
    int bufferpos;
};


void CALLBACK InternetCallback(HINTERNET hInternet, DWORD_PTR dwcontext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{

}


extern "C" DlHandle_t* NewDLRequest()
{
    HINTERNET hInet = InternetOpenA("CoD4X-Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, INTERNET_FLAG_ASYNC);
    if(hInet == NULL)
    {
        return NULL;
    }
	int timeout = 15000;

	InternetSetOptionA(hInet, INTERNET_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
	InternetSetOptionA(hInet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));
	InternetSetOptionA(hInet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetStatusCallbackA(hInet, InternetCallback); 
    DlHandle_t* dl = (DlHandle_t*)malloc(sizeof(DlHandle_t));
    dl->hInet = hInet;
    return dl;
}

extern "C" bool StartDLRequest(DlHandle_t* dl, char* localname, const char* remotename)
{
	DWORD flags = INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_NO_UI | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE;
	HINTERNET hUrl = InternetOpenUrlA(dl->hInet, remotename, NULL, 0, flags, 0);
	if(hUrl == NULL)
	{
		InternetCloseHandle(dl->hInet);
        free(dl);
		return false;
	}
    dl->hUrl = hUrl;
    dl->buffer = (char*)malloc(64*1024);
    dl->buffersize = 64*1024;
    dl->bufferpos = 0;
    return true;
}


extern "C" void DeleteDLRequest(DlHandle_t* dl)
{
    if(dl->hUrl){
    	InternetCloseHandle(dl->hUrl);
        free(dl->buffer);
    }
	InternetCloseHandle(dl->hInet);
    free(dl);
}

extern "C" signed int GetDLRequestProgress(DlHandle_t* dl)
{
    if(dl->bufferpos == dl->buffersize)
    {
        int newsize = dl->buffersize << 1;
        char* newbuffer = NULL;
        newbuffer = (char*)realloc(dl->buffer, newsize);
        if(newbuffer)
        {
            dl->buffer = newbuffer;
        }else{
            return -1;
        }
    }
	DWORD size = 0;
    if(InternetReadFile(dl->hUrl, dl->buffer + dl->bufferpos, dl->buffersize - dl->bufferpos, &size) == TRUE)
    {
        dl->bufferpos += size;
        return 0;
    }else{
        DWORD error = GetLastError();
        if(error == ERROR_IO_PENDING)
        {
            return 0;
        }else if(error == INTERNET_STATUS_REQUEST_COMPLETE){
            return dl->bufferpos;
        }
    }
    return -1;
}

extern "C" void StopDLRequest(DlHandle_t* dl)
{

}


extern "C" void GetDLRequestName(DlHandle_t* dl, const char* outname, int maxnamelen)
{
    InternetQueryOptionA(dl->hUrl, INTERNET_OPTION_URL, (void*)outname, (DWORD*)&maxnamelen);
}

