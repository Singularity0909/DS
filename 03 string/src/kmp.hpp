#pragma once
using namespace std;

const int maxn = 1e5 + 10;
int nxt[maxn], pos[maxn];

void getNext(char* p)
{
    int len = (int)strlen(p + 1);
    for (int i = 2, j = 0; i <= len; i++)
    {
        while (j && p[i] != p[j + 1]) j = nxt[j];
        if (p[i] == p[j + 1]) j++;
        nxt[i] = j;
    }
}

int kmp(char* s, char* p)
{
    int cnt = 0;
    int slen = (int)strlen(s + 1), plen = (int)strlen(p + 1);
    for (int i = 1, j = 0; i <= slen; i++)
    {
        while (j && s[i] != p[j + 1]) j = nxt[j];
        if (s[i] == p[j + 1]) j++;
        if (j == plen)
        {
            pos[cnt++] = i - plen + 1;
            j = nxt[j];
        }
    }
    return cnt;
}
