//
// Created by zzqni on 2024/4/23.
//

#include "testGraph.h"


void testALGraph() {
    ALGraph graph;
    int vexNum = 5;
    int arcNum = 6;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i + 1);
    }

    vector<pair<string, string>> edges(0);
    edges.emplace_back("v1", "v2");
    edges.emplace_back("v1", "v4");
    edges.emplace_back("v2", "v3");
    edges.emplace_back("v2", "v5");
    edges.emplace_back("v3", "v4");
    edges.emplace_back("v3", "v5");
    ALGraph_CreateUDG(graph, vexNum, arcNum, vertices, edges);
    ALGraph_Print(graph);

    VNode *vNode = ALGraph_FindVNode(graph, "v3");
    VertexType data;
    ALGraph_GetVex(graph, *vNode, data);
    printf("Get from vNode: %s\n", data.c_str());

    // 顶点赋值
//    ALGraph_PutVex(graph, *vNode, "v9");
    ALGraph_Print(graph);

    // 第一个邻接顶点
    VNode firstAdjVex;
    ALGraph_FirstAdjVex(graph, *vNode, firstAdjVex);
    printf("Get first adjVex from %s is: %s\n", vNode->data.c_str(), firstAdjVex.data.c_str());

    // 邻接顶点的下一个邻接顶点
    VNode nextAdjVex;
    firstAdjVex = *ALGraph_FindVNode(graph, "v4");
    ALGraph_NextAdjVex(graph, *vNode, firstAdjVex, nextAdjVex);
    printf("Get next adjVex after %s from %s is: %s\n", firstAdjVex.data.c_str(), vNode->data.c_str(),
           nextAdjVex.data.c_str());

    // 新增顶点
    printf("add vex:\n");
    ALGraph_InsertVex(graph, "v6");
    ALGraph_Print(graph);
    // 删除顶点 ???
//    printf("delete vex:\n");
//    ALGraph_DeleteVex(graph, "v3");
//    ALGraph_Print(graph);

    // 新增边
    printf("add arc:\n");
    ALGraph_InsertArc(graph, Arc("v5", "v6"));
    ALGraph_Print(graph);
    ALGraph_InsertArc(graph, Arc("v5", "v6"));
    ALGraph_Print(graph);

    // 删除边
//    printf("delete arc:\n");
//    ALGraph_DeleteArc(graph, Arc("v5", "v6"));
//    ALGraph_DeleteArc(graph, Arc("v5", "v6"));
//    ALGraph_Print(graph);

    // DFS
    printf("DFS:\n");
    int visited[graph.vexNum];
    for (int i = 0; i < graph.vexNum; ++i) {
        visited[i] = 0;
    }
    printf("recursive:\n");
    ALGraph_DepthFirstSearchRecursive(graph, visited, 0);
    printf("no recursive:\n");
    ALGraph_DepthFirstSearch(graph, 0);
    cout << endl;

    // BFS
    printf("BFS:\n");
    ALGraph_BreadthFirstSearch(graph, 0);
}

void testAMGraph() {
    AMGraph graph;
    int vexNum = 5;
    int arcNum = 6;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i + 1);
    }

    vector<WeightedArc> edges(0);
    edges.emplace_back(Arc("v1", "v2"), 2);
    edges.emplace_back(Arc("v1", "v4"), 4);
    edges.emplace_back(Arc("v2", "v3"), 5);
    edges.emplace_back(Arc("v2", "v5"), 3);
    edges.emplace_back(Arc("v3", "v4"), 2);
    edges.emplace_back(Arc("v3", "v5"), 6);
    AMGraph_CreateUDN(graph, vexNum, arcNum, vertices, edges);
    AMGraph_Print(graph);

    // 寻找顶点
    int pos = AMGraph_LocateVex(graph, "v3");

    // 顶点赋值
    printf("vex assign at %d:\n", pos);
    AMGraph_PutVex(graph, pos, "v9");
    AMGraph_Print(graph);

    // 第一个邻接顶点
    VertexType adjVex;
    AMGraph_FirstAdjVex(graph, pos, adjVex);
    printf("Get first adjVex at %d is: %s\n", pos, adjVex.c_str());

    // 邻接顶点的下一个邻接顶点
    VertexType nextAdjVex;
    pos = 2;
    AMGraph_NextAdjVex(graph, pos, adjVex, nextAdjVex);
    printf("Get next adjVex after %s at %d is: %s\n", adjVex.c_str(), pos,
           nextAdjVex.c_str());

    // 新增顶点
    printf("add vex: v6\n");
    AMGraph_InsertVex(graph, "v6");
    AMGraph_Print(graph);
    // 删除顶点 ???
    printf("delete vex: v9\n");
