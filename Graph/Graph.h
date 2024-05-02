//
// Created by zzqni on 2024/4/23.
//

#ifndef ANDROIDFRAMEWORKTEST_GRAPH_H
#define ANDROIDFRAMEWORKTEST_GRAPH_H

#include <cstdio>
#include <string>
#include <utility>
#include "../common.h"

using namespace std;

#define MaxInt 65535  // 极大值
#define ARC 1   // 有弧或边
#define NO_ARC 0    // 无弧或边
#define MVNum 100  // 最大顶点数
typedef string VertexType;  // 顶点数据类型
typedef int ArcType;   // 边的权值类型
typedef pair<VertexType, VertexType> Arc; // 弧或边
typedef pair<Arc, ArcType> WeightedArc; //带权的弧或边

#endif //ANDROIDFRAMEWORKTEST_GRAPH_H
