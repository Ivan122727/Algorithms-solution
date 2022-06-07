#include <vector>

class IGraph
{
public:
	virtual ~IGraph(){}
	virtual void AddEdge(int from, int to) = 0;
	virtual int VerticesCount() const = 0;
	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const = 0;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const = 0;
};