//    AMGraph_DeleteVex(graph, "v9");
//    AMGraph_DeleteVexOpt(graph, "v9");
    AMGraph_Print(graph);

    // 新增边
    printf("add arc:\n");
    AMGraph_InsertArc(graph, WeightedArc(Arc("v5", "v6"), 9));
    AMGraph_Print(graph);
    AMGraph_InsertArc(graph, WeightedArc(Arc("v5", "v6"), 11));
    AMGraph_Print(graph);

    // 删除边
//    printf("delete arc:\n");
//    ALGraph_DeleteArc(graph, Arc("v5", "v6"));
//    ALGraph_DeleteArc(graph, Arc("v5", "v6"));
//    ALGraph_Print(graph);

    // DFS
    printf("DFS:\n");
    int visited[graph.vexNum];
    for (int i = 0; i < graph.vexNum; ++i) {
        visited[i] = 0;
    }
    printf("recursive:\n");
    AMGraph_DepthFirstSearchRecursive(graph, visited, 0);
    cout << endl;
    printf("no recursive:\n");
    AMGraph_DepthFirstSearch(graph, 0);
    cout << endl;
    // BFS
    printf("BFS:\n");
    AMGraph_BreadthFirstSearch(graph, 0);
}

void testGraphMSTAlgorithm() {
    AMGraph graph;
    int vexNum = 6;
    int arcNum = 9;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i + 1);
    }

    vector<WeightedArc> edges(0);
    edges.emplace_back(Arc("v1", "v2"), 6);
    edges.emplace_back(Arc("v1", "v3"), 1);
    edges.emplace_back(Arc("v1", "v4"), 5);
    edges.emplace_back(Arc("v2", "v3"), 5);
    edges.emplace_back(Arc("v2", "v5"), 3);
    edges.emplace_back(Arc("v3", "v4"), 5);
    edges.emplace_back(Arc("v3", "v5"), 6);
    edges.emplace_back(Arc("v3", "v6"), 4);
    edges.emplace_back(Arc("v4", "v6"), 2);
    edges.emplace_back(Arc("v5", "v6"), 6);
    AMGraph_CreateUDN(graph, vexNum, arcNum, vertices, edges);
    AMGraph_Print(graph);

    vector<int> foundVertexes(0);
    foundVertexes.push_back(0);
    vector<int> remainVertexes(vexNum - 1);
    for (int i = 0; i < vexNum; ++i) {
        remainVertexes[i] = i + 1;
    }
    AMGraph mst;
    AMGraph_InitUDN(mst, graph.vexNum, graph.arcNum);
    mst.arcNum = 0;
    for (int i = 0; i < vexNum; ++i) {
        mst.vexs[i] = graph.vexs[i];
    }
    printf("Prim MST1:\n");
    PrimMST_AMGraph(graph, foundVertexes, remainVertexes, mst);
    AMGraph_Print(mst);
//
//    GetMST_AMGraph(graph, 0);

    printf("Prim MST2:\n");
    PrimMST_AMGraph2(graph);

    printf("Kruskal MST:\n");
    KruskalMST_AMGraph(graph);


    ALGraph alGraph;
    ALGraph_CreateUDN(alGraph, vexNum, arcNum, vertices, edges);
    ALGraph_Print(alGraph);

    printf("Kruskal MST:\n");
    KruskalMST_ALGraph(alGraph);
}

