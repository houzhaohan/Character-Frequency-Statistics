/*
19122120
侯兆晗
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 结点结构体
typedef struct Node {
    char character;                                // 用于存储汉字
    int frequency;                                 // 用于存储该汉字的频率  
    struct Node* next;                             //指向下一个结点的指针
} Node;

// 创建结点
Node* createNode(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));   // 为新结点动态分配内存
    newNode->character = c;                        // 将传入的字符赋值给新结点的character字段
    newNode->frequency = 1;                        // 新结点的频率初始化为1，表示该汉字首次出现
    newNode->next = NULL;                          // 新结点的next字段初始化为NULL，表示当前结点没有下一个结点
    return newNode;                                // 返回新结点
}

// 插入或更新结点的频率
void insertOrUpdate(Node* head, char c) { 
    Node* current = head;                          // 从链表头部开始查找
    // 如果链表不为空并且当前结点的下一个结点的字符与要插入的字符相同
    while (current->next != NULL) 
    {
        if (current->next->character == c) 
        {
            current->next->frequency++;            // 更新该结点的频率
            return;
        }
        current = current->next;                   // 继续查找下一个结点
    }
    current->next = createNode(c);                 // 如果链表为空或者已经遍历完链表但未找到匹配的字符，则插入新的结点
}

// 冒泡排序
void bubbleSort(Node* head) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do 
    {
        swapped = 0;
        ptr1 = head->next;

        while (ptr1->next != lptr) 
        {
            if (ptr1->frequency < ptr1->next->frequency) 
            {
                // 交换频率和汉字
                int tempFrequency = ptr1->frequency;
                char tempCharacter = ptr1->character;

                ptr1->frequency = ptr1->next->frequency;
                ptr1->character = ptr1->next->character;

                ptr1->next->frequency = tempFrequency;
                ptr1->next->character = tempCharacter;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } 
    while (swapped);
}

// 打印排序后的频率
void printSortedFrequency(Node* head) {
    Node* current = head->next;                             // 从链表的第二个结点开始打印（跳过头结点）
    while (current != NULL) 
    {
        printf("字符：  %c    频率：  %d\n", current->character, current->frequency);
        current = current->next;
    }
}

int main() 
{
    FILE* file = fopen("wenben.txt", "r");
    if (file == NULL) 
    {
        printf("Unable to open file.\n");
        return 1;
    }

    Node* head = createNode('\0');                          //创建一个以'\0'为初始字符的结点作为头结点

    // 从文件中读取字符，直到遇到文件结束标记（EOF）
    char c;
    while ((c = fgetc(file)) != EOF) 
    {
        if (c!=0) 
        {
            insertOrUpdate(head, c);                        // 插入或更新结点频率
        }
    }

    fclose(file);

    bubbleSort(head);                                       // 进行排序

    printSortedFrequency(head);                             // 打印排序后的频率

    return 0;
}

