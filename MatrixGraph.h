#include "IGraph.h"

class MatrixGraph : IGraph 
{
public:
	MatrixGraph(const IGraph* graph);
	MatrixGraph(int size);
	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const;
	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;
private:
	int size;
	std::vector<std::vector<bool>> g;
};