void testGraphShortestPathAlgorithm() {
    AMGraph graph;
    int vexNum = 7;
    int arcNum = 10;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i);
    }

    vector<WeightedArc> edges(0);
    edges.emplace_back(Arc("v0", "v1"), 13);
    edges.emplace_back(Arc("v0", "v2"), 8);
    edges.emplace_back(Arc("v0", "v4"), 30);
    edges.emplace_back(Arc("v0", "v6"), 32);
    edges.emplace_back(Arc("v1", "v5"), 9);
    edges.emplace_back(Arc("v1", "v6"), 7);
    edges.emplace_back(Arc("v2", "v3"), 5);
    edges.emplace_back(Arc("v3", "v4"), 6);
    edges.emplace_back(Arc("v4", "v5"), 2);
    edges.emplace_back(Arc("v5", "v6"), 17);
    AMGraph_CreateDN(graph, vexNum, arcNum, vertices, edges);
    AMGraph_Print(graph);

    vector<int> shortestPath(graph.vexNum, -1);
    printf("Dijkstra shortest path for AMGraph\n");
    vector<ArcType> shortestWeight(graph.vexNum, MaxInt);
    DijkstraShortestPath_AMGraph(graph, 0, shortestPath, shortestPath);
    for (int i = 0; i < shortestPath.size(); ++i) {
        if (shortestPath[i] >= 0 && shortestPath[i] < graph.vexNum)
            printf("vex %s from %s\n", graph.vexs[i].c_str(), graph.vexs[shortestPath[i]].c_str());
    }
    printf("\n");

    ALGraph alGraph;
    printf("Dijkstra shortest path for ALGraph\n");
    ALGraph_CreateDN(alGraph, vexNum, arcNum, vertices, edges);
    ALGraph_Print(alGraph);
    for (int &i: shortestPath) {
        i = -1;
    }
    shortestWeight.resize(alGraph.vexNum);
    DijkstraShortestPath_ALGraph(alGraph, 0, shortestPath, shortestWeight);
    for (int i = 0; i < shortestPath.size(); ++i) {
        if (shortestPath[i] >= 0 && shortestPath[i] < alGraph.vexNum)
            printf("vex %s from %s\n", alGraph.vertices[i].data.c_str(),
                   alGraph.vertices[shortestPath[i]].data.c_str());
    }

    printf("Floyd shortest path for AMGraph:\n");
    int **matrix = new int *[graph.vexNum];
    int **path = new int *[graph.vexNum];
    for (int i = 0; i < graph.vexNum; ++i) {
        matrix[i] = new int[graph.vexNum];
        path[i] = new int[graph.vexNum];
    }
    FloydShortedPath_AMGraph(graph, matrix, path);
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            if (matrix[i][j] == MaxInt) {
                printf("%6s ", "\u221E");
            } else {
                printf("%4d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        matrix[i] = new int[graph.vexNum];
    }
    printf("Floyd shortest path for ALGraph:\n");
    FloydShortedPath_ALGraph(alGraph, matrix);
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            if (matrix[i][j] == MaxInt) {
                printf("%6s ", "\u221E");
            } else {
                printf("%4d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void testTopologicalAlgorithm() {
    AMGraph amGraph;
    int vexNum = 12;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "c" + to_string(i + 1);
    }

    vector<Arc> edges(0);
    edges.emplace_back("c1", "c2");
    edges.emplace_back("c1", "c3");
    edges.emplace_back("c1", "c4");
    edges.emplace_back("c1", "c12");
    edges.emplace_back("c2", "c3");
    edges.emplace_back("c3", "c5");
    edges.emplace_back("c3", "c7");
    edges.emplace_back("c3", "c8");
    edges.emplace_back("c4", "c5");
    edges.emplace_back("c5", "c7");
    edges.emplace_back("c6", "c8");
    edges.emplace_back("c9", "c10");
    edges.emplace_back("c9", "c11");
    edges.emplace_back("c9", "c12");
    edges.emplace_back("c10", "c12");
    edges.emplace_back("c11", "c6");
    // add a cycle
    // edges.emplace_back("c12", "c9");
    int arcNum = edges.size();
    AMGraph_CreateDAG(amGraph, vexNum, arcNum, vertices, edges);
    AMGraph_Print(amGraph);

    printf("Topological Sort for AMGraph:\n");
    vector<int> topologicalSort;
    TopologicalSort_AMGraph(amGraph, topologicalSort);
    for (int i: topologicalSort) {
        printf("%s ", amGraph.vexs[i].c_str());
    }
    printf("\n");
    if (topologicalSort.size() == amGraph.vexNum) {
        printf("the graph has no cycle!\n");
    } else {
        printf("the graph has cycle!\n");
    }
//    AMGraph_Print(amGraph);
    printf("Topological Sort Opt for AMGraph:\n");
    topologicalSort.resize(0);
    TopologicalSort_AMGraphOpt(amGraph, topologicalSort);
    for (int i: topologicalSort) {
        printf("%s ", amGraph.vexs[i].c_str());
    }
    printf("\n");
    if (topologicalSort.size() == amGraph.vexNum) {
        printf("the graph has no cycle!\n");
    } else {
        printf("the graph has cycle!\n");
    }

    ALGraph alGraph;
    ALGraph_CreateDG(alGraph, vexNum, arcNum, vertices, edges);
    printf("DFS for ALGraph:\n");
    ALGraph_DepthFirstSearch(alGraph, 0);
    ALGraph_BreadthFirstSearch(alGraph, 0);
    ALGraph_Print(alGraph);
    printf("Topological Sort for ALGraph:\n");
    topologicalSort.resize(0);
    TopologicalSort_ALGraph(alGraph, topologicalSort);
    for (int i: topologicalSort) {
        printf("%s ", alGraph.vertices[i].data.c_str());
    }
    printf("\n");
    if (topologicalSort.size() == alGraph.vexNum) {
        printf("the graph has no cycle!\n");
    } else {
        printf("the graph has cycle!\n");
    }
}

void testCriticalPathAlgorithm() {
    AMGraph amGraph;
    int vexNum = 9;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i);
    }
    vector<WeightedArc> edges(0);
    edges.emplace_back(Arc("v0", "v2"), 4);
    edges.emplace_back(Arc("v0", "v1"), 6);
    edges.emplace_back(Arc("v0", "v3"), 5);
    edges.emplace_back(Arc("v1", "v4"), 1);
    edges.emplace_back(Arc("v2", "v4"), 1);
    edges.emplace_back(Arc("v3", "v5"), 2);
    edges.emplace_back(Arc("v4", "v6"), 9);
    edges.emplace_back(Arc("v4", "v7"), 7);
    edges.emplace_back(Arc("v5", "v7"), 4);
    edges.emplace_back(Arc("v6", "v8"), 2);
    edges.emplace_back(Arc("v7", "v8"), 4);
    int arcNum = edges.size();
    AMGraph_CreateDN(amGraph, vexNum, arcNum, vertices, edges);
    AMGraph_Print(amGraph);

    printf("Critical Path for AMGraph:\n");
    vector<pair<int, int >> criticalPath;
    CriticalPath_AMGraph(amGraph, criticalPath);
    for (pair p: criticalPath) {
        printf("<%s,%s>\n", amGraph.vexs[p.first].c_str(), amGraph.vexs[p.second].c_str());
    }

    ALGraph alGraph;
    ALGraph_CreateDN(alGraph, vexNum, arcNum, vertices, edges);
    ALGraph_Print(alGraph);
    printf("Critical Path for ALGraph:\n");
    criticalPath.resize(0);
    CriticalPath_ALGraph(alGraph, criticalPath);
    for (pair p: criticalPath) {
        printf("<%s,%s>\n", amGraph.vexs[p.first].c_str(), amGraph.vexs[p.second].c_str());
    }
}

