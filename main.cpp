
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

void get_walk(std::vector<graphe> g, std::string path)
{
    
}

int main()
{
    std::vector<graphe> g;
    int Edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 7}, {5, 8}, {6, 8}, {6, 9}, {7, 9}, {-1, -1}};

    std::string Vertices[] = {"A", "B", "C", "D", "E", "A", "B", "C", "D", "E"};
    for (int i = 0; i < 10; i++)
    {
        add_node(g, i, Vertices[i]);
    }
    for(int i = 0; Edges[i][0] != -1; i++)
    {
        add_edge(g, Edges[i][0], Edges[i][1]);
    }

    for (int i = 0; i < 10; i++)
    {
        g[i].print();
    }
    return 0;
}