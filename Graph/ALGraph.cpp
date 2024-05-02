//
// Created by zzqni on 2024/4/22.
//

#include <queue>
#include <stack>
#include <optional>
#include "ALGraph.h"

void ALGraph_Init(ALGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices) {
    graph.vexNum = vexNum;
    graph.arcNum = arcNum;

    for (int i = 0; i < vexNum; ++i) {
        graph.vertices[i].data = vertices[i];
        graph.vertices[i].firstArc = nullptr;
        graph.converseVertices[i].data = vertices[i];
        graph.converseVertices[i].firstArc = nullptr;
    }
}

/**
 * 创建无向图
 */
void ALGraph_CreateUDG(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                       vector<Arc> edges) {
    ALGraph_Init(alGraph, vexNum, arcNum, vertices);
    for (int i = 0; i < arcNum; ++i) {
        pair edge = edges[i];
        int arc1Index = ALGraph_LocateVex(alGraph, edge.first);
        int arc2Index = ALGraph_LocateVex(alGraph, edge.second);
        if (arc1Index < 0 || arc2Index < 0) continue;

        auto *arcNode1 = new ArcNode;
        arcNode1->adjvex = arc2Index;
        arcNode1->nextArc = alGraph.vertices[arc1Index].firstArc;
        alGraph.vertices[arc1Index].firstArc = arcNode1;

        auto *arcNode2 = new ArcNode;
        arcNode2->adjvex = arc1Index;
        arcNode2->nextArc = alGraph.vertices[arc2Index].firstArc;
        alGraph.vertices[arc2Index].firstArc = arcNode2;
    }
}

/**
 * 创建无向网
 */
void ALGraph_CreateUDN(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                       vector<WeightedArc> edges) {
    ALGraph_Init(alGraph, vexNum, arcNum, vertices);
    for (int i = 0; i < arcNum; ++i) {
        pair edge = edges[i];
        int arc1Index = ALGraph_LocateVex(alGraph, edge.first.first);
        int arc2Index = ALGraph_LocateVex(alGraph, edge.first.second);
        if (arc1Index < 0 || arc2Index < 0) continue;

        auto *arcNode1 = new ArcNode;
        arcNode1->adjvex = arc2Index;
        arcNode1->nextArc = alGraph.vertices[arc1Index].firstArc;
        arcNode1->weight = edge.second;
        alGraph.vertices[arc1Index].firstArc = arcNode1;

        auto *arcNode2 = new ArcNode;
        arcNode2->adjvex = arc1Index;
        arcNode2->weight = edge.second;
        arcNode2->nextArc = alGraph.vertices[arc2Index].firstArc;
        alGraph.vertices[arc2Index].firstArc = arcNode2;
    }
}

/**
 * 创建有向网
 */
void ALGraph_CreateDN(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                      vector<WeightedArc> edges) {
    ALGraph_Init(alGraph, vexNum, arcNum, vertices);
    for (int i = 0; i < arcNum; ++i) {
        pair edge = edges[i];
        int arc1Index = ALGraph_LocateVex(alGraph, edge.first.first);
        int arc2Index = ALGraph_LocateVex(alGraph, edge.first.second);
        if (arc1Index < 0 || arc2Index < 0) continue;

        auto *arcNode1 = new ArcNode;
        arcNode1->adjvex = arc2Index;
        arcNode1->nextArc = alGraph.vertices[arc1Index].firstArc;
        arcNode1->weight = edge.second;
        alGraph.vertices[arc1Index].firstArc = arcNode1;
    }
}

void ALGraph_CreateDG(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                      vector<Arc> edges) {
    ALGraph_Init(alGraph, vexNum, arcNum, vertices);
    for (int i = 0; i < arcNum; ++i) {
        pair edge = edges[i];
        int arc1Index = ALGraph_LocateVex(alGraph, edge.first);
        int arc2Index = ALGraph_LocateVex(alGraph, edge.second);
        if (arc1Index < 0 || arc2Index < 0) continue;

        auto *arcNode1 = new ArcNode;
        arcNode1->adjvex = arc2Index;
        arcNode1->nextArc = alGraph.vertices[arc1Index].firstArc;
        alGraph.vertices[arc1Index].firstArc = arcNode1;

        auto *arcNode2 = new ArcNode;
        arcNode2->adjvex = arc1Index;
        arcNode2->nextArc = alGraph.converseVertices[arc2Index].firstArc;
        alGraph.converseVertices[arc2Index].firstArc = arcNode2;
    }
}

