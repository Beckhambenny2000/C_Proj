#include "../inc/Main.h"
#include <climits>  
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

extern unordered_map<char, int> costGeneric;
extern set<char> preferredTerrains;
extern string VehicleType;

struct Node {
    int r, c;
    int cost;
    bool hasPreferred;
    vector<pair<int, int>> path;

    bool operator>(const Node& other) const {
        if (hasPreferred != other.hasPreferred) {
            return !hasPreferred;
        }
        return cost > other.cost;
    }
};


struct PathResult {
    vector<pair<int, int>> path;
    int totalEnergy;
};

// Shotest Path
vector<pair<int, int>> findShortestPathWithWT(
    const vector<vector<char>>& terrainMap,
    pair<int, int> start,
    pair<int, int> end
) {
    int rows = terrainMap.size();
    int cols = terrainMap[0].size();

    vector<vector<vector<int>>> visited(rows, vector<vector<int>>(cols, vector<int>(2, numeric_limits<int>::max())));
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    char startChar = terrainMap[start.first][start.second];
    bool isPref = preferredTerrains.count(startChar);

    pq.push({start.first, start.second, 0, isPref, {start}});
    visited[start.first][start.second][isPref] = 0;

    vector<pair<int, int>> fallbackPath;
    int fallbackCost = numeric_limits<int>::max();

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (cur.r == end.first && cur.c == end.second) {
            if (cur.hasPreferred) {
                return cur.path;
            } else if (cur.cost < fallbackCost) {
                fallbackCost = cur.cost;
                fallbackPath = cur.path;
            }
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

            char nextChar = terrainMap[nr][nc];
            if (nextChar == '#') continue;

            int moveCost = costGeneric.count(nextChar) ? costGeneric[nextChar] : 1000;
            int newCost = cur.cost + moveCost;
            bool newPref = cur.hasPreferred || preferredTerrains.count(nextChar);

            if (newCost < visited[nr][nc][newPref]) {
                visited[nr][nc][newPref] = newCost;
                vector<pair<int, int>> newPath = cur.path;
                newPath.push_back({nr, nc});
                pq.push({nr, nc, newCost, newPref, newPath});
            }
        }
    }

    return fallbackPath;
}


// least energy path
PathResult findLeastEnergyPath(
    const vector<vector<char>>& terrainMap,
    pair<int, int> start,
    pair<int, int> end
) {
    int rows = terrainMap.size();
    int cols = terrainMap[0].size();

    // Dijkstra algorithm (local lambda returning path only)
    auto dijkstra = [&](pair<int, int> src, pair<int, int> dst) -> vector<pair<int, int>> {
        vector<vector<int>> energy(rows, vector<int>(cols, numeric_limits<int>::max()));
        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
        using Node = pair<int, pair<int, int>>; // {totalEnergy, {r, c}}
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        energy[src.first][src.second] = 0;
        pq.push({0, src});

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [currEnergy, pos] = pq.top(); pq.pop();
            int r = pos.first, c = pos.second;

            if (pos == dst) break;

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

                char ch = terrainMap[nr][nc];
                if (ch == '#') continue;

                //int cost = costGeneric.count(ch) ? costGeneric[ch] : 1000;
                int baseCost = costGeneric.count(ch) ? costGeneric[ch] : 1000;

				if (VehicleType == VehicleType && isPreferred(ch)) {
    			baseCost = baseCost / 2;  // apply discount during pathfinding
				}
				
                int newEnergy = currEnergy + baseCost;

                if (newEnergy < energy[nr][nc]) {
                    energy[nr][nc] = newEnergy;
                    parent[nr][nc] = {r, c};
                    pq.push({newEnergy, {nr, nc}});
                }
            }
        }

        // Reconstruct path
        vector<pair<int, int>> path;
        pair<int, int> cur = dst;
        while (cur != make_pair(-1, -1)) {
            path.push_back(cur);
            cur = parent[cur.first][cur.second];
        }
        reverse(path.begin(), path.end());
        if (!path.empty() && path[0] == src) return path;
        return {};
    };

    // Find all preferred terrain tiles
    vector<pair<int, int>> preferredPoints;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (isPreferred(terrainMap[r][c])) {
                preferredPoints.emplace_back(r, c);
            }
        }
    }

    // Try going through preferred terrain if available
    vector<pair<int, int>> bestPath;
    int minTotalEnergy = INT_MAX;

    for (auto& mid : preferredPoints) {
        auto path1 = dijkstra(start, mid);
        auto path2 = dijkstra(mid, end);
        if (path1.empty() || path2.empty()) continue;

        vector<pair<int, int>> fullPath = path1;
        fullPath.insert(fullPath.end(), path2.begin() + 1, path2.end()); // avoid mid duplication

        int energySum = 0;
        for (size_t i = 1; i < fullPath.size(); ++i) {
            char ch = terrainMap[fullPath[i].first][fullPath[i].second];
            energySum += costGeneric.count(ch) ? costGeneric[ch] : 1000;
        }

        if (energySum < minTotalEnergy) {
            minTotalEnergy = energySum;
            bestPath = fullPath;
        }
    }

    // Fallback: direct path if no preferred terrain path found
    if (!bestPath.empty()) return {bestPath, minTotalEnergy};

    auto fallbackPath = dijkstra(start, end);
    int fallbackEnergy = 0;
    for (size_t i = 1; i < fallbackPath.size(); ++i) {
        char ch = terrainMap[fallbackPath[i].first][fallbackPath[i].second];
        fallbackEnergy += costGeneric.count(ch) ? costGeneric[ch] : 1000;
    }

    return {fallbackPath, fallbackEnergy};
}

