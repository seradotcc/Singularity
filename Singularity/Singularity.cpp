#include <iostream>
#include <string>
#include <array>
#include <Windows.h>
#include "SHA256.h"

SHA256 shaObject;

std::string GetHashedResult(std::string input)
{
    shaObject.update(input);
    std::array<uint8_t, 32> digest = shaObject.digest();

    std::string result = {};
    for (int i = 0; i < 32; i++)
    {
        int value = digest[i] % 127;
        if (value < 33)
            value += 33;
        result += static_cast<char>(value);
    }

    return result;
}

bool CopyToClipboard(std::string input)
{
    const char* text = input.c_str();
    if (OpenClipboard(NULL)) {
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
        if (hMem != NULL) {
            char* pMem = static_cast<char*>(GlobalLock(hMem));

            strcpy_s(pMem, strlen(text) + 1, text);
            GlobalUnlock(hMem);

            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);

            CloseClipboard(); 
            return true;
        }
    }
    return false;
}



int main()
{
    std::string masterPass, identifier, result;
    std::cout << "Masterpass: " << std::endl;
    std::cin >> masterPass;
    std::cout << "Identifier: " << std::endl;
    std::cin >> identifier;
    result = GetHashedResult(masterPass + identifier);
    std::cout << "Generated Password: " << result << std::endl;
    if (CopyToClipboard(result))
    {
        std::cout << "Text copied to clipboard." << std::endl;
    }
    else
    {
        std::cout << "Failed to copy to clipboard." << std::endl;
    }
}