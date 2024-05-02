//
// Created by zzqni on 2024/4/24.
//

#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include "GraphAlgorithm.h"

/**
 * Prim 算法构造邻接矩阵表示的无向网的最小生成树，递归版本
 */
void PrimMST_AMGraph(const AMGraph &graph, vector<int> &foundVertexes, vector<int> &remainVertexes, AMGraph &mst) {
    if (foundVertexes.size() == graph.vexNum) {
        return;
    }
    int minWeight = MaxInt;
    int minVexI, minVexJ, minVexJPos;
    for (int i: foundVertexes) {
        for (int j = 0; j < remainVertexes.size(); ++j) {
            int jj = remainVertexes[j];
            if (graph.arcs[i][jj] < minWeight) {
                minWeight = graph.arcs[i][jj];
                minVexI = i;
                minVexJ = jj;
                minVexJPos = j;
            }
        }
    }
    mst.arcs[minVexI][minVexJ] = mst.arcs[minVexJ][minVexI] = minWeight;
    cout << "边  " << mst.vexs[minVexI] << "--->" << mst.vexs[minVexJ] << endl;

    mst.arcNum++;
    foundVertexes.push_back(minVexJ);
    remainVertexes.erase(remainVertexes.begin() + minVexJPos);
    PrimMST_AMGraph(graph, foundVertexes, remainVertexes, mst);
}

/**
 * Prim 算法构造邻接矩阵表示的无向网的最小生成树
 */
void PrimMST_AMGraph2(const AMGraph &graph) {
    vector<int> visited(graph.vexNum, 0);
    vector<int> parent(graph.vexNum, -1);
    vector<int> key(graph.vexNum, MaxInt);

    int currentVex = 0;
    for (int i = 0; i < graph.vexNum; ++i) {
        int minVex = MaxInt;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (!visited[j] && key[j] < minVex) {
                minVex = key[j];
                currentVex = j;
            }
        }
        visited[currentVex] = 1;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (!visited[j] && graph.arcs[currentVex][j] < key[j]) {
                key[j] = graph.arcs[currentVex][j];
                parent[j] = currentVex;
            }
        }
    }
    for (int i = 1; i < graph.vexNum; i++) {
        cout << "v" << i + 1 << "--->v" << parent[i] + 1 << endl;
    }
}


struct {
    VertexType adjVex;
    ArcType lowCost;
} closedge[MVNum];

int min(const AMGraph &graph) {
    int index = -1;
    int min = MaxInt;
    for (int i = 0; i < graph.vexNum; ++i) {
        if (min > closedge[i].lowCost && closedge[i].lowCost != 0) {
            min = closedge[i].lowCost;
            index = i;
        }
    }
    return index;
}

void GetMST_AMGraph(const AMGraph &graph, int startPos) {
    VertexType u0, v0;
    VertexType u = graph.vexs[startPos];
    for (int i = 0; i < graph.vexNum; ++i) {
        if (i != startPos) {
            closedge[i].adjVex = u;
            closedge[i].lowCost = graph.arcs[startPos][i];
        }
    }
    closedge[startPos].lowCost = 0;
    for (int i = 1; i < graph.vexNum; ++i) {
        int k = min(graph);
        u0 = closedge[k].adjVex;
        v0 = graph.vexs[k];
        cout << "边  " << u0 << "--->" << v0 << endl;
        closedge[k].lowCost = 0;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (graph.arcs[k][j] < closedge[j].lowCost) {
                closedge[j].adjVex = graph.vexs[k];
                closedge[j].lowCost = graph.arcs[k][j];
            }
        }
    }
}

bool compareWeightedArcs(const WeightedArc &a, const WeightedArc &b) {
    return a.second < b.second;
}

/**
 * 克鲁斯卡尔算法求邻接矩阵表示的无向网的最小生成树
 */
