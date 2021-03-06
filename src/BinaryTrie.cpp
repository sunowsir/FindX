/*************************************************************************
	> File Name:    BinaryTrie.cpp
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年04月14日 星期日 17时10分22秒
 ************************************************************************/

#include "BinaryTrie.h"

SKF::BTrie::BTrie () {
    this->indepChar = false;
    this->indepWord = false;
    this->count = 0;
    this->nodeNum = 0;
    this->child = new BTrie*[2];
    this->child[0] = this->child[1] = nullptr;
    this->fail = nullptr;
}

bool SKF::BTrie::insert (const std::string& pattern) {
    BTrie *root = this;
    int count = 0;
    for (int i = 0; i < (int)pattern.size(); i++) {
        std::string code = getCoding(pattern[i]);
        for (int j = 0; j < (int)code.size(); j++) {
            if (root->child[code[j] - '0'] == nullptr) {
                root->child[code[j] - '0'] = new BTrie();
                count++;
            }
            root = root->child[code[j] - '0'];
        }
        root->indepChar = true;
    }
    root->indepWord = true;
    root->count++;
    root->flag.push_back(this->nodeNum++);
    return true;
}

void SKF::BTrie::build () {
    BTrie* root = this;
    std::queue<BTrie*> q;
    q.push(root);
    while (!q.empty()) {
        BTrie* nowNode = q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            if (nowNode->child[i] == nullptr) {
                if (nowNode != root) {
                    nowNode->child[i] = nowNode->fail->child[i];
                }
                continue;
            }
            BTrie* p = (nowNode->fail ? nowNode->fail->child[i] : root);
            if (p == nullptr) p = root; 
            nowNode->child[i]->fail = p;
            q.push(nowNode->child[i]);
        }
    }
    return ;
}

int SKF::BTrie::match   (const std::string&     buffer, 
                         std::vector<int>&      ans) {
    int ret = 0;
    BTrie *root = this, *q = nullptr;
    for (int i = 0; i < (int)buffer.size(); i++) {
        std::string code = getCoding(buffer[i]);
        for (int j = 0; j < (int)code.size(); j++) {
            root = root->child[code[j] - '0'];
            if (!root) root = this;
            q = root;
        }
        while (q) {
            if (q->flag.size() > 0) {
                for (int j = 0; j < (int)q->flag.size(); j++) {
                    ans[q->flag[j]] += q->indepWord;
                }
            }
            ret += q->count;
            q = q->fail;
        }
        if (root == nullptr) root = this;
    }
    return ret;
}



