#include <windows.h>
#include <tchar.h>
#include <stdio.h>
void PrintFilePermissions(LPCTSTR filePath) {
    DWORD fileAttrs = GetFileAttributes(filePath);
    if (fileAttrs == INVALID_FILE_ATTRIBUTES) {
        _tprintf(_T("Could not get file attributes for %s (error %d)\n"), filePath, GetLastError());
        return;
    }
    _tprintf(_T("File: %s\n"), filePath);
    if (fileAttrs & FILE_ATTRIBUTE_DIRECTORY) {
        _tprintf(_T("File Type: Directory\n"));
    } else {
        _tprintf(_T("File Type: Regular file\n"));
    }
    _tprintf(_T("Permissions: "));
    _tprintf(_T((fileAttrs & FILE_ATTRIBUTE_READONLY) ? "r--" : "rw-"));
    _tprintf(_T("r--"));
    _tprintf(_T("\n"));
}
int _tmain(int argc, TCHAR *argv[]) {
    if (argc != 2) {
        _tprintf(_T("Usage: %s <file_path>\n"), argv[0]);
        return 1;
    }
    PrintFilePermissions(argv[1]);
    return 0;
}
