#include "IGraph.h"
#include <unordered_set>  

class SetGraph : IGraph 
{
public:
	SetGraph(const IGraph* graph);
	SetGraph(int size);
	virtual void AddEdge(int from, int to);
	virtual int VerticesCount() const;
	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;
private:
	int size;
	std::vector<std::unordered_set<int>> g;
	std::vector<std::unordered_set<int>> reversedG;
};
