#include <iostream>
#include <vector>

class QuickFind
{
private:
    std::vector<int> m_id;

public:
    QuickFind(size_t n)
    {
        m_id.reserve(n);
        for (int i = 0; i < n; i++)
        {
            m_id.push_back(i);
        }
    }

    void Union(int p, int q)
    {
        int newVal = m_id[q];
        int oldVal = m_id[p];

        for (int i = 0; i < m_id.size(); i++)
        {
            if (m_id[i] == oldVal)
            {
                m_id[i] = newVal;
            }
        }
    }

    bool Find(int p, int q)
    {
        return m_id[p] == m_id[q];
    }

};

// Contains path compression and union by rank
class QuickUnion
{
private:
    std::vector<int> m_id;
    std::vector<int> m_rank;

    int Find(int p)
    {
        int parent = m_id[p];
        while (parent != p)
        {
            parent = m_id[parent];
            p = m_id[p];
        }

        return parent;
    }

public:
    QuickUnion(size_t n)
    {
        m_id.reserve(n);
        m_rank.reserve(n);

        for(int i = 0; i < n; i++)
        {
            m_id.push_back(i);
            m_rank.push_back(0);
        }
    }

    void Union(int p, int q)
    {
        int parentP = Find(p);
        int parentQ = Find(q);

        if (parentP == parentQ)
        {
            return;
        }

        // make p the larger parent
        if (parentP < parentQ)
        {
            int temp = parentP;
            parentP = parentQ;
            parentQ = temp;
        }

        // Now that Q is smaller, set it's parent as P!
        m_id[parentQ] = parentP;

        if (m_rank[parentQ] == m_rank[parentP])
        {
            m_rank[parentP]++;
        }
    }

    // Uses Tarjan's non-recursive optimization for path compression
    bool Find(int p, int q)
    {
        return Find(p) == Find(q);
    }
};
int main()
{
    QuickFind qf(10);
    qf.Union(5,9);
    qf.Union(1,5);

    std::cout << qf.Find(1,9) << std::endl;

    QuickUnion qu(100);
    std::cout << qu.Find(4,88) << std::endl;
    for(int i = 0; i < 99; i++)
    {
        qu.Union(i, i+1);
    }

    std::cout << qu.Find(4,88) << std::endl;
}