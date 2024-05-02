//
// Created by zzqni on 2024/4/17.
//
#include "LinearList.h"

void testLinearList() {
//    testSqList();
//    testLinkList();
//    testUnionList();
//    testDuLinkList();
//    testMergeSortedSqList();
    testMergeSortedLinkList();
}

/**
 * 线性表的合并  链表实现
 */
void unionList(LinkList &L1, LinkList L2) {
    int length1 = GetLength_L(L1);
    int length2 = GetLength_L(L2);
    for (int i = 1; i <= length2; ++i) {
        ElemType e;
        GetElem_L(L2, i, e);
        if (!LocateElem_L(L1, e)) {
            InsertNode_L(L1, ++length1, e);
        }
    }
}

/**
 * 线性表的合并  顺序表实现
 */
void unionList(SqList &L1, SqList L2) {
    int length1 = GetLength(L1);
    int length2 = GetLength(L2);
    for (int i = 1; i <= length2; ++i) {
        ElemType e;
        GetElem(L2, i, e);
        if (!LocateElem(L1, e)) {
            ListInsert_Sq(L1, ++length1, e);
        }
    }
}

void testSqListUnion() {
    printf("test union two SqList:\n");
    SqList sqList1, sqList2;
    InitList_Sq(sqList1);
    InitList_Sq(sqList2);
    for (int i = 0; i < 5; ++i) {
        ListInsert_Sq(sqList1, i + 1, 'a' + i);
        ListInsert_Sq(sqList2, i + 1, 'c' + i);
    }
    printf("first: ");
    ListSq_Print(sqList1);
    printf("second: ");
    ListSq_Print(sqList2);
    unionList(sqList1, sqList2);
    printf("result: ");
    ListSq_Print(sqList1);
}

void testUnionList() {
    printf("test union two LinkList:\n");
    LinkList linkList1, linkList2;
    CreateList_Array(linkList1, "abcde");
    CreateList_Array(linkList2, "cdefg");
    printf("first: ");
    LinkList_Print(linkList1);
    printf("second: ");
    LinkList_Print(linkList2);
    unionList(linkList1, linkList2);
    printf("result: ");
    LinkList_Print(linkList1);

    testSqListUnion();
}

/**
 *  合并两个有序表，顺序表实现
 */
void mergeSortedSqList(SqList L1, SqList L2, SqList &L3) {
    InitList_Sq(L3);
    SqList &minL = GetLength(L1) > GetLength(L2) ? L2 : L1;
    SqList &maxL = &minL == &L1 ? L2 : L1;
    int minLength = minL.length;
    int maxLength = maxL.length;
    int i = 0;
    int j = 0;
    int length = 0;
    while (i < minLength && j < maxLength) {
        char a, b;
        GetElem(L1, i + 1, a);
        GetElem(L2, j + 1, b);
        if (a <= b) {
            ListInsert_Sq(L3, ++length, a);
            i++;
        } else {
            ListInsert_Sq(L3, ++length, b);
            j++;
        }
    }
    while (i < minLength) {
        char a;
        GetElem(minL, i + 1, a);
        ListInsert_Sq(L3, ++length, a);
        i++;
    }

    while (j < maxLength) {
        char a;
        GetElem(maxL, j + 1, a);
        ListInsert_Sq(L3, ++length, a);
        j++;
    }
}

