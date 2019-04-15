/*************************************************************************
	> File Name:    Application.cpp
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 21时57分51秒
 ************************************************************************/

#include "Application.h"

SKF::Application::Application (int argc, char** argv) {
    if (argc == 1) { 
        Usage();
        exit(0);
    }
    for (int i = 1; i < argc; i++) {
        if (i != argc - 1) {
            this->pattern.push_back(new std::string(argv[i]));
        } else {
            this->bufferFile = new std::string(argv[i]);
        }
    }
}

SKF::Application::~Application () {
    if (this->bufferFile) delete this->bufferFile;
    for (int i = 0; i < (int)this->pattern.size(); i++) {
        if (this->pattern[i]) delete this->pattern[i];
    }
}

int SKF::Application::run () {
    SKF::BTrie* root = new SKF::BTrie();
    int patternNum = (int)this->pattern.size();
    for (int i = 0; i < patternNum; i++) {
        int ret = root->insert(*(this->pattern[i]));
        if (!ret) return -1;
    }
    root->build();
    std::vector<int> ans(patternNum);
    
    char _temp[102400];
    FILE* fp = fopen((*this->bufferFile).c_str(), "r");
    if (!fp) return -2;
    fscanf(fp, "%s", _temp);
    fclose(fp);
    
    std::string buffer(_temp);
    int ret = root->match(buffer, ans);
    std::cout << "test!!!\n";
    if (!ret) return -3;
    
    std::cout << "Matching Number : " << std::endl;
    for (int i = 0; i < (int)ans.size(); i++) {
        std::cout << "[ " << ans[i] << " ] \"" << *this->pattern[i]  << "\""  << std::endl;
    }
    
    delete root;
    return 0;
}



void SKF::Usage () {
    std::cout << "Usage :\n\
    \tFindX 'pattern string' ... buffer string File\n\
    \teg.FindX 'abc' 'def' 'hello' ./test" << std::endl;
}