void ALGraph_Print(const ALGraph &graph) {
    printf("ALGraph: vex(%d), arc(%d) \n", graph.vexNum, graph.arcNum);
    for (int i = 0; i < graph.vexNum; ++i) {
        ArcNode *p;
        // 邻接表
        VNode node = graph.vertices[i];
        printf("%d:(%s)", i, node.data.c_str());
        p = node.firstArc;
        while (p) {
            printf("->%d", p->adjvex);
            p = p->nextArc;
        }
        p = graph.converseVertices[i].firstArc;
        if (p) {
            printf("\n\t");
            // 逆邻接表
            while (p) {
                printf("<-(%d)", p->adjvex);
                p = p->nextArc;
            }
        }
        printf("\n");
    }
}

int ALGraph_LocateVex(const ALGraph &graph, const VertexType &data) {
    for (int i = 0; i < graph.vexNum; ++i) {
        if (graph.vertices[i].data == data) {
            return i;
        }
    }
    return -1;
}

Status ALGraph_FindVex(const ALGraph &graph, const VNode &vNode) {
    for (int i = 0; i < graph.vexNum; ++i) {
        if (&graph.vertices[i] == &vNode) {
            return OK;
        }
    }
    return ERROR;
}

VNode *ALGraph_FindVNode(ALGraph &graph, const VertexType &data) {
    for (int i = 0; i < graph.vexNum; ++i) {
        if (graph.vertices[i].data == data) {
            return &graph.vertices[i];;
        }
    }
    return nullptr;
}

Status ALGraph_GetVex(const ALGraph &graph, const VNode &vNode, VertexType &data) {
    if (ALGraph_FindVex(graph, vNode)) {
        data = vNode.data;
        return OK;
    }
    return ERROR;
}

Status ALGraph_PutVex(const ALGraph &graph, VNode &vNode, const VertexType &data) {
    if (ALGraph_FindVex(graph, vNode)) {
        vNode.data = data;
        return OK;
    }
    return ERROR;
}

/**
 * 返回顶点的第一个邻接顶点
 */
Status ALGraph_FirstAdjVex(const ALGraph &graph, const VNode &vNode, VNode &firstVNode) {
    if (ALGraph_FindVex(graph, vNode)) {
        ArcNode *p = vNode.firstArc;
        if (p && p->adjvex < graph.vexNum) {
            firstVNode = graph.vertices[p->adjvex];
            return OK;
        }
    }
    return ERROR;
}

/**
 * adjVex 是 vNode 的邻接顶点，返回 vNode 相对于 adjVex 的下一个邻接顶点
 */
Status ALGraph_NextAdjVex(const ALGraph &graph, const VNode &vNode, const VNode &adjVex, VNode &nextAdjVex) {
    int index;
    if (ALGraph_FindVex(graph, vNode) && (index = ALGraph_LocateVex(graph, adjVex.data)) >= 0) {
        ArcNode *p = vNode.firstArc;
        while (p) {
            if (p->adjvex == index && p->nextArc) {
                nextAdjVex = graph.vertices[p->nextArc->adjvex];
                return OK;
            }
            p = p->nextArc;
        }
    }
    return ERROR;
}

/**
 * 新增顶点
 */
void ALGraph_InsertVex(ALGraph &graph, const VertexType &data) {
    if (graph.vexNum >= MVNum) return;
    VNode &vNode = graph.vertices[graph.vexNum];
    vNode.data = data;
    vNode.firstArc = nullptr;

    VNode &vNode2 = graph.converseVertices[graph.vexNum];
    vNode2.data = data;
    vNode2.firstArc = nullptr;
    ++graph.vexNum;
}

/**
 * 删除顶点及相关的边
 */
void ALGraph_DeleteVex(ALGraph &graph, const VertexType &data) {
    int index = ALGraph_LocateVex(graph, data);
    if (index >= 0) {
        // 先删除相关的边
        for (int i = 0; i < graph.vexNum; ++i) {
            VNode &node = graph.vertices[i];
            ArcNode *prev = nullptr;
            ArcNode *current = node.firstArc;
            while (current) {
                if (current->adjvex == index) {
                    if (prev) {
                        prev->nextArc = current->nextArc;
                    } else {
                        node.firstArc = current->nextArc;
                    }
                    ArcNode *temp = current;
                    current = current->nextArc;
                    delete temp;
                    graph.arcNum--;
                } else if (current->adjvex > index) {
                    // 更新其他边中的索引
                    current->adjvex--;
                    prev = current;
                    current = current->nextArc;
                } else {
                    prev = current;
                    current = current->nextArc;
                }
            }
        }
        // 删除顶点
        delete graph.vertices[index].firstArc;
        for (int i = index + 1; i < graph.vexNum; ++i) {
            graph.vertices[i - 1] = graph.vertices[i];
        }
        graph.vexNum--;
    }
}

