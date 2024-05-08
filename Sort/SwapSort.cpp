//
// Created by zzqni on 2024/5/1.
//

#include <random>
#include "SwapSort.h"

/**
 * ������ð������
 */
void Sort_SwapBubble(SortSqList &list) {
    int totalCompare = 0;
    for (int i = 0; i < list.length - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < list.length - i - 1; ++j) {
            printf("Ԫ�� %d �� Ԫ�� %d �Ƚ�\n", list.r[j].key, list.r[i].key);
            totalCompare++;
            if (list.r[j].key > list.r[j + 1].key) {
                ElementType temp = list.r[j + 1];
                list.r[j + 1] = list.r[j];
                list.r[j] = temp;
                swapped = true;
            }
            SortPrint(list);
        }
        if (!swapped) break;
    }
    printf("�ܹ��Ƚ�%d��\n", totalCompare);
}


/**
 *  ���Ż��� ��ͨ�汾
 *  ���֣��ѱ� pivot С��Ԫ�طŵ���ǰ�棬��ķŵ����棬��һ��ѭ����ʵ�֡�
 *
 *  ȱ�㣺
 *  1. ����˳�����������������ʱ��ÿ�β��ֻ��һ��Ԫ�ء����Ӷȳ�Ϊ N^2�������׼�����
 *  2. �������ظ�Ԫ�ؽ϶�ʱ�����Ӷȳ�Ϊ N^2��˫·����·���Ž����
 */
int Sort_SwapQuickPartitionNormal(SortSqList &list, int low, int high) {
    // �����׼�������������������� ���졣��������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(low, high);
    int random = dis(gen);
    swap(list.r[low], list.r[random]);

    ElementType pivot = list.r[low];
    int j = low;
    // nums[low + 1 .. j] ��Ԫ�� <= pivot
    // nums(j..i) > pivot
    for (int i = low + 1; i <= high; ++i) {
        // j ��ʾ <= pivot Ԫ�������ұ�Ԫ�ص�������
        // i �� low + 1 ��ʼ�������ӦԪ��С�� pivot ����ô j + 1, ���Ǵ��� pivot �ĵ�һ��Ԫ��
        if (list.r[i].key <= pivot.key) {
            j++;
            swap(list.r[i], list.r[j]);
        }
    }
    // j �������ұߵ� <= pivot ��Ԫ��λ�á�
    // ��� �� low �ŵ� j ��λ�á�
    swap(list.r[low], list.r[j]);
    return j;
}

/**
 * �������������� ����
 * ˫·����
 */
int Sort_SwapQuickPartition(SortSqList &list, int low, int high) {
    // �����׼�������������������� ���졣��������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(low, high);
    int random = dis(gen);
    swap(list.r[low], list.r[random]);

    ElementType data = list.r[low];
    KeyType pivotKey = list.r[low].key;
    // ˫ָ��һǰһ��
    while (low < high) {
        // high λ�� >= ��׼���������㣬 high--
        // ֱ�� high λ�� < ��׼������ѭ����high λ�õ�Ԫ�ش浽 low λ�á�
        while (low < high && list.r[high].key >= pivotKey)
            --high;
        list.r[low] = list.r[high];

        // low λ�� <= ��׼���������㣬low++
        // ֱ�� low λ�� > ��׼������ѭ����low λ�õ�Ԫ�ش浽 high λ��
        while (low < high && list.r[low].key <= pivotKey)
            ++low;
        list.r[high] = list.r[low];
    }
    // low �� high �غ� λ�þ��ǻ�׼����λ�á�
    list.r[low] = data;
    return low;
}

/**
 * ��������������
 */
void Sort_SwapQuick(SortSqList &list, int low, int high) {
    if (low < high) {
//        int pivotPos = Sort_SwapQuickPartitionNormal(list, low, high);
        int pivotPos = Sort_SwapQuickPartition(list, low, high);

        Sort_SwapQuick(list, low, pivotPos - 1);
        Sort_SwapQuick(list, pivotPos + 1, high);
    }
}

/**
 * ��·��������
 * ������ظ�Ԫ�أ��ݹ����䳤
 * �������Σ��м���ǵ��� pivot ��Ԫ��
 *
 * 1. ��Ԫ�� < pivot��Ԫ�ؽ����� ���� pivot �����ǰһ��λ��
 * 2. ��Ԫ�� = pivot��ʲô������������һ��Ԫ��
 * 3. ��Ԫ�� > pivot, Ԫ�ؽ��������� pivot ��ǰһ��λ�á�
 */
void Sort_SwapQuickThreeWay(SortSqList &list, int low, int high) {
    if (low < high) {
        // �����׼�������������������� ���졣��������
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution dis(low, high);
        int random = dis(gen);
        swap(list.r[low], list.r[random]);
        ElementType pivot = list.r[low];
        // С�ڻ�׼ֵ������ұ߽�
        int lessThan = low;
        // ���ڻ�׼ֵ�������߽�
        int greatThan = high;
        int i = low + 1;
        while (i <= greatThan) {
            if (list.r[i].key < pivot.key) {
                // С�ڻ�׼ֵ ��С�ڵ��ұ߽罻��
                swap(list.r[i], list.r[lessThan]);
                lessThan++;
                i++;
            } else if (list.r[i].key > pivot.key) {
                // ���ڻ�׼ֵ �����ڵ���߽罻��
                swap(list.r[i], list.r[greatThan]);
                greatThan--;
            } else {
                // ���ڻ�׼ֵ �������� i++
                i++;
            }
        }
        Sort_SwapQuickThreeWay(list, low, lessThan - 1);
        Sort_SwapQuickThreeWay(list, greatThan + 1, high);
    }
}
