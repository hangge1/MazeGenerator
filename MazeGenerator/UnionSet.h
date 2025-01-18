#pragma once

#include <vector>

class UnionSet
{
public:
    void Init(int n)
    {
        this->n = n;
        Parent.resize(n);
        Size.resize(n, 1);
        for(int i = 0; i < n; i++)
        {
            Parent[i] = i;
        }
    }

    int Find(int i)
    {
        int root = i;
        while(Parent[root] != root)
            root = Parent[root];
        
        int cur = i;
        while(cur != root)
        {
            int parent = Parent[cur];
            Parent[cur] = root;
            cur = parent;
        }
        return root;
    }

    bool IsSameSet(int a, int b)
    {
        return Find(a) == Find(b);
    }

    void Union(int a, int b)
    {
        int fa = Find(a);
        int fb = Find(b);
        if(Size[fa] > Size[fb])
        {
            Parent[fb] = fa;
            Size[fa]++;
        }
        else
        {
            Parent[fa] = fb;
            Size[fb]++;
        }
    }

    int GetSetCount()
    {
        int res = 0;
        for(int i = 0; i < n; i++)
        {
            if(Parent[i] == i)
            {
                res++;
            }
        }
        return res;
    }

   /* void Print()
    {
        for(int i = 0; i < n; i++)
        {
            std::cout << i << " -> " << Parent[i] << std::endl;
        }
        std::cout << endl;
    }*/
   
private:
    std::vector<int> Parent;
    std::vector<int> Size;
    int n;
};