void KruskalMST_AMGraph(const AMGraph &graph) {
    // 将边按权值从小到大排序
    vector<WeightedArc> sortedArcs;
    // 连通分量 开始各个顶点各自一个分量
    vector<int> vexSet(graph.vexNum, 0);
    for (int i = 0; i < graph.vexNum; ++i) {
        vexSet[i] = i;
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = i; j < graph.vexNum; ++j) {
            if (graph.arcs[i][j] != MaxInt) {
                sortedArcs.emplace_back(pair(graph.vexs[i], graph.vexs[j]), graph.arcs[i][j]);
            }
        }
    }
    sort(sortedArcs.begin(), sortedArcs.end(), compareWeightedArcs);
    for (int i = 0; i < graph.arcNum; ++i) {
        int v1 = AMGraph_LocateVex(graph, sortedArcs[i].first.first);
        int v2 = AMGraph_LocateVex(graph, sortedArcs[i].first.second);
        int vs1 = vexSet[v1];
        int vs2 = vexSet[v2];
        if (vs1 != vs2) {
            cout << "边 " << sortedArcs[i].first.first << "--->" << sortedArcs[i].first.second << endl;
            for (int j = 0; j < graph.vexNum; ++j) {
                // 连通后，合并连通分量
                if (vexSet[j] == vs2) {
                    vexSet[j] = vs1;
                }
            }
        }
    }
}

/**
 * 克鲁斯卡尔算法求邻接表表示的无向网的最小生成树
 */
void KruskalMST_ALGraph(const ALGraph &graph) {
    vector<WeightedArc> sortedArcs;
    vector<int> vexSet(graph.vexNum, 0);
    for (int i = 0; i < graph.vexNum; ++i) {
        vexSet[i] = i;
    }
    for (int i = 0; i < graph.vexNum; i++) {
        ArcNode *arcNode = graph.vertices[i].firstArc;
        while (arcNode) {
            bool found = false;
            VertexType vex1 = graph.vertices[i].data;
            VertexType vex2 = graph.vertices[arcNode->adjvex].data;
            for (const WeightedArc &arc: sortedArcs) {
                if (arc.first.first == vex1 && arc.first.second == vex2 ||
                    arc.first.first == vex2 && arc.first.second == vex1) {
                    found = true;
                    break;
                }
            }
            if (!found)
                sortedArcs.emplace_back(pair(vex1, vex2), arcNode->weight);
            arcNode = arcNode->nextArc;
        }
    }
    sort(sortedArcs.begin(), sortedArcs.end(), compareWeightedArcs);
    for (int i = 0; i < graph.arcNum; ++i) {
        int v1 = ALGraph_LocateVex(graph, sortedArcs[i].first.first);
        int v2 = ALGraph_LocateVex(graph, sortedArcs[i].first.second);
        int vs1 = vexSet[v1];
        int vs2 = vexSet[v2];
        if (vs1 != vs2) {
            cout << "边 " << sortedArcs[i].first.first << "--->" << sortedArcs[i].first.second << endl;
            for (int j = 0; j < graph.vexNum; ++j) {
                // 连通后，合并连通分量
                if (vexSet[j] == vs2) {
                    vexSet[j] = vs1;
                }
            }
        }
    }
}

/**
 * Dijkstra 迪杰斯特拉算法求邻接矩阵表示的有向网的 单源点最短路径
 * @param shortestPath 返回各顶点的前驱 最短的弧
 * @param shortestWeight 存储源点到各顶点的最短路径
*/
void DijkstraShortestPath_AMGraph(const AMGraph &graph, int sourceVex, vector<int> &shortestPath,
                                  vector<ArcType> &shortestWeight) {
    if (sourceVex < 0 || sourceVex >= graph.vexNum) return;
    // 存储源点到各顶点的最短路径
    for (int i = 0; i < graph.vexNum; ++i) {
        shortestWeight[i] = MaxInt;
    }
    shortestWeight[sourceVex] = 0;
    vector<int> visited(graph.vexNum, 0);   // 已求得最短的顶点集合
    visited[sourceVex] = 1;
    // 初始化 weight 数组为源点到各顶点的路径
    for (int i = 0; i < graph.vexNum; ++i) {
        shortestWeight[i] = graph.arcs[sourceVex][i];
        if (shortestWeight[i] != MaxInt) shortestPath[i] = sourceVex;
        else shortestPath[i] = -1;
    }

    // 循环 n-1 次，找剩余顶点的最短路径
    for (int i = 1; i < graph.vexNum; ++i) {
        // 寻找当前已知路径中最短的
        int minWeight = MaxInt, minWeightPos = -1;
        for (int j = 0; j < shortestWeight.size(); ++j) {
            if (!visited[j] && shortestWeight[j] < minWeight) {
                minWeight = shortestWeight[j];
                minWeightPos = j;
            }
        }
        // 若当前剩余顶点没有最小距离，说明不可达，跳出
        if (minWeightPos < 0)
            break;
        visited[minWeightPos] = 1;
        // 更新路径
        for (int j = 0; j < graph.vexNum; ++j) {
            // 加入该顶点后 源点到其余顶点距离若变短，则更新
            if (!visited[j] && shortestWeight[minWeightPos] + graph.arcs[minWeightPos][j] < shortestWeight[j]) {
                shortestWeight[j] = shortestWeight[minWeightPos] + graph.arcs[minWeightPos][j];
                shortestPath[j] = minWeightPos;
            }
        }
    }
}

