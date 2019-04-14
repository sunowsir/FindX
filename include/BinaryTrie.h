/*************************************************************************
	> File Name:    BinaryTrie.h
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 17时10分10秒
 ************************************************************************/

#ifndef _BINARYTRIE_H
#define _BINARYTRIE_H

#include <vector>
#include <queue>
#include <string>

#include "CodingSystem.h"

namespace SKF {
    
    class BTrie {
    private : 
        bool indepChar;
        bool indepWord;
        int count;
        int nodeNum;
        std::vector<int> flag;
        BTrie **child, *fail;
    public : 
        BTrie();
        bool insert(std::string pattern);
        void build();
        int match(std::string str, std::vector<int>& ans);
    };
}

#endif
