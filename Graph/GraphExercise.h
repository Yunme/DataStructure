//
// Created by zzqni on 2024/4/26.
//

#ifndef ANDROIDFRAMEWORKTEST_GRAPHEXERCISE_H
#define ANDROIDFRAMEWORKTEST_GRAPHEXERCISE_H

#include "ALGraph.h"
#include "AMGraph.h"
#include "GraphAlgorithm.h"

int GraphExercise_MaxShortestPath(const ALGraph &graph, int pos);

bool GraphExercise_CanVertexReach(const ALGraph &graph, int aPos, int bPos);

bool GraphExercise_PathLength(const ALGraph &graph, int aPos, int bPos, int pathLength);

#endif //ANDROIDFRAMEWORKTEST_GRAPHEXERCISE_H
