#include "charUtils.h"  
using namespace std;

int my_strcmp(const char *str1, const char *str2)
{

    while (*str1 != '\0' && (*str1 == *str2))
    {
        str1++; 
        str2++;
    }

    return static_cast<int>(static_cast<unsigned char>(*str1) -
                            static_cast<unsigned char>(*str2));
}

char *my_strcpy(char *dest, const char *src)
{
    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0')
        ;
    return original_dest;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *original_dest = dest;
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    for (; i < n; ++i)
    {
        dest[i] = '\0';
    }

    return original_dest;
}

size_t my_strlen(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
    {
        ++length;
    }
    return length;
}

bool my_isalpha(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
    {
        return true;
    }
    // Русские буквы в кодировке Windows-1251
    if ((ch >= '\xC0' && ch <= '\xDF') || 
        (ch >= '\xE0' && ch <= '\xFF'))
    { 
        return true;
    }
    return false;
}

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (str1[i] == '\0' || str2[i] == '\0' || str1[i] != str2[i])
        {
            return static_cast<int>(static_cast<unsigned char>(str1[i]) -
                                    static_cast<unsigned char>(str2[i]));
        }
    }
    return 0;
}

bool my_isdigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

char *my_strncat(char *dest, const char *src, size_t n)
{
    char *ptr = dest;
    while (*ptr)
        ++ptr;

    size_t i = 0;
    while (i < n && *src)
    {
        *ptr++ = *src++;
        ++i;
    }
    *ptr = '\0';

    return dest;
}

#include <iostream>
#include <cstring>
#include <cctype>

bool parseDate(const char *data, int *day, int *month, int *year)
{
    
    if (data == nullptr || data[0] == '\0')
    {
        return false;
    }

    int values[3] = {0}; 
    int valueIndex = 0;  
    int pos = 0;        
    int length = my_strlen(data);

    while (pos < length && valueIndex < 3)
    {
        while (pos < length && data[pos] == ' ')
        {
            pos++;
        }

        if (pos >= length)
        {
            break;
        }

  
        int start = pos;
        int number = 0;

        while (pos < length && my_isdigit(data[pos]))
        {
            number = number * 10 + (data[pos] - '0');
            pos++;
        }

      
        if (start == pos)
        { 
            return false;
        }

        values[valueIndex++] = number;

        if (pos < length && data[pos] != ' ')
        {
            return false;
        }
    }

  
    if (valueIndex != 3 || pos != length)
    {
        return false;
    }


    if (values[0] < 1 || values[0] > 31 ||
        values[1] < 1 || values[1] > 12 ||
        values[2] < 1)
    {
        return false;
    }


    *day = values[0];
    *month = values[1];
    *year = values[2];

    return true;
}

