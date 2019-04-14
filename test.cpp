/*************************************************************************
    > File Name:    FindXmain.cpp
    > Author:       sunowsir
    > Mail:         sunow.wang@gmail.com
    > Created Time: 2019年04月14日 星期日 09时52分39秒
************************************************************************/


#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* BTrie 的结构定义 */
typedef struct Binary_Trie {
    /* char_flag: 标记独⽴成字，word_flag: 标记独⽴成词 */
    int char_flag, word_flag, count, flag[100];
    struct Binary_Trie **child, *fail;
} Binary_Trie, *BTrie;


/* 获取字符的编码 */
unsigned char *get_coding(unsigned char one_of_char_in_buffer) {
    int code = one_of_char_in_buffer, ret_len = 0;
    unsigned char *ret = (unsigned char *)calloc(sizeof(unsigned char), 20);
    while (code) {
        ret[ret_len++] = code % 2 + '0';
        code /= 2;
    }
    return ret;
}

#define SIZE 2
#define BASE '0'

/* BTrie 的获取新节点的函数 */
BTrie BTrie_get_new_node() {
    BTrie bt = (BTrie)calloc(sizeof(Binary_Trie), 1);
    bt->child = (Binary_Trie **)calloc(sizeof(BTrie), 2);
    return bt;
} 

/* BTrie 的插⼊函数 */
int BTrie_insert(BTrie root, unsigned char *buffer, int num) {
    BTrie p = root;
    int count = 0;
    for (int i = 0; buffer[i]; i++) {
        unsigned char *coding = get_coding(buffer[i]);
        // printf("%c : <%s>\n", buffer[i], coding);
        /* 根据获取到的每个字符的编码向下建树 */
        for (int j = 0; coding[j]; j++) {
            if (p->child[coding[j] - BASE] == NULL) {
                p->child[coding[j] - BASE] = BTrie_get_new_node();
                count++;
            } 
            p = p->child[coding[j] - BASE];
        } 
        
        /* 标记独⽴成字 */
        p->char_flag = 1;
        free(coding);
    } 
    
    /* 标记独⽴成词 */
    p->word_flag = 1;
    p->count++;
    p->flag[++p->flag[0]] = num;
    return count;
} 


/* BTrie 的线索化和失败指针建⽴函数 */
void BTrie_build(BTrie root, int node_number) {
    std::queue<BTrie> q;
    root->fail = NULL;
    q.push(root);
    while (!q.empty()) {
        BTrie now_node = q.front();
        q.pop();
        for (int i = 0; i < SIZE; i++) {
            if (now_node->child[i] == NULL) {
                if (now_node != root) {
                    now_node->child[i] = now_node->fail->child[i];
                } 
                continue;
            } 
            BTrie p = (now_node->fail ? now_node->fail->child[i] : root);
            if (p == NULL) {
                p = root;
            } 
            now_node->child[i]->fail = p;
            q.push(now_node->child[i]);
        }
    } 
    return ;
} 

/* BTrie 的匹配函数 */
int BTrie_match_count(BTrie root, unsigned char *str, int *num) {
    int ret = 0;
    BTrie p = root, q;
    while (str[0]) {
        unsigned char *coding = get_coding(str[0]);
        for (int i = 0; coding[i]; i++) {
            p = p->child[coding[i] - BASE];
            q = p;
        } 
        while (q) {
            if (q->flag[0] > 0) {
                for (int i = 1; i <= q->flag[0]; i++) {
                    num[q->flag[i]] += q->word_flag;
                }
            } 
            ret += q->count;
            // q->count = 0;
            q = q->fail;
        } 
        if (p == NULL) {
            p = root;
        } 
        free(coding);
        str++;
    } 
    return ret;
} 

#undef SIZE

/* Binary Trie End */

int main() {
    int n, cnt = 0;
    BTrie root = BTrie_get_new_node();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        unsigned char pattern[100005] = {0};
        scanf("%s", pattern);
        cnt += BTrie_insert(root, pattern, i);
    } 
    BTrie_build(root, cnt);
    unsigned char buffer[100005] = {0};
    scanf("%s", buffer);
    int ans[n] = {0};
    int total_count = BTrie_match_count(root, buffer, ans);
    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", i, ans[i]);
    } 
    return 0;
}