/**
 * Dijkstra 迪杰斯特拉算法求邻接表表示的有向网的 单源点最短路径
 * @param shortestPath 返回各顶点的前驱 最短的弧
 * @param shortestWeight 存储源点到各顶点的最短路径
*/
void DijkstraShortestPath_ALGraph(const ALGraph &graph, int sourceVex, vector<int> &shortestPath,
                                  vector<ArcType> &shortestWeight) {
    if (sourceVex < 0 || sourceVex >= graph.vexNum) return;
    // 存储源点到各顶点的最短路径
    for (int i = 0; i < graph.vexNum; ++i) {
        shortestWeight[i] = MaxInt;
    }
    shortestWeight[sourceVex] = 0;
    vector<int> visited(graph.vexNum, 0);   // 已求得最短的顶点集合
    visited[sourceVex] = 1;
    // 初始化 shortestWeight 数组为源点到各顶点的路径
    ArcNode *arc = graph.vertices[sourceVex].firstArc;
    while (arc) {
        shortestWeight[arc->adjvex] = arc->weight;
        if (arc->weight != MaxInt) shortestPath[arc->adjvex] = sourceVex;
        else shortestPath[arc->adjvex] = -1;
        arc = arc->nextArc;
    }
    // 循环 n-1 次，找剩余顶点的最短路径
    for (int i = 1; i < graph.vexNum; ++i) {
        // 寻找当前已知路径中最短的
        int minWeight = MaxInt, minWeightPos = -1;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (!visited[j] && shortestWeight[j] < minWeight) {
                minWeight = shortestWeight[j];
                minWeightPos = j;
            }
        }
        // 若当前剩余顶点没有最小距离，说明不可达，跳出
        if (minWeightPos < 0) break;
        visited[minWeightPos] = 1;
        arc = graph.vertices[minWeightPos].firstArc;
        while (arc) {
            // 加入该顶点后 源点到其余顶点距离若变短，则更新
            if (!visited[arc->adjvex] && arc->weight + shortestWeight[minWeightPos] < shortestWeight[arc->adjvex]) {
                shortestWeight[arc->adjvex] = arc->weight + shortestWeight[minWeightPos];
                shortestPath[arc->adjvex] = minWeightPos;
            }
            arc = arc->nextArc;
        }
    }

}

/**
 * Floyd 弗洛伊德算法求邻接矩阵表示的有向网中各个顶点间的最短路径
 */
