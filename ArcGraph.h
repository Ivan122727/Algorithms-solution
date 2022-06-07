#include "IGraph.h"

class ArcGraph : IGraph
{
public:
	ArcGraph(const IGraph* graph);
	ArcGraph(int size);
	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const;
	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;
private:
	int size;
	std::vector<std::pair<int, int>> g;
};