/**
 * 添加一条边
 */
void ALGraph_InsertArc(ALGraph &graph, const Arc &arc) {
    int pos1, pos2;
    if ((pos1 = ALGraph_LocateVex(graph, arc.first)) >= 0 && (pos2 = ALGraph_LocateVex(graph, arc.second)) >= 0) {
        VNode &vNode1 = graph.vertices[pos1];

        ArcNode *current = vNode1.firstArc;
        auto newArc = new ArcNode;
        newArc->adjvex = pos2;
        newArc->nextArc = nullptr;
        if (!current) {
            vNode1.firstArc = newArc;
        } else if (current->adjvex != pos2) {
            while (current->nextArc) {
                if (current->nextArc->adjvex == pos2) break;
                current = current->nextArc;
            }
            current->nextArc = newArc;
        }

        VNode &vNode2 = graph.vertices[pos2];
        current = vNode2.firstArc;
        newArc = new ArcNode;
        newArc->adjvex = pos1;
        newArc->nextArc = nullptr;
        if (!current) {
            vNode2.firstArc = newArc;
        } else if (current->adjvex != pos1) {
            while (current->nextArc) {
                if (current->nextArc->adjvex == pos1) break;
                current = current->nextArc;
            }
            current->nextArc = newArc;
        }
        graph.arcNum++;
    }
}

/**
 * 删除一条边
 */
void ALGraph_DeleteArc(ALGraph &graph, const Arc &arc) {
    int pos1, pos2;
    if ((pos1 = ALGraph_LocateVex(graph, arc.first)) >= 0 && (pos2 = ALGraph_LocateVex(graph, arc.second)) >= 0) {
        VNode &vNode1 = graph.vertices[pos1];
        ArcNode *current = vNode1.firstArc;
        ArcNode *prev = nullptr;
        while (current && current->adjvex != pos2) {
            prev = current;
            current = current->nextArc;
        }
        if (current) {
            if (!prev) {
                vNode1.firstArc = current->nextArc;
            } else {
                prev->nextArc = current->nextArc;
            }
            delete current;
        }

        VNode &vNode2 = graph.vertices[pos2];
        current = vNode2.firstArc;
        prev = nullptr;
        while (current && current->adjvex != pos1) {
            prev = current;
            current = current->nextArc;
        }
        if (current) {
            if (!prev) {
                vNode2.firstArc = current->nextArc;
            } else {
                prev->nextArc = current->nextArc;
            }
            delete current;
        }
        graph.arcNum--;
    }
}

/**
 * 深度优先遍历 递归版本
 */
void ALGraph_DepthFirstSearchRecursive(const ALGraph &graph, int visited[], int pos) {
    printf("%s ", graph.vertices[pos].data.c_str());
    visited[pos] = 1;
    ArcNode *arcNode = graph.vertices[pos].firstArc;
    while (arcNode) {
        if (!visited[arcNode->adjvex]) {
            ALGraph_DepthFirstSearchRecursive(graph, visited, arcNode->adjvex);
        }
        arcNode = arcNode->nextArc;
    }
}

/**
 * 深度优先遍历 非递归 栈实现
 */
void ALGraph_DepthFirstSearch(const ALGraph &graph, int pos, vector<int> *result) {
    vector<int> visited(graph.vexNum);
    stack<int> stack;
    stack.push(pos);
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        if (!visited[top]) {
            visited[top] = 1;
            result->push_back(top);
            printf("%s ", graph.vertices[top].data.c_str());
        }
        ArcNode *arcNode = graph.vertices[top].firstArc;
        while (arcNode) {
            if (!visited[arcNode->adjvex]) {
                stack.push(arcNode->adjvex);
            }
            arcNode = arcNode->nextArc;
        }
    }
    printf("\n");
}

void ALGraph_BreadthFirstSearch(const ALGraph &graph, int pos, vector<int> *result) {
    vector<int> visited(graph.vexNum);
    queue<int> q;
    q.push(pos);
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        if (!visited[front]) {
            visited[front] = 1;
            result->push_back(front);
            printf("%s ", graph.vertices[front].data.c_str());
        }

        ArcNode *arcNode = graph.vertices[front].firstArc;
        while (arcNode) {
            int next = arcNode->adjvex;
            if (!visited[next]) {
                q.push(next);
            }
            arcNode = arcNode->nextArc;
        }
    }
    printf("\n");
}