void FloydShortedPath_AMGraph(AMGraph &graph, int **matrix, int **path) {
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = graph.arcs[i][j];
            if (matrix[i][j] != MaxInt) path[i][j] = i;
            else path[i][j] = -1;
        }
    }

    for (int k = 0; k < graph.vexNum; ++k) {
        for (int i = 0; i < graph.vexNum; ++i) {
            for (int j = 0; j < graph.vexNum; ++j) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

/**
 * Floyd 弗洛伊德算法求邻接表表示的有向网中各个顶点间的最短路径
 */
void FloydShortedPath_ALGraph(ALGraph &graph, int **matrix) {
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = MaxInt;
        }
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        ArcNode *arcNode = graph.vertices[i].firstArc;
        while (arcNode) {
            matrix[i][arcNode->adjvex] = arcNode->weight;
            arcNode = arcNode->nextArc;
        }
    }

    for (int k = 0; k < graph.vexNum; ++k) {
        for (int i = 0; i < graph.vexNum; ++i) {
            for (int j = 0; j < graph.vexNum; ++j) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
}

/**
 * 拓扑排序判断邻接矩阵表示的有向图中是否有环
 * @param sortResult 返回排序顺序，顶点全部输出：无环，否则：有环
 * 简单粗暴版 O(n^3)
 */
void TopologicalSort_AMGraph(AMGraph graph, vector<int> &sortResult) {
    vector<int> visited(graph.vexNum, 0);
    for (int i = 0; i < graph.vexNum; ++i) {
        int noPrePos = -1;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (visited[j]) continue;
            int noPre = true;
            for (int k = 0; k < graph.vexNum; ++k) {
                if (AMGraph_HasArc(graph, graph.arcs[k][j])) {
                    noPre = false;
                    break;
                }
            }
            if (noPre) {
                noPrePos = j;
                break;
            }
        }

        if (noPrePos >= 0) {
            visited[noPrePos] = 1;
            sortResult.push_back(noPrePos);
            for (int j = 0; j < graph.vexNum; ++j) {
                graph.arcs[noPrePos][j] = AMGraph_GetNoArc(graph);
            }
        }
    }
}

/**
 * 拓扑排序判断邻接矩阵表示的有向图中是否有环
 * @param sortResult 返回排序顺序，顶点全部输出：无环，否则：有环
 * 优化版 O(n^2)
 * 使用队列得到正序的拓扑序列， 使用栈得到逆序的拓扑序列。
 */
void TopologicalSort_AMGraphOpt(const AMGraph &graph, vector<int> &sortResult) {
    vector<int> inDegrees(graph.vexNum);
    // 存储事件AOE最早发生时间
    for (int i = 0; i < graph.vexNum; ++i) {
        int count = 0;
        for (int j = 0; j < graph.vexNum; ++j) {
            if (AMGraph_HasArc(graph, graph.arcs[j][i])) {
                count++;
            }
        }
        inDegrees[i] = count;
    }
    queue<int> queue;
    for (int i = 0; i < inDegrees.size(); ++i) {
        if (inDegrees[i] == 0) queue.push(i);
    }
    while (!queue.empty()) {
        int top = queue.front();
        queue.pop();
        sortResult.push_back(top);
        // 该顶点已遍历移除，所有后继顶点的入度数减一。
        for (int i = 0; i < graph.vexNum; ++i) {
            if (AMGraph_HasArc(graph, graph.arcs[top][i])) {
                if (--inDegrees[i] == 0)
                    queue.push(i);
            }
        }
    }
}

/**
 * 拓扑排序判断邻接表表示的有向图中是否有环
 * @param sortResult 返回排序顺序，顶点全部输出：无环，否则：有环
 */
void TopologicalSort_ALGraph(const ALGraph &graph, vector<int> &sortResult) {
    vector<int> inDegrees(graph.vexNum);
    for (int i = 0; i < graph.vexNum; ++i) {
        ArcNode *arcNode = graph.converseVertices[i].firstArc;
        int count = 0;
        while (arcNode) {
            count++;
            arcNode = arcNode->nextArc;
        }
        inDegrees[i] = count;
    }
    queue<int> queue;
    for (int i = 0; i < inDegrees.size(); ++i) {
        if (inDegrees[i] == 0) queue.push(i);
    }
    while (!queue.empty()) {
        int top = queue.front();
        queue.pop();
        sortResult.push_back(top);
        // 该顶点已遍历移除，所有后继顶点的入度数减一。
        ArcNode *arcNode = graph.vertices[top].firstArc;
        while (arcNode) {
            if (--inDegrees[arcNode->adjvex] == 0)
                queue.push(arcNode->adjvex);
            arcNode = arcNode->nextArc;
        }
    }
}

/**
 * 关键路径 邻接矩阵表示的有向图
 */
void CriticalPath_AMGraph(const AMGraph &graph, vector<pair<int, int>> &criticalPaths) {
    vector<int> vertexEarliest(graph.vexNum);
    vector<int> vertexLatest(graph.vexNum);
    vector<int> topologicalSort;
    TopologicalSort_AMGraph(graph, topologicalSort);
    if (topologicalSort.size() != graph.vexNum) return;

    // 根据拓扑排序的顺序求事件的最早发生时间
    for (int vex: topologicalSort) {
        // 后继事件的最早发生时间 = max(前驱事件的最早发生时间 + 活动时间（边的权重）)
        for (int j = 0; j < graph.vexNum; ++j) {
            if (AMGraph_HasArc(graph, graph.arcs[vex][j])) {
                vertexEarliest[j] = max(vertexEarliest[vex] + graph.arcs[vex][j], vertexEarliest[j]);
            }
        }
    }

    for (int i = 0; i < graph.vexNum; ++i) {
        vertexLatest[i] = vertexEarliest[graph.vexNum - 1];
    }
    for (int i = topologicalSort.size() - 1; i >= 0; --i) {
        int vex = topologicalSort[i];
        // 前驱事件的最晚发生事件 = min(后继事件的最晚发生事件 - 活动事件（边的权重）)
        for (int j = 0; j < graph.vexNum; ++j) {
            if (AMGraph_HasArc(graph, graph.arcs[vex][j])) {
                vertexLatest[vex] = min(vertexLatest[j] - graph.arcs[vex][j], vertexLatest[vex]);
            }
        }
    }

    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            if (AMGraph_HasArc(graph, graph.arcs[i][j])) {
                int ei = vertexEarliest[i];
                int li = vertexLatest[j] - graph.arcs[i][j];
                if (ei == li) {
                    criticalPaths.emplace_back(i, j);
                }
            }
        }
    }
}

