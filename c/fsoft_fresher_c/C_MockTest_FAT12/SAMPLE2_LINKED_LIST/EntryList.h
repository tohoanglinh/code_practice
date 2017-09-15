#ifndef _EntryList_H_
#define _EntryList_H_

#define SIZE_FILE_NAME             (8)
#define SIZE_EXTEND                (3)
#define SIZE_ATTRIBUTE             (1)
#define SIZE_PROPERTIES            (14)
#define SIZE_FIRST_CLUST           (2)
#define SIZE_FILE_SIZE             (4)

#define BYTE_OF_DIR                (32)
#define NUM_SECT_TO_ROOT           (19)
#define RESERVE_SECT_CNT           (1)

#define ATTR_HIDDEN                (0x02)
#define ATTR_DIRECTORY             (0x10)
#define END_OF_FILE                (0xfff)
#define ROOT_DIR_OFFSET            (0x00)

typedef struct Directory {
    char           fileName [SIZE_FILE_NAME];
    uint8_t        extend [SIZE_EXTEND];
    uint8_t        attribute;
    uint8_t        properties [SIZE_PROPERTIES];
    uint16_t       firstCluster;
    uint32_t       fileSize;
}directory_t;

typedef struct Node {
    int index;
    directory_t data;
    struct Node *next;
}node_t;

int insertFirst(node_t **head, directory_t input_data, int idx);
int length(const node_t *head);
uint16_t searchClust(node_t *head, int index);
bool isFolder(node_t *head, node_t *node);
node_t *searchIdx(node_t *head, int index);
int freeList(node_t **head);
int printNode(const node_t *node);
int printList(const node_t *head);

int readDir(directory_t *rdir, node_t **head, uint16_t startCluster, bool isSubDir);
int requestHandle(directory_t *rdir, node_t **head, uint16_t startCluster, bool isSubDir);

#endif /* _EntryList_H_ */
