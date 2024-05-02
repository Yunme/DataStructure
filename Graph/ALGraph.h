//
// Created by zzqni on 2024/4/22.
//

#ifndef ANDROIDFRAMEWORKTEST_ALGRAPH_H
#define ANDROIDFRAMEWORKTEST_ALGRAPH_H

#include "Graph.h"
#include <vector>

using namespace std;

/**
 * 边结点
 */
typedef struct ArcNode {
    int adjvex;  // 该边指向顶点在顶点数组中的位置
    ArcNode *nextArc;  // 下一条边的指针
    ArcType weight;     // 权
} ArcNode;

/**
 * 图顶点结构
 */
typedef struct VNode {
    VertexType data;    // 顶点信息
    ArcNode *firstArc;    // 第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];

/**
 * 邻接表
 */
typedef struct {
    AdjList vertices;   // 邻接表
    AdjList converseVertices;   // 逆邻接表
    int vexNum, arcNum;     // 顶点个数，边个数
} ALGraph;

void ALGraph_CreateUDG(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                       vector<Arc> edges);

void ALGraph_CreateUDN(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                       vector<WeightedArc> edges);

void ALGraph_CreateDN(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                      vector<WeightedArc> edges);

void ALGraph_CreateDG(ALGraph &alGraph, int vexNum, int arcNum, vector<VertexType> &vertices,
                      vector<Arc> edges);

void ALGraph_Print(const ALGraph &graph);

int ALGraph_LocateVex(const ALGraph &graph, const VertexType &data);

Status ALGraph_FindVex(const ALGraph &graph, const VNode &vNode);

VNode *ALGraph_FindVNode(ALGraph &graph, const VertexType &data);

Status ALGraph_GetVex(const ALGraph &graph, const VNode &vNode, VertexType &data);

Status ALGraph_PutVex(const ALGraph &graph, VNode &vNode, const VertexType &data);

Status ALGraph_FirstAdjVex(const ALGraph &graph, const VNode &vNode, VNode &firstVNode);

Status ALGraph_NextAdjVex(const ALGraph &graph, const VNode &vNode, const VNode &adjVex, VNode &nextAdjVex);

void ALGraph_InsertVex(ALGraph &graph, const VertexType &data);

void ALGraph_DeleteVex(ALGraph &graph, const VertexType &data);

void ALGraph_InsertArc(ALGraph &graph, const Arc &arc);

void ALGraph_DeleteArc(ALGraph &graph, const Arc &arc);

void ALGraph_DepthFirstSearchRecursive(const ALGraph &graph, int visited[], int pos);

void ALGraph_DepthFirstSearch(const ALGraph &graph, int pos, vector<int> *result = nullptr);

void ALGraph_BreadthFirstSearch(const ALGraph &graph, int pos, vector<int> *result = nullptr);

#endif //ANDROIDFRAMEWORKTEST_ALGRAPH_H
