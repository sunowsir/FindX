/*************************************************************************
	> File Name:    CodingSystem.cpp
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 16时32分33秒
 ************************************************************************/

#include "CodingSystem.h"


std::string SKF::getCoding (unsigned char character) {
    int code = character;
    std::string ret = "";
    while (code) {
        ret += code % 2 + '0';
        code /= 2;
    }
    return ret;
}
