#include "comun.hpp"

using namespace std;

string trad::binToStr(char c) {
    std::string temp = "", res = "";
    while (c != 0) {
        temp += c % 2 == 0 ? '0' : '1';
        c /= 2;
    }
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        res += *it;
    }
    return res;
}

char trad::strToBin(std::string s) {
    char res = 0;
    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        res = res << 1;
        res += *it - '0';
    }
    return res;
}
