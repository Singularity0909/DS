#pragma once
using namespace std;

typedef pair<int, int> p;
const int maxn = 1e4 + 10;
const int maxm = 1e5 + 10;
bool vis[maxn];
int n, m, tot, top;
int head[maxn], dis[maxn], pre[maxn], sta[maxn], g[maxn][maxn];
string name[maxn];
struct node { int to, w, nxt; } e[maxm];
priority_queue<p, vector<p>, greater<p> > q;
unordered_map<string, int> id;
