#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Stack.h"

using namespace std;

string intToString(int num) {
    string stringNum;
    int tempNum = num;
    int digits = 0;
    do {
        tempNum /= 10;
        digits++;
    } while (tempNum != 0);
    int m = 0;
    do {
        tempNum = (num / pow(10, digits - 1)) - (10 * static_cast<int>(num / pow(10, digits)));
        stringNum += tempNum + 48;
        digits--;
        m++;
    } while (digits != 0);
    return stringNum;
}

int lengthOfString(const string str) //calculates length of a string
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

bool compareStrings(const string str1, const string str2) //compares 2 strings
{
    int count = 0;
    for (int i = 0; ; i++)
    {
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            break;
        }
        else if (str1[i] == '\0' || str2[i] == '\0')
        {
            return false; //both strings have different length i.e. also unequal
        }
        if (str1[i] == str2[i])
        {
            count++;
        }
    }
    if (count == lengthOfString(str2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkForDouble(const string str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            return true;
        }
    }
    return false;
}

double stringToIntDouble(string stringNum) {
    bool isDouble = checkForDouble(stringNum);
    if (isDouble) {
        int digits = lengthOfString(stringNum);
        digits--;
        int intPart = 0;
        int i = 0;
        for (;; i++, digits--) {
            if (stringNum[i] == '.') {
                i++;
                break;
            }
            intPart *= 10;
            intPart += stringNum[i] - 48;
        }
        double floatPart = 0;
        for (; digits != 0; i++, digits--) {
            floatPart *= 0.1;
            floatPart += static_cast<double>((stringNum[i] - 48)) * 0.1;
        }
        return static_cast<double>(intPart) + floatPart;
    }
    else {
        int digits = lengthOfString(stringNum);
        int num = 0;
        for (int i = 0; digits != 0; i++, digits--) {
            num *= 10;
            num += stringNum[i] - 48;
        }
        return num;
    }
}

bool doesStringInclude(string mainStr, string subStr) {
    bool firstCharFound = false;
    int lengthOfSubStr = lengthOfString(subStr);
    int count = 0;
    for (int i = 0, j = 0; mainStr[i] != '\0'; i++) {
        if (subStr[j] == '\0') {
            break;
        }
        if (!firstCharFound) {
            if (mainStr[i] == subStr[j]) {
                firstCharFound = true;
            }
        }
        if (firstCharFound == true) {
            if (mainStr[i] == subStr[j]) {
                count++;
                j++;
            }
            else {
                firstCharFound = false;
                j = 0;
                count = 0;
            }
        }
    }
    if (count == lengthOfSubStr) {
        return true;
    }
    return false;
}

int indexOfSubstring(string mainStr, string subStr) {
    bool firstCharFound = false;
    int lengthOfSubStr = lengthOfString(subStr);
    int count = 0;
    int indexOfSubStr = 0;
    for (int i = 0, j = 0; mainStr[i] != '\0'; i++) {
        if (subStr[j] == '\0') {
            break;
        }
        if (!firstCharFound) {
            if (mainStr[i] == subStr[j]) {
                firstCharFound = true;
                indexOfSubStr = i;
            }
        }
        if (firstCharFound == true) {
            if (mainStr[i] == subStr[j]) {
                count++;
                j++;
            }
            else {
                firstCharFound = false;
                j = 0;
                count = 0;
            }
        }
    }
    return indexOfSubStr;
}

Vector<string> tokenizeString(string str, char token) {
    Vector<string> strVec;
    string tempStr = "";
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == token) {
            if (tempStr != "") {
                strVec.pushBack(tempStr);
            }
            tempStr = "";
        }
        else {
            tempStr += str[i];
        }
    }
    strVec.pushBack(tempStr);
    return strVec;
}

template <class T>
void invertArray(Vector<T>& arr) {
    Stack<T> tempStk;
    for (int i = 0; i < arr.size(); i++) {
        tempStk.push(arr.get(i));
    }
    Vector<T> newVec;
    for (int i = 0; i < arr.size(); i++) {
        newVec.pushBack(tempStk.pop());
    }
    T temp = newVec.get(0);
    newVec.remove(0);
    newVec.pushBack(temp);
    arr = newVec;
}

void removeSource(string source, Vector<string>& path) {
    for (int i = 0; i < path.size(); i++) {
        if (path.get(i) == source) {
            path.remove(i);
        }
    }
}