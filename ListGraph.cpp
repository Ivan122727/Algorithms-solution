#include "ListGraph.h"
#include <iostream>

ListGraph::ListGraph(const IGraph* graph) : size(graph->VerticesCount()),
g(std::vector<std::vector<int>>(graph->VerticesCount(), std::vector<int>())),
reversedG(std::vector<std::vector<int>>(graph->VerticesCount(), std::vector<int>()))
{
	for (int i = 0; i < size; i++)
	{
		std::vector<int> vertices;
		graph->FindAllAdjacentOut(i, vertices);
		for (int j : vertices)
		{
			AddEdge(i, j);
		}
	}
}

ListGraph::ListGraph(int size) : size(size), g(std::vector<std::vector<int>>(size, std::vector<int>())), reversedG(std::vector<std::vector<int>>(size, std::vector<int>())) {}

void ListGraph::AddEdge(int from, int to)
{
	g[from].push_back(to);
	reversedG[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
	return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const
{
	for (int x : reversedG[vertex])
	{
		vertices.push_back(x);
	}
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	for (int x : g[vertex])
	{
		vertices.push_back(x);
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
	ListGraph g(n);
	int from, to;
	for (int i = 0; i < n; i++)
	{
		std::cin >> from >> to;
		g.AddEdge(from, to);
	}
	std::cout << "Original Graph:\n";
	PrintGraph(g, g.VerticesCount());
	ListGraph g1(g);
	std::cout << "Copied Graph:\n";
	PrintGraph(g1, g1.VerticesCount());
	return 0;
}
