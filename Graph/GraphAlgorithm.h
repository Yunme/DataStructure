//
// Created by zzqni on 2024/4/24.
//

#ifndef ANDROIDFRAMEWORKTEST_GRAPHALGORITHM_H
#define ANDROIDFRAMEWORKTEST_GRAPHALGORITHM_H

#include "ALGraph.h"
#include "AMGraph.h"

void PrimMST_AMGraph(const AMGraph &graph, vector<int> &foundVertexes, vector<int> &remainVertexes, AMGraph &mst);

void PrimMST_AMGraph2(const AMGraph &graph);

void GetMST_AMGraph(const AMGraph &graph, int startPos);

void KruskalMST_AMGraph(const AMGraph &graph);

void KruskalMST_ALGraph(const ALGraph &graph);

void DijkstraShortestPath_AMGraph(const AMGraph &graph, int sourceVex, vector<int> &shortestPath,
                                  vector<ArcType> &shortestWeight);

void DijkstraShortestPath_ALGraph(const ALGraph &graph, int sourceVex, vector<int> &shortestPath,
                                  vector<ArcType> &shortestWeight);

void FloydShortedPath_AMGraph(AMGraph &graph, int **matrix, int **path);

void FloydShortedPath_ALGraph(ALGraph &graph, int **matrix);

void TopologicalSort_AMGraph(AMGraph graph, vector<int> &sortResult);

void TopologicalSort_AMGraphOpt(const AMGraph &graph, vector<int> &sortResult);

void TopologicalSort_ALGraph(const ALGraph &graph, vector<int> &sortResult);

void CriticalPath_AMGraph(const AMGraph &graph, vector<pair<int, int>> &criticalPaths);

void CriticalPath_ALGraph(const ALGraph &graph, vector<pair<int, int>> &criticalPaths);

#endif //ANDROIDFRAMEWORKTEST_GRAPHALGORITHM_H
