#include "SetGraph.h"
#include <iostream>

SetGraph::SetGraph(const IGraph* graph) : size(graph->VerticesCount()), g(graph->VerticesCount(), std::unordered_set<int>()), reversedG(graph->VerticesCount(), std::unordered_set<int>())
{
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> vertices;
		graph->FindAllAdjacentOut(i, vertices);
		for (int j : vertices) 
		{
			AddEdge(i, j);
		}
	}
}

SetGraph::SetGraph(int size) : size(size), g(size, std::unordered_set<int>()), reversedG(size, std::unordered_set<int>()){}

void SetGraph::AddEdge(int from, int to) 
{
	g[from].insert(to);
	reversedG[to].insert(from);
}

int SetGraph::VerticesCount() const
{
	return size;
}

void SetGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const 
{
	for (int i : reversedG[vertex]) 
	{
		vertices.push_back(i);
	}
}

void SetGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const 
{
	for (int i : g[vertex]) 
	{
		vertices.push_back(i);
	}
}

template<class T>
void PrintGraph(T graph, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::vector<int> ans;
		std::cout << i << ":\nin: ";
		graph.FindAllAdjacentIn(i, ans);
		for (auto& c : ans)
		{
			std::cout << c << " ";
		}
		ans.clear();
		std::cout << "\nout: ";
		graph.FindAllAdjacentOut(i, ans);
		for (auto& c : ans)
		{
			std::cout << c << " ";
		}
		std::cout << "\n";
	}
}

int main()
{
	int n;
	std::cin >> n;
	SetGraph g(n);
	int from, to;
	for (int i = 0; i < n; i++)
	{
		std::cin >> from >> to;
		g.AddEdge(from, to);
	}
	std::cout << "Original Graph:\n";
	PrintGraph(g, g.VerticesCount());
	SetGraph g1(g);
	std::cout << "Copied Graph:\n";
	PrintGraph(g1, g1.VerticesCount());
	return 0;
}
