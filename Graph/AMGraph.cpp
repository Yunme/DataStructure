//
// Created by zzqni on 2024/4/22.
//

#include <algorithm>
#include <queue>
#include <stack>
#include "AMGraph.h"

using namespace std;


/**
* 无向图 邻接矩阵中 用0 1表示
* 有向网 边是单向的
* 有向图 边是单向的，邻接矩阵中 用0 1表示
*/

void AMGraph_InitUDN(AMGraph &graph, int vexNum, int arcNum) {
    graph.vexNum = vexNum;
    graph.arcNum = arcNum;
    graph.weighted = true;
    for (int i = 0; i < vexNum; ++i) {
        for (int j = 0; j < vexNum; ++j) {
            graph.arcs[i][j] = MaxInt;
        }
    }
}

/**
 * 创建无向网
 */
void AMGraph_CreateUDN(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices,
                       const vector<WeightedArc> &arcs) {
    AMGraph_InitUDN(graph, vexNum, arcNum);
    for (int i = 0; i < vexNum; ++i) {
        graph.vexs[i] = vertices[i];
    }
    for (auto &arc: arcs) {
        int arc1Index = AMGraph_LocateVex(graph, arc.first.first);
        int arc2Index = AMGraph_LocateVex(graph, arc.first.second);
        if (arc1Index < 0 || arc2Index < 0) continue;
        graph.arcs[arc1Index][arc2Index] = graph.arcs[arc2Index][arc1Index] = arc.second;
    }
}

/**
 * 创建有向网
 */
void AMGraph_CreateDN(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices,
                      const vector<WeightedArc> &arcs) {
    AMGraph_InitUDN(graph, vexNum, arcNum);
    for (int i = 0; i < vexNum; ++i) {
        graph.vexs[i] = vertices[i];
    }
    for (auto &edge: arcs) {
        int arc1Index = AMGraph_LocateVex(graph, edge.first.first);
        int arc2Index = AMGraph_LocateVex(graph, edge.first.second);
        if (arc1Index < 0 || arc2Index < 0) continue;
        graph.arcs[arc1Index][arc2Index] = edge.second;
    }
}

/**
 * 创建有向无环图
 */
void AMGraph_CreateDAG(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices, const vector<Arc> &arcs) {
    AMGraph_InitUDN(graph, vexNum, arcNum);
    graph.weighted = false;
    for (int i = 0; i < vexNum; ++i) {
        graph.vexs[i] = vertices[i];
        for (int j = 0; j < vexNum; ++j) {
            graph.arcs[i][j] = NO_ARC;
        }
    }
    for (auto &edge: arcs) {
        int arc1Index = AMGraph_LocateVex(graph, edge.first);
        int arc2Index = AMGraph_LocateVex(graph, edge.second);
        if (arc1Index < 0 || arc2Index < 0) continue;
        graph.arcs[arc1Index][arc2Index] = ARC;
    }
}

