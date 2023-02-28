#include <iostream>
#include "PathFinder.h"

bool FindPath(std::pair<int, int> Start,
            std::pair<int, int> Target,
            const std::vector<int>& Map,
            std::pair<int, int> MapDimensions,
            std::vector<int>& OutPath)
{
    if (Map.empty()) {
        return false;
    }

    // if Start and Target are at the same position the function should return true
    if (Start.first == Target.first && Start.second == Target.second) {
        return true;
    }

    PathFinder pf(Start, Target, Map, MapDimensions);

    return pf.FindPath(OutPath);
}

int main()
{
    std::cout << "Problem A" << std::endl;

    std::vector<int> OutPath;
    //std::vector<int> Map = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
    //if (FindPath({ 2, 0 }, { 0, 2 }, Map, { 3, 3 }, OutPath)) {
    // std::vector<int> Map = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
    //if (FindPath({ 0, 0 }, { 1, 2 }, Map, { 4, 3 }, OutPath)) {

    std::vector<int> Map = { 1, 1 };
    if (FindPath({ 0, 0 }, { 0, 0 }, Map, { 1, 1 }, OutPath)) {
        std::cout << "Path distance: " << OutPath.size() << std::endl;

        for (int i = 0; i < static_cast<int>(OutPath.size()); ++i) {
            std::cout << OutPath[i] << " ";
        }
    }
    else {
        std::cout << "Path wasn't found" << std::endl;
    }

    std::cout << std::endl;
}
