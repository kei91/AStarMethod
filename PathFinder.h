#pragma once

#include <queue>

struct Node
{
    Node(int _index, int _x, int _y, int _parentIndex, int _distanceFromStart, int _weight)
        : index(_index)
        , x(_x)
        , y(_y)
        , parentIndex(_parentIndex)
        , distanceFromStart(_distanceFromStart)
        , weight(_weight)
    {}

    int index = 0;
    int x = 0;
    int y = 0;
    int parentIndex = 0;
    int distanceFromStart = 0;
    int weight = 0; // Sum of the distance from start node to current node and distance from target node to curren node
};

bool operator>(const Node& left, const Node& right);

class PathFinder
{
public:
    PathFinder(std::pair<int, int> start, std::pair<int, int> target, const std::vector<int>& map, std::pair<int, int> mapDimensions);
    ~PathFinder() = default;

    bool FindPath(std::vector<int>& outPath);

private:
    void CalculateData(const Node& node);
    void AddNodeToQueue(const Node& parentNode, const int x, const int y);

    int FindIndex(const int x, const int y);
    int CalculateDistance(const int x, const int y);

private:
    std::pair<int, int> _start;
    std::pair<int, int> _target;

    std::vector<int> _map;
    std::pair<int, int> _mapDimensions;

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> _nodesQueue;

    std::vector<int> _distances;        // For storing distance from the start node
    std::vector<int> _parentIndexes;    // For helping traverse back from target node
};
