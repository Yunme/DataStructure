//
// Created by zzqni on 2024/4/26.
//

#include <stack>
#include <queue>
#include "GraphExercise.h"

using namespace std;

/**
 * 求图中距离顶点v最短路径长度最大的顶点
 * 1. 根据 Dijkstra 算法求单源点到最短路径
 * 2. 找出最短路径列表中最长的
*/
int GraphExercise_MaxShortestPath(const ALGraph &graph, int pos) {
    vector<int> shortestPath(graph.vexNum);
    vector<ArcType> shortestWeight(graph.vexNum, MaxInt);
    DijkstraShortestPath_ALGraph(graph, pos, shortestPath, shortestWeight);

    int maxWeight = 0;
    int maxVex = -1;
    for (int i = 0; i < graph.vexNum; ++i) {
        if (shortestWeight[i] != MaxInt && shortestWeight[i] > maxWeight) {
            maxWeight = shortestWeight[i];
            maxVex = i;
        }
    }
    return maxVex;
}

/**
 * 判断有向图中是否存在顶点 i 到 j 的路径
 * 从 i 开始遍历，遍历到 j 说明可达，否则不可达。
*/
bool GraphExercise_CanVertexReach(const ALGraph &graph, int aPos, int bPos) {
    if (aPos == bPos) return true;
    vector<int> searchList;
    ALGraph_DepthFirstSearch(graph, aPos, &searchList);
    for (int i: searchList) {
        if (i == bPos) {
            return true;
        }
    }
    return false;
}

/**
 * 判断无向图中任意两个顶点间是否存在一条长度为 k 的简单路径
 * 路径长度：边的数量
*/
bool GraphExercise_PathLength(const ALGraph &graph, int aPos, int bPos, int pathLength) {
    if (aPos == bPos && pathLength == 0) return true;
    vector<int> visited(graph.vexNum);
    vector<int> pathLen(graph.vexNum, -1);
    queue<int> q;

    q.push(aPos);
    pathLen[aPos] = 0;

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        if (top == bPos && pathLen[top] == pathLength) return true;
        visited[top] = 1;

        ArcNode *arcNode = graph.vertices[top].firstArc;
        while (arcNode) {
            if (!visited[arcNode->adjvex]) {
                q.push(arcNode->adjvex);
                pathLen[arcNode->adjvex] = pathLen[top] + 1;
            }
            arcNode = arcNode->nextArc;
        }
    }
    return false;
}