void testExercise() {
    // 求图中距离顶点v最短路径长度最大的顶点
    int vexNum = 7;
    int arcNum = 10;
    vector<string> vertices(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i);
    }

    vector<WeightedArc> edges(0);
    edges.emplace_back(Arc("v0", "v1"), 13);
    edges.emplace_back(Arc("v0", "v2"), 8);
    edges.emplace_back(Arc("v0", "v4"), 30);
    edges.emplace_back(Arc("v0", "v6"), 32);
    edges.emplace_back(Arc("v1", "v5"), 9);
    edges.emplace_back(Arc("v1", "v6"), 7);
    edges.emplace_back(Arc("v2", "v3"), 5);
    edges.emplace_back(Arc("v3", "v4"), 6);
    edges.emplace_back(Arc("v4", "v5"), 2);
    edges.emplace_back(Arc("v5", "v6"), 17);
    ALGraph alGraph;
    ALGraph_CreateDN(alGraph, vexNum, arcNum, vertices, edges);
    ALGraph_Print(alGraph);
    int pos = 0;
    int longestVex = GraphExercise_MaxShortestPath(alGraph, pos);
    if (longestVex >= 0)
        printf("the longest distance from vex %s is %s.\n", alGraph.vertices[pos].data.c_str(),
               alGraph.vertices[longestVex].data.c_str());
    else
        printf("vex %s can't reach other vex.\n", alGraph.vertices[pos].data.c_str());

    // 有向图中顶点a能否可达顶点b
    vexNum = 12;
    vertices.resize(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "c" + to_string(i + 1);
    }
    vector<Arc> edges2(0);
    edges2.emplace_back("c1", "c2");
    edges2.emplace_back("c1", "c3");
    edges2.emplace_back("c1", "c4");
    edges2.emplace_back("c1", "c12");
    edges2.emplace_back("c2", "c3");
    edges2.emplace_back("c3", "c5");
    edges2.emplace_back("c3", "c7");
    edges2.emplace_back("c3", "c8");
    edges2.emplace_back("c4", "c5");
    edges2.emplace_back("c5", "c7");
    edges2.emplace_back("c6", "c8");
    edges2.emplace_back("c9", "c10");
    edges2.emplace_back("c9", "c11");
    edges2.emplace_back("c9", "c12");
    edges2.emplace_back("c10", "c12");
    edges2.emplace_back("c11", "c6");
    arcNum = edges2.size();
    int startPos = 8, endPos = 7;
    ALGraph DAG;
    ALGraph_CreateDG(DAG, vexNum, arcNum, vertices, edges2);
    bool reach = GraphExercise_CanVertexReach(DAG, startPos, endPos);
    if (reach) {
        printf("%s can reach %s.\n", DAG.vertices[startPos].data.c_str(), DAG.vertices[endPos].data.c_str());
    } else {
        printf("%s can not reach %s.\n", DAG.vertices[startPos].data.c_str(), DAG.vertices[endPos].data.c_str());
    }

    // 两顶点间的简单路径是否为k
    ALGraph UDG;
    vexNum = 5;
    vertices.resize(vexNum);
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = "v" + to_string(i + 1);
    }
    edges2.resize(0);
    edges2.emplace_back("v1", "v2");
    edges2.emplace_back("v1", "v4");
    edges2.emplace_back("v2", "v3");
    edges2.emplace_back("v2", "v5");
    edges2.emplace_back("v3", "v4");
    edges2.emplace_back("v3", "v5");

    edges2.emplace_back("v1", "v5");
    arcNum = edges2.size();
    ALGraph_CreateUDG(UDG, vexNum, arcNum, vertices, edges2);
    ALGraph_Print(UDG);
    startPos = 0;
    endPos = 4;
    int length = 1;
    bool lengthCorrect = GraphExercise_PathLength(UDG, startPos, endPos, length);
    if (lengthCorrect) {
        printf("length between %s and %s is (%d).\n", UDG.vertices[startPos].data.c_str(),
               UDG.vertices[endPos].data.c_str(), length);
    } else {
        printf("length between %s and %s is not (%d).\n", UDG.vertices[startPos].data.c_str(),
               UDG.vertices[endPos].data.c_str(), length);
    }
}

void testGraph() {
//    testALGraph();
//    testAMGraph();
//    testGraphMSTAlgorithm();
//    testGraphShortestPathAlgorithm();
//    testTopologicalAlgorithm();
//    testCriticalPathAlgorithm();
    testExercise();
}
