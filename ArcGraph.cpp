#include "ArcGraph.h"
#include <iostream>

ArcGraph::ArcGraph(const IGraph* graph) : size(graph->VerticesCount()) 
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

ArcGraph::ArcGraph(int size) : size(size){}

void ArcGraph::AddEdge(int from, int to) 
{
    g.push_back({from, to});
} 

int ArcGraph::VerticesCount() const 
{
	return size;
}

void ArcGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const
{
	for (auto i : g) 
	{
		if (i.first == vertex) 
		{
			vertices.push_back(i.second);
		}
	}
}

void ArcGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const 
{
	for (const auto& i : g) 
	{
		if (i.second == vertex)
		{
			vertices.push_back(i.first);
		}
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
	ArcGraph g(n);
	int from, to;
	for (int i = 0; i < n; i++)
	{
		std::cin >> from >> to;
		g.AddEdge(from, to);
	}
	std::cout << "Original Graph:\n";
	PrintGraph(g, g.VerticesCount());
	ArcGraph g1(g);
	std::cout << "Copied Graph:\n";
	PrintGraph(g1, g1.VerticesCount());
	return 0;
}