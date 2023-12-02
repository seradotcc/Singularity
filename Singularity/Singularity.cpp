#include <iostream>
#include <string>
#include <array>
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





int main()
{
    std::cout << GetHashedResult("Hello, world!") << std::endl;;
}