/**
 * 关键路径 邻接表表示的有向图
 */
void CriticalPath_ALGraph(const ALGraph &graph, vector<pair<int, int>> &criticalPaths) {
    vector<int> vertexEarliest(graph.vexNum);
    vector<int> vertexLatest(graph.vexNum);
    vector<int> topologicalSort;
    TopologicalSort_ALGraph(graph, topologicalSort);
    if (topologicalSort.size() != graph.vexNum) return;

    // 根据拓扑排序的顺序求事件的最早发生时间
    for (int vex: topologicalSort) {
        // 后继事件的最早发生时间 = max(前驱事件的最早发生时间 + 活动时间（边的权重）)
        ArcNode *arcNode = graph.vertices[vex].firstArc;
        while (arcNode) {
            vertexEarliest[arcNode->adjvex] = max(vertexEarliest[vex] + arcNode->weight,
                                                  vertexEarliest[arcNode->adjvex]);
            arcNode = arcNode->nextArc;
        }
    }

    // 根据逆拓扑排序顺序
    for (int i = 0; i < graph.vexNum; ++i) {
        vertexLatest[i] = vertexEarliest[graph.vexNum - 1];
    }
    for (int i = topologicalSort.size() - 1; i >= 0; --i) {
        int vex = topologicalSort[i];
        // 前驱事件的最晚发生事件 = min(后继事件的最晚发生事件 - 活动事件（边的权重）)
        ArcNode *arcNode = graph.vertices[vex].firstArc;
        while (arcNode) {
            vertexLatest[vex] = min(vertexLatest[arcNode->adjvex] - arcNode->weight, vertexLatest[vex]);
            arcNode = arcNode->nextArc;
        }
    }

    for (int i = 0; i < graph.vexNum; ++i) {
        ArcNode *arcNode = graph.vertices[i].firstArc;
        while (arcNode) {
            // e(i) = ve(j) 活动最早开始时间 = 事件最早开始时间
            ArcType e = vertexEarliest[i];
            // a(i)=<vj, vk> 活动最晚开始时间 = 事件vk 的最晚发生时间 - 活动ai的持续时间w(j,k)
            ArcType l = vertexLatest[arcNode->adjvex] - arcNode->weight;
            if (e == l) {
                criticalPaths.emplace_back(i, arcNode->adjvex);
            }
            arcNode = arcNode->nextArc;
        }
    }
}