void mergeSortedSqList2(SqList L1, SqList L2, SqList &L3) {
    InitList_Sq(L3);
    L3.length = L1.length + L2.length;
    // pa 指针和 pb 指针分别指向两表的第一个元素
    ElemType *pa = L1.elem;
    ElemType *pb = L2.elem;
    ElemType *pc = L3.elem;
    // paLast, pbLast分别指向最后一个元素
    ElemType *paLast = pa + L1.length - 1;
    ElemType *pbLast = pb + L2.length - 1;
    while (pa <= paLast && pb <= pbLast) {
        if (*pa < *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= paLast)
        *pc++ = *pa++;
    while (pb <= pbLast)
        *pc++ = *pb++;
}

void mergeSortLinkList(LinkList L1, LinkList L2, LinkList &L3) {
    InitList_L(L3);
    LinkNode *p = L3;
    LinkNode *p1 = L1->next;
    LinkNode *p2 = L2->next;
    while (p1 && p2) {
        if (p1->data < p2->data) {
            p->next = p1;
            p = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p = p2;
            p2 = p2->next;
        }
    }
    p->next = p1 ? p1 : p2;
}


void testMergeSortedSqList() {
    SqList sqList1, sqList2, sqList3;

    ListSq_Create(sqList1, "fnpsuvw");
    ListSq_Create(sqList2, "afxyz");
    ListSq_Print(sqList1);
    ListSq_Print(sqList2);
//    mergeSortedSqList(sqList1, sqList2, sqList3);
    mergeSortedSqList2(sqList1, sqList2, sqList3);
    ListSq_Print(sqList3);
}

void testMergeSortedLinkList() {
    LinkList linkList1, linkList2, linkList3;
    CreateList_Array(linkList1, "fnpsuvw");
    CreateList_Array(linkList2, "afxyz");
    LinkList_Print(linkList1);
    LinkList_Print(linkList2);

    mergeSortLinkList(linkList1, linkList2, linkList3);
    LinkList_Print(linkList3);
}

void testSqList() {
    SqList sqList;
    InitList_Sq(sqList);
    cout << "emtpy: " << isEmpty(sqList) << endl;
    for (int i = 0; i < 6; ++i) {
        Status status = ListInsert_Sq(sqList, i + 1, 'a' + i);
//        printf("status: %d\n", status);
    }
    int l = GetLength(sqList);
//    LocateElem(sqList, )
    char a;
    GetElem(sqList, 8, a);
    l = LocateElem(sqList, 'f');
    std::cout << "Hello, World: " << l << std::endl;
    ListDelete_Sq(sqList, 4);
    l = LocateElem(sqList, 'f');
//    printf(reinterpret_cast<const char *>(l));
    ListSq_Print(sqList);
    std::cout << "Hello, World: " << l << std::endl;
}

void testLinkList() {
    LinkList linkList;
//    CreateList_H(linkList, 5);
//    CreateList_T(linkList, 5);
    char array[] = "abcde";
    CreateList_Array(linkList, array);
    int length = GetLength_L(linkList);
    LinkList_Print(linkList);
    printf("length: %d \n", length);

    int index = 2;
    ElemType elemType;
    Status status1 = GetElem_L(linkList, index, elemType);
    if (status1 == OK) {
        printf("get element at %d : %c\n", index, elemType);
    } else {
        printf("get element at %d, not found\n", index);
    }

    if (elemType) {
        LinkNode *linkNode = LocateElem_L(linkList, elemType);
        printf("locate element %c : %p\n", elemType, linkNode);
    }

    index = LocateElemIndex_L(linkList, 'a');
    printf("locate element %c : %d\n", 'a', index);

    index = 3;
    LinkList_Print(linkList);
    printf("insert to %d\n", index);
    InsertNode_L(linkList, index, 'f');
    LinkList_Print(linkList);

    int index1 = 6;
    LinkNode linkNode1;
    Status status = GetElem_L(linkList, index1, linkNode1);
    if (status == OK) {
        printf("locate element at: %d, r: %c\n", index1, linkNode1.data);
    } else {
        printf("locate element at: %d, not found\n", index1);
    }

    char a;
    index = 2;
    printf("remove index: %d\n", index);
    DeleteNode_L(linkList, index, a);
    LinkList_Print(linkList);
}

void testDuLinkList() {
    char array[] = "abcde";
    DuLinkList duLinkList;
    CreateDuLinkList_Array(duLinkList, array);
    DuLinkList_Print(duLinkList);

    int index = 6;
    DuLNode *a;
    if ((a = GetElemP_DuL(duLinkList, index)))
        printf("get at index: %d : %c\n", index, a->data);
    else
        printf("get at index: %d not found\n", index);

    index = 6;
    printf("insert to index: %d\n", index);
    ListInsert_Dul(duLinkList, index, 'f');
    DuLinkList_Print(duLinkList);
}
