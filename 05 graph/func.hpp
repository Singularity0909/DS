#pragma once
using namespace std;

void addEdge(int u, int v, int w)
{
    e[tot].to = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot++;
}

void init()
{
    tot = 0;
    id.clear();
    memset(head, -1, sizeof head);
    memset(vis, false, sizeof vis);
    memset(g, 0x3f, sizeof g);
    memset(dis, 0x3f, sizeof dis);
    cout << "请输入地点个数: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        pre[i] = i;
        cout << "请输入第 " << i << " 个地点的名称: ";
        cin >> name[i];
        id[name[i]] = i;
    }
    cout << "请输入道路条数: ";
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cout << "请分别输入第 " << i << " 条道路的两端地点名称及长度: ";
        string name1, name2;
        int w;
    input:
        cin >> name1 >> name2 >> w;
        if (id.find(name1) == id.end() || id.find(name2) == id.end())
        {
            cout << "地点不存在，请重新输入: ";
            goto input;
        }
        int u = id[name1], v = id[name2];
        g[u][v] = g[v][u] = min(g[u][v], w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    cout << endl << "网络图初始化成功" << endl;
}

void dijkstra()
{
    cout << "请分别输入源点名称和汇点名称: ";
    string name_src, name_des;
    cin >> name_src >> name_des;
    if (id.find(name_src) == id.end() || id.find(name_des) == id.end())
    {
        cout << "地点不存在" << endl;
        return;
    }
    int src = id[name_src], des = id[name_des];
    q.push(p(dis[src] = 0, src));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[u] + w)
            {
                pre[v] = u;
                dis[v] = dis[u] + w;
                q.push(p(dis[v], v));
            }
        }
    }
    cout << endl << name_src << " 到 " << name_des << " 的最短路径如下: " << endl;
    top = 0;
    for (int i = des; i != src; i = pre[i]) sta[top++] = i;
    for (int i = top - 1, last = src; i >= 0; i--)
    {
        int u = last, v = sta[i];
        cout << "从 " << name[u] << " 到 " << name[v] << endl;
        last = v;
    }
    cout << "总路程为 " << dis[des] << endl << endl;
}

void floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            cout << name[i] << " 到 " << name[j] << " 的最短路径长为 " << g[i][j] << endl << endl;
}
