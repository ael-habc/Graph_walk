
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
    std::string letter;
    int adj[3];
    graphe(int index, std::string letter);
    ~graphe();
    void print();
};

graphe::graphe(int index, std::string letter) : index(index), letter(letter)
{
    this->adj[0] = -1;
    this->adj[1] = -1;
    this->adj[2] = -1;
}

graphe::~graphe()
{

}

void graphe::print()
{
    std::cout << index << ", " << letter << ", " << adj[0] << ", " << adj[1] << ", " << adj[2] << std::endl;
}

void add_node(std::vector<graphe> &g, int index, std::string letter)
{
    graphe node(index, letter);
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
        if (g[g[index].adj[i]].letter == v2)
            return (g[index].adj[i]);
    }
    return (-1);
}

int get_first_index(std::vector<graphe> g,char c1, char c2)
{
    std::string v1;
    std::string v2;
    int index;
    int i;

    v1.push_back(c1);
    v2.push_back(c2);
    for (i = 0; g[i].letter != v1; i++)
        ;
    index = get_index(g, i, c2);
    std::cout << "index " << index << std::endl;
    if (index != -1)
        return (get_index(g, index, c1));
    for (i = 0; g[i].letter != v1; i++)
        ;
    index = get_index(g, i, c2);
    return (get_index(g, index, c1));
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
    std::cout << "first char index " << i << std::endl;
    start = i;
    index = get_first_index(g, path[i], path[i + 1]);
    std::cout << index << std::endl;
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
    i = start + 1;
    index = get_first_index(g, path[i], path[i - 1]);
    for (; i - 1 >= 0; i--)
    {
        next = get_index(g, index,  path[i - 1]);
        if (next != -1)
            walk.insert(walk.begin(), next);
        else
        {
            std::cout << -1 << std::endl;
            break;
        }
        index = next;
    }
    for (i = 0; i < walk.size(); i++)
        std::cout << walk[i] << ", ";
    std::cout << std::endl;
    
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
    // for (int i = 0; i < 10; i++)
    //     g[i].print();
    get_walk(g, "AAAB");
    return 0;
}
