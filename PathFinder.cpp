#include "PathFinder.h"
#include <cmath>

bool operator>(const Node& left, const Node& right)
{
    return left.weight > right.weight;
}

PathFinder::PathFinder(std::pair<int, int> start, std::pair<int, int> target, const std::vector<int>& map, std::pair<int, int> mapDimensions)
    : _start(start)
    , _target(target)
    , _map(map)
    , _mapDimensions(mapDimensions)
{
    const int nodesAmount = _mapDimensions.first * _mapDimensions.second;
    _distances.assign(nodesAmount, -1);
    _parentIndexes.assign(nodesAmount, -1);
}

bool PathFinder::FindPath(std::vector<int>& outPath)
{
    const int startIndex = FindIndex(_start.first, _start.second);
    const int targetIndex = FindIndex(_target.first, _target.second);

    // push start node
    _nodesQueue.push(Node(startIndex, _start.first, _start.second, -1, 0, 0));

    // traverse through the nodes to calculate the distance
    while (!_nodesQueue.empty()) {
        Node node = _nodesQueue.top();
        _nodesQueue.pop();

        if (node.index == targetIndex) {
            _distances[node.index] = node.distanceFromStart;
            _parentIndexes[node.index] = node.parentIndex;
            break;
        }

        CalculateData(node);
    }

    const int targetDistance = _distances[targetIndex];
    if (targetDistance != -1) {
        int i = 1;
        int currentIndex = targetIndex;
        outPath.resize(targetDistance);
        while (currentIndex != startIndex && i <= targetDistance) {
            outPath[targetDistance - i] = currentIndex;
            currentIndex = _parentIndexes[currentIndex];
            ++i;
        }
        return true;
    }

    return false;
}

void PathFinder::CalculateData(const Node& node)
{
    // return if we've already calculated data for this node
    if (_distances[node.index] != -1) {
        return;
    }

    _distances[node.index] = node.distanceFromStart;
    _parentIndexes[node.index] = node.parentIndex;

    // check the left node
    if (0 <= node.x - 1) {
        AddNodeToQueue(node, node.x - 1, node.y);
    }

    // check the right node
    if (node.x + 1 < _mapDimensions.first) {
        AddNodeToQueue(node, node.x + 1, node.y);
    }

    // check the top node
    if (0 <= node.y - 1) {
        AddNodeToQueue(node, node.x, node.y - 1);
    }

    // check the bottom node
    if (node.y + 1 < _mapDimensions.second) {
        AddNodeToQueue(node, node.x, node.y + 1);
    }
}

void PathFinder::AddNodeToQueue(const Node& parentNode, const int x, const int y)
{
    const int index = FindIndex(x, y);
    if (_distances[index] == -1 && _map[index] == 1) {
        const int distanceFromStart = parentNode.distanceFromStart + 1;
        const int weight = distanceFromStart + CalculateDistance(x, y);
        _nodesQueue.push(Node(index, x, y, parentNode.index, distanceFromStart, weight));
    }
}

int PathFinder::FindIndex(const int x, const int y)
{
    return y * _mapDimensions.first + x;
}

int PathFinder::CalculateDistance(const int x, const int y)
{
    return std::abs(_target.first - x) + std::abs(_target.second - y);
}
