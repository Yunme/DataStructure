//
// Created by zzqni on 2024/5/1.
//

#include <valarray>
#include <cstring>
#include "testSort.h"

static SqList fixedData() {
//    const int count = 20;
    int count;
//    int array[count] = {81, 68, 32, 1, 4, 25, 94, 64, 30, 71, 85,
//                        24, 70, 62, 28, 54, 31, 43, 53, 20};
//    int array[] = {60, 70, 80, 90, 100};
//    int array[count] = {70, 60, 65, 90, 100};
//    int array[] = {10, 5, 15, 3, 7, 18, 12, 20};
//    int array[] = {588, 3, 699, 928, 834, 764, 526, 235, 919, 899, 182, 983, 817, 149, 897, 371, 833, 910, 165, 431,
//                   119,
//                   671, 902, 838, 444, 359, 211, 484, 327, 898, 292, 4, 84, 366, 940, 627, 123, 851, 274, 736, 523, 541,
//                   913, 905, 191, 137, 791, 197, 583, 498};
    int array[] = {101, 402, 303, 266, 202};

    count = size(array);
    SqList list;
    list.length = count;
    for (int i = 0; i < count; ++i) {
        list.r[i].key = array[i];
    }
    return list;
}

void testInsertSort() {
    SqList data = fixedData();
    SortPrint(data);
    printf("====ֱ�Ӳ������򣬴Ӻ���ǰ�ң�\n");
    Sort_InsertStraight(data);
    printf("====ֱ�Ӳ������򣬴�ǰ����ң�\n");
    data = fixedData();
    Sort_InsertStraightBackward(data);
    printf("====���ֲ�������\n");
    data = fixedData();
    Sort_InsertBinary(data);
    printf("====ϣ������\n");
    data = fixedData();
    Sort_InsertShell(data);
}

void testSwapSort() {
    SqList data = fixedData();
    SortPrint(data);
    printf("====ð������\n");
    Sort_SwapBubble(data);

    printf("====��������\n");
    data = fixedData();
    Sort_SwapQuick(data, 0, data.length - 1);
    SortPrint(data);
}

void testSelectionSort() {
    SqList data = fixedData();
    SortPrint(data);
    printf("====��ѡ������\n");
    Sort_SelectionSimple(data);

    printf("====������\n");
    data = fixedData();
    Sort_SelectionHeap(data);
    SortPrint(data);

    printf("====�鲢����\n");
    data = fixedData();
    Sort_MergeSort(data, 0, data.length - 1);
    SortPrint(data);
}

void Sort(SLList L, int adr[]) {
    //���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼�����
    int i = 0, p = L.r[0].next;
    while (p) {
        adr[i++] = p;
        p = L.r[p].next;
    }
}

void Rearrange(SLList &L, int adr[]) {
    //adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼��
    //���㷨��adr����L.r��ʹ�������㷨10.18(L�������б�)
    int i, j, k;
    if (adr[i] != i) {
        j = i;
        L.r[0] = L.r[i]; //�ݴ��¼(*L).r[i]
        while (adr[j] != i) {
            //����(*L).r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ
            k = adr[j];
            L.r[j] = L.r[k];
            adr[j] = j;
            j = k; //��¼����λ
        }
        L.r[j] = L.r[0];
        adr[j] = j;
    }
}

void testRadixSort() {
    SLList l;
    int *adr;
    int max = -1;
    int count = 5;
//    vector<ElementType> data = getDataArrayForSort(count, max);
    SqList sqList = fixedData();
    vector<ElementType> data(sqList.r, sqList.r + sqList.length);

    for (ElementType &e: data) {
        if (e.key > max)
            max = e.key;
        printf("%d ", e.key);
    }
    printf("\n");
    l.keyNum = ceil(log10(max));
    l.recordNum = count;
    for (int i = 1; i <= count; i++) {
        char c[10];
        itoa(data[i - 1].key, c, 10);  //��10��������ת��Ϊ�ַ���,����c
        for (int j = strlen(c); j < l.keyNum; j++) { //��c�ĳ���<max��λ��,��cǰ��'0'
            char c1[10];
            strcpy(c1, "0");
            strcat(c1, c);
            strcpy(c, c1);
        }
        for (int j = 0; j < l.keyNum; j++)
            l.r[i].keys[j] = c[l.keyNum - 1 - j];
    }
//    RadixSort(l);
//    RadixPrint(l);
//
//    adr = new int[l.recordNum];
//    Sort(l, adr);
//    Rearrange(l, adr);
//    cout << "�����(���ż�¼):\n";
////    print(l);
//    RadixPrint(l);

    radixSort(data);
    for (ElementType &e: data) {
        printf("%d ", e.key);
    }
}


void testSort() {
//    testInsertSort();
//    testSwapSort();
//    testSelectionSort();
    testRadixSort();
}