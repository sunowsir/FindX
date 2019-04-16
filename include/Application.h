/*************************************************************************
	> File Name:    Application.h
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 21时53分39秒
 ************************************************************************/

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <cstdio>
#include <cstring>

#include <vector>
#include <string>
#include <iostream>

#include "BinaryTrie.h"

namespace SKF {
    class Application {
    private : 
        std::vector<std::string*> pattern;
        std::string *bufferFile;
    public : 
        Application(int, char**);
        int run();
        ~Application();
    };
    void Usage ();
}

#endif
