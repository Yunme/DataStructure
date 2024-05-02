//
// Created by zzqni on 2024/4/22.
//

#ifndef ANDROIDFRAMEWORKTEST_AMGRAPH_H
#define ANDROIDFRAMEWORKTEST_AMGRAPH_H

#include "../common.h"
#include "Graph.h"

/**
 * 邻接矩阵 Adjacency Matrix Graph
 */

typedef struct {
    VertexType vexs[MVNum];     // 顶点表
    ArcType arcs[MVNum][MVNum];     // 邻接矩阵
    int vexNum, arcNum;     // 图的当前点数和边数。
    bool weighted;  // 是否是带权的网
} AMGraph;

void AMGraph_InitUDN(AMGraph &graph, int vexNum, int arcNum);

void AMGraph_CreateUDN(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices,
                       const vector<WeightedArc> &arcs);

void AMGraph_CreateDN(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices,
                      const vector<WeightedArc> &arcs);

void AMGraph_CreateDAG(AMGraph &graph, int vexNum, int arcNum, vector<VertexType> vertices, const vector<Arc> &arcs);

void AMGraph_Print(const AMGraph &graph);

bool AMGraph_HasArc(const AMGraph &graph, int element);

int AMGraph_GetNoArc(const AMGraph &graph);

int AMGraph_LocateVex(const AMGraph &graph, const VertexType &data);

Status AMGraph_PutVex(AMGraph &graph, int pos, const VertexType &data);

Status AMGraph_FirstAdjVex(const AMGraph &graph, int pos, VertexType &firstAdjVex);

Status AMGraph_NextAdjVex(const AMGraph &graph, int pos, const VertexType &adjVex, VertexType &nextAdjVex);

void AMGraph_InsertVex(AMGraph &graph, const VertexType &data);

void AMGraph_DeleteVex(AMGraph &graph, const VertexType &data);

void AMGraph_DeleteVexOpt(AMGraph &graph, const VertexType &data);

void AMGraph_InsertArc(AMGraph &graph, const WeightedArc &arc);

void AMGraph_DeleteArc(AMGraph &graph, const Arc &arc);

void AMGraph_DepthFirstSearchRecursive(const AMGraph &graph, int visited[], int pos);

void AMGraph_DepthFirstSearch(const AMGraph &graph, int pos);

void AMGraph_BreadthFirstSearch(AMGraph &graph, int pos);

#endif //ANDROIDFRAMEWORKTEST_AMGRAPH_H
