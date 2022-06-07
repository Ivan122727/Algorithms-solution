﻿#include "MatrixGraph.h"
#include <iostream>

MatrixGraph::MatrixGraph(const IGraph* graph) : size(graph->VerticesCount()), g(std::vector<std::vector<bool>>(graph->VerticesCount(), std::vector<bool>(graph->VerticesCount())))
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

MatrixGraph::MatrixGraph(int size) : size(size), g(std::vector<std::vector<bool>>(size, std::vector<bool>(size))) {}

void MatrixGraph::AddEdge(int from, int to) 
{
	g[from][to] = true;
}

int MatrixGraph::VerticesCount() const 
{
	return size;
}

void MatrixGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const 
{
	for (int i = 0; i < size; ++i) 
	{
		if (g[i][vertex]) 
		{
			vertices.push_back(i);
		}
	}
}

void MatrixGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const 
{
	for (int i = 0; i < size; ++i) 
	{
		if (g[vertex][i])
		{
			vertices.push_back(i);
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
	MatrixGraph g(n);
	int from, to;
	for (int i = 0; i < n; i++)
	{
		std::cin >> from >> to;
		g.AddEdge(from, to);
	}
	std::cout << "Original Graph:\n";
	PrintGraph(g, g.VerticesCount());
	MatrixGraph g1(g);
	std::cout << "Copied Graph:\n";
	PrintGraph(g1, g1.VerticesCount());
	return 0;
}