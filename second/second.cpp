/*
19122120
侯兆晗
*/

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define MAX_SIZE 10000             // 定义哈希表的最大大小  
  
// 定义一个名为Node的结构体  
typedef struct Node {    
    char character;                // 存储字符  
    int frequency;                 // 存储字符的频率  
    struct Node *next;             // 指向下一个Node的指针，用于处理哈希冲突  
} Node;    
  
// 定义一个名为HashTable的结构体  
typedef struct HashTable {    
    Node **table;                  // 二维指针，指向Node指针的数组，即哈希表的主体部分  
    int size;                      // 哈希表的大小  
} HashTable;    
  
// 计算哈希值的函数  
// 输入是一个key和哈希表的大小，输出是key对应的哈希值  
int hash(int key, int size) {    
    return key % size;             // 使用取余法计算哈希值  
}    
  
// 创建哈希表的函数  
// 输入是哈希表的大小，输出是一个指向新创建的哈希表的指针  
HashTable *createHashTable(int size) {    
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));     // 为HashTable结构体分配内存  
    hashTable->size = size;                                            // 设置哈希表的大小  
    hashTable->table = (Node **)malloc(size * sizeof(Node *));         // 为Node指针数组分配内存  
    for (int i = 0; i < size; i++) 
    {    
        hashTable->table[i] = NULL;                                    // 初始化Node指针数组的每一个元素为NULL  
    }    
    return hashTable;                                                  // 返回新创建的哈希表的指针  
}
  
// 定义一个函数，用于在哈希表中插入一个新的节点  
void insert(HashTable *hashTable, char character, int frequency) {    
    int index = hash(hash(character, hashTable->size), hashTable->size);    // 使用双重哈希函数计算索引  

    Node *node = (Node *)malloc(sizeof(Node));                              // 为新的节点动态分配内存  

    node->character = character;                                            // 设置节点的字符和频率  
    node->frequency = frequency;    
      
    node->next = hashTable->table[index];                                   // 如果哈希表在该索引处已经有节点，则将新节点插入到链表的开头  
      
    hashTable->table[index] = node;                                         // 将新节点添加到哈希表的指定索引位置  
}  
  
// 定义一个函数，用于在哈希表中查找一个节点  
Node *search(HashTable *hashTable, char character) {    

    int index = hash(hash(character, hashTable->size), hashTable->size);    // 使用双重哈希函数计算索引  
      
    Node *current = hashTable->table[index];                                // 开始从哈希表的指定索引位置查找  
      
    while (current != NULL && current->character != character)              // 如果当前节点为空或其字符与要查找的不匹配，则继续查找下一个节点  
    {    
        current = current->next;    
    }    
      
    return current;                                                         // 返回找到的节点或如果未找到则返回NULL  
}  
  
// 定义一个函数，用于打印哈希表中的所有节点  
void printHashTable(HashTable *hashTable) {    
    for (int i = 0; i < hashTable->size; i++)                               // 遍历哈希表的每个索引位置  
    {    
        Node *current = hashTable->table[i];    
        while (current != NULL)                                             // 从当前索引位置开始遍历链表，并打印每个节点的字符和频率  
        {    
            printf("字符：  %c    频率：  %d\n", current->character, current->frequency);    
            current = current->next;    
        }    
    }    
}  
  
int main() 
{    
    FILE *file = fopen("wenben.txt", "r");               // 打开文件    
    if (file == NULL) 
    {    
        printf("无法打开文件\n");    
        return 1;    
    }    
    
    HashTable *hashTable = createHashTable(MAX_SIZE);    // 创建哈希表    
    
    char character;    
    int frequency = 0;    
    
    while (fscanf(file, "%c", &character) != EOF)        // 读取文件中的每个字符，并统计频率    
    {      
        // 如果遇到字符，则统计频率，并在哈希表中插入新节点或更新节点频率  
        if (character)
        {      
            Node *node = search(hashTable, character);   // 在哈希表中查找该字符的频率，如果找到则增加频率，否则插入新节点并设置频率为1    
            if (node == NULL)   
            {    
                insert(hashTable, character, 1);         // 插入新节点并设置频率为1    
            }   
            else   
            {    
                node->frequency++;                       // 如果找到则增加频率    
            }    
        }   
    }    
    
    printHashTable(hashTable);                           // 打印哈希表中的所有节点 
    
    fclose(file);                                        // 关闭文件    
    return 0;    
}