void AMGraph_Print(const AMGraph &graph) {
    printf("AMGraph: vex(%d), arc(%d) \n", graph.vexNum, graph.arcNum);
    printf("%*c", 5, ' ');
    for (int i = 0; i < graph.vexNum; ++i) {
        printf("%4d ", i);
    }
    printf("\n%*c", 5, ' ');
    for (int i = 0; i < graph.vexNum; ++i) {
        VertexType vex = graph.vexs[i];
        printf("(%2s) ", vex.c_str());
    }
    printf("\n");
    for (int i = 0; i < graph.vexNum; ++i) {
        VertexType vex = graph.vexs[i];
        printf("(%2s)", vex.c_str());
        for (int j = 0; j < graph.vexNum; ++j) {
            if (graph.arcs[i][j] == MaxInt) {
                printf("%6s ", "\u221E");
            } else {
                printf("%4d ", graph.arcs[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool AMGraph_HasArc(const AMGraph &graph, int element) {
    if (graph.weighted) {
        return element != MaxInt;
    }
    return element == ARC;
}

int AMGraph_GetNoArc(const AMGraph &graph) {
    if (graph.weighted) {
        return MaxInt;
    } else {
        return NO_ARC;
    }
}

int AMGraph_LocateVex(const AMGraph &graph, const VertexType &data) {
    for (int i = 0; i < graph.vexNum; ++i) {
        if (graph.vexs[i] == data) {
            return i;
        }
    }
    return -1;
}

Status AMGraph_PutVex(AMGraph &graph, int pos, const VertexType &data) {
    if (pos < 0 || pos > graph.vexNum) {
        return ERROR;
    }
    graph.vexs[pos] = data;
    return OK;
}

/**
 * 返回顶点的第一个邻接顶点
 */
Status AMGraph_FirstAdjVex(const AMGraph &graph, int pos, VertexType &firstAdjVex) {
    if (pos < 0 || pos > graph.vexNum) {
        return ERROR;
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        ArcType weight = graph.arcs[pos][i];
        if (weight != MaxInt) {
            firstAdjVex = graph.vexs[i];
            return OK;
        }
    }
    return ERROR;
}

/**
 * adjVex 是 pos位置顶点 的邻接顶点，返回 r 相对于 adjVex 的下一个邻接顶点
 */
Status AMGraph_NextAdjVex(const AMGraph &graph, int pos, const VertexType &adjVex, VertexType &nextAdjVex) {
    if (pos < 0 || pos > graph.vexNum) {
        return ERROR;
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        ArcType weight = graph.arcs[pos][i];
        if (weight != MaxInt && graph.vexs[i] != adjVex) {
            nextAdjVex = graph.vexs[i];
            return OK;
        }
    }
    return ERROR;
}

/**
 * 新增顶点
 */
void AMGraph_InsertVex(AMGraph &graph, const VertexType &data) {
    if (graph.vexNum >= MAXSIZE) return;
    graph.vexs[graph.vexNum++] = data;
    for (int i = 0; i < graph.vexNum; ++i) {
        graph.arcs[graph.vexNum - 1][i] = AMGraph_GetNoArc(graph);
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        graph.arcs[i][graph.vexNum - 1] = AMGraph_GetNoArc(graph);
    }
}

/**
 * 删除顶点及相关的边
 * 需要移动元素，复杂度高
 */
void AMGraph_DeleteVex(AMGraph &graph, const VertexType &data) {
    int pos;
    if ((pos = AMGraph_LocateVex(graph, data)) >= 0) {
        for (int i = pos + 1; i < graph.vexNum; ++i) {
            graph.vexs[i - 1] = graph.vexs[i];
        }
        for (int i = pos; i < graph.vexNum - 1; ++i) {
            for (int j = 0; j < graph.vexNum; ++j) {
                if (i == pos && AMGraph_HasArc(graph, graph.arcs[pos][j]))
                    graph.arcNum--;
                graph.arcs[i][j] = graph.arcs[i + 1][j];
            }
        }
        for (int i = 0; i < graph.vexNum; ++i) {
            for (int j = pos; j < graph.vexNum - 1; ++j) {
                graph.arcs[i][j] = graph.arcs[i][j + 1];
            }
        }
        graph.vexNum--;
    }
}

/**
 * 删除顶点及相关的边
 * 直接把最后一个顶点移动到删除位置，复杂度降低。
 */
void AMGraph_DeleteVexOpt(AMGraph &graph, const VertexType &data) {
    int pos;
    if ((pos = AMGraph_LocateVex(graph, data)) >= 0) {
        graph.vexs[pos] = graph.vexs[graph.vexNum - 1];
        for (int i = 0; i < graph.vexNum; ++i) {
            if (AMGraph_HasArc(graph, graph.arcs[pos][i]))
                graph.arcNum--;
            graph.arcs[pos][i] = graph.arcs[graph.vexNum - 1][i];
            graph.arcs[i][pos] = graph.arcs[i][graph.vexNum - 1];
        }
        graph.vexNum--;
    }
}

/**
 * 添加一条边
 */
void AMGraph_InsertArc(AMGraph &graph, const WeightedArc &arc) {
    int pos1, pos2;
    if ((pos1 = AMGraph_LocateVex(graph, arc.first.first)) >= 0 &&
        (pos2 = AMGraph_LocateVex(graph, arc.first.second)) >= 0) {
        if (!AMGraph_HasArc(graph, graph.arcs[pos1][pos2])) {
            graph.arcNum++;
        }
        graph.arcs[pos1][pos2] = graph.arcs[pos2][pos1] = arc.second;
    }
}

/**
 * 删除一条边
 */
void AMGraph_DeleteArc(AMGraph &graph, const Arc &arc) {
    int pos1, pos2;
    if ((pos1 = AMGraph_LocateVex(graph, arc.first)) >= 0 &&
        (pos2 = AMGraph_LocateVex(graph, arc.first)) >= 0) {
        graph.arcs[pos1][pos2] = graph.arcs[pos2][pos1] = AMGraph_GetNoArc(graph);
        graph.arcNum--;
    }
}

/**
 * 深度优先遍历 递归版本
 */
void AMGraph_DepthFirstSearchRecursive(const AMGraph &graph, int visited[], int pos) {
    visited[pos] = 1;
    printf("%s ", graph.vexs[pos].c_str());
    for (int i = 0; i < graph.vexNum; ++i) {
        if (AMGraph_HasArc(graph, graph.arcs[pos][i]) && !visited[i]) {
            AMGraph_DepthFirstSearchRecursive(graph, visited, i);
        }
    }
}

/**
 * 深度优先遍历 非递归 栈实现
 */
void AMGraph_DepthFirstSearch(const AMGraph &graph, int pos) {
    vector<int> visited(graph.vexNum);
    stack<int> stack;
    stack.push(pos);
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        if (!visited[top]) {
            visited[top] = 1;
            printf("%s ", graph.vexs[top].c_str());
        }
        for (int i = 0; i < graph.vexNum; ++i) {
            if (!visited[i] && AMGraph_HasArc(graph, graph.arcs[top][i])) {
                stack.push(i);
            }
        }
    }
    printf("\n");
}

/**
 * 广度优先遍历 非递归 队列实现
 */
void AMGraph_BreadthFirstSearch(AMGraph &graph, int pos) {
    vector<int> visited(graph.vexNum);
    queue<int> q;
    q.push(pos);
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        if (!visited[front]) {
            visited[front] = 1;
            printf("%s ", graph.vexs[front].c_str());
        }
        for (int i = 0; i < graph.vexNum; ++i) {
            if (AMGraph_HasArc(graph, graph.arcs[front][i]) && !visited[i]) {
                q.push(i);
            }
        }
    }
    printf("\n");
}
