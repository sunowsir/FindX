/*************************************************************************
	> File Name:    FindXmain.cpp
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 19时08分47秒
 ************************************************************************/

#include "BinaryTrie.h"

#include <iostream>


int main () {
    SKF::BTrie *root = new SKF::BTrie();
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string pattern;
        std::cin >> pattern;
        root->insert(pattern);
    }
    root->build();
    std::string buffer;
    std::cin >> buffer;
    std::vector<int> ans(n);
    root->match(buffer, ans);
    for (int i = 0; i < (int)ans.size(); i++) {
        std::cout << i << " : " << ans[i] << std::endl;
    }
    
    delete root;
    return 0;
}
