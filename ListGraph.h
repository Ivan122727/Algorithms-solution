#include "IGraph.h"

class ListGraph : IGraph
{
public:
	ListGraph(const IGraph* graph);
	ListGraph(int size);
	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const;
	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;
private:
	int size;
	std::vector<std::vector<int>> g;
	std::vector<std::vector<int>> reversedG;
};