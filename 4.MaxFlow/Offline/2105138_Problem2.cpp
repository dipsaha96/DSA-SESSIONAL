#include <bits/stdc++.h>
#include "Ford_Fulkerson.cpp"
using namespace std;

int main()
{
    //freopen("in2.txt", "r", stdin);
    vector<vector<int>> man;
    vector<vector<int>> woman;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        int hgt, age, is_Divorced;
        cin >> hgt >> age >> is_Divorced;
        man.push_back({hgt, age, is_Divorced});
    }

    for (int i = 0; i < n; i++)
    {
        int hgt, age, is_Divorced;
        cin >> hgt >> age >> is_Divorced;
        woman.push_back({hgt, age, is_Divorced});
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = m + 1; j <= m + n; j++)
        {
            if (abs(man[i - 1][0] - woman[j - m - 1][0]) <= 10 )
            {
                if(abs(man[i - 1][1] - woman[j - m - 1][1]) <= 5 )
                {
                    if( man[i - 1][2] == woman[j - m - 1][2])
                    {
                        graph[i].push_back({j, 1});
                    }
                }
                
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        graph[0].push_back({i, 1});
    }

    for (int i = m + 1; i <= m + n; i++)
    {
        graph[i].push_back({m + n + 1, 1});
    }
    int ans=ford_Fulkerson(0,m+n+1);
    cout << ans << endl;
    return 0;
}