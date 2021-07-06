
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class graphe
{
public:
    int index;
    std::string name;
    int adj[3];
    graphe(int index, std::string name);
    ~graphe();
    void print();
};

graphe::graphe(int index, std::string name) : index(index), name(name)
{
    this->adj[0] = -1;
    this->adj[1] = -1;
    this->adj[2] = -1;
}

graphe::~graphe(){}

void graphe::print()
{
    std::cout << index << ", " << name << ", " << adj[0] << ", " << adj[1] << ", " << adj[2] << std::endl;
}

void add_node(std::vector<graphe> &g, int index, std::string name)
{
    graphe node(index, name);
    g.push_back(node);
}

void add_edge(std::vector<graphe> &g, int v1, int v2)
{
    for (int i = 0; i < 3; i++)
    {
        if (g[v1].adj[i] == -1)
        {
            g[v1].adj[i] = v2;
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (g[v2].adj[i] == -1)
        {
            g[v2].adj[i] = v1;
            break;
        }
    }
}

int get_index(std::vector<graphe> g, int index, char c2)
{
    std::string v2;
    v2.push_back(c2);
    if (index == -1)
        return (-1);
    for (int i = 0; i < 3; i++)
    {
        if (g[g[index].adj[i]].name == v2)
            return (g[index].adj[i]);
    }
    return (-1);
}

int get_first_index(std::vector<graphe> g,char c1, char c2)
{
    std::string v1;
    std::string v2;
    int i;

    v1.push_back(c1);
    v2.push_back(c2);
    for (i = 0; g[i].name != v1 && i < g.size(); i++)
        ;
    if (i == g.size())
        return (-1);
    if (get_index(g, i, c2) != -1)
        return (i);
    for (i = 0; g[i].name != v1; i++)
        ;
    if (get_index(g, i, c2 != -1))
        return (i);
    return (-1);
}

void get_walk(std::vector<graphe> g, std::string path)
{
    std::vector<int> walk;
    int next;
    int i;
    int index;
    int start;
    std::cout << "path " << path << std::endl;
    for (i = 0; path[i] == path[i + 1] && i + 1 < path.length(); i++)
        ;
    if(i == path.length() -1)
        i = 0;
    start = i;
    index = get_first_index(g, path[i], path[i + 1]);
    walk.push_back(index);
    for (; i + 1 < path.length(); i++)
    {
        next = get_index(g, index,  path[i + 1]);
        if (next != -1)
            walk.push_back(next);
        else
        {
            std::cout << -1 << std::endl;
            return;
        }
        index = next;
    }
    i = start;
    index = get_first_index(g, path[i], path[i - 1]); 
    for (; i - 1 >= 0; i--)
    {
        next = get_index(g, index,  path[i - 1]);
        if (next != -1)
            walk.insert(walk.begin(), next); // g.push_front(next)
        else
        {
            std::cout << -1 << std::endl;
            break;
        }
        index = next;
    }
    std::cout << "(";
    for (i = 0; i < walk.size() - 1; i++)
        std::cout << walk[i] << ", ";
    std::cout << walk[i] << ")" << std::endl;
    
}



int main()
{
    std::vector<graphe> g;
    std::string Vertices[] = {"A", "B", "C", "D", "E", "A", "B", "C", "D", "E"};

    int Edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {0, 5}, {1, 6}\
    , {2, 7}, {3, 8}, {4, 9}, {5, 7}, {5, 8}, {6, 8}, {6, 9}, {7, 9}, {-1, -1}};

    for (int i = 0; i < 10; i++)
        add_node(g, i, Vertices[i]);
    for(int i = 0; Edges[i][0] != -1; i++)
        add_edge(g, Edges[i][0], Edges[i][1]);
    get_walk(g, "AABBBBBB");
    return 0;
}
