Cau truc du lieu va giai thuat.
---------------------------------------
big data, machine learning
Du lieu nhieu (1 mil records) --> tim kiem
rat kho, mat thoi gian (time & space complexity)

To chuc du lieu trong cau truc du lieu
--> khi can se tim thay ngay lap tuc.
---------------------------------------

Con tro tro den o nho
Kick thuoc con tro = kick thuoc o nho
char *p1;
int *p2;
char A[10] = {0};
sizeof(p1) = 1 ; // 1 byte
sizeof(p2) = ... (depend on architecture PIC, HTPIC)
sizeof(A) = 10; // kick thuoc da dc cap phat.

---------------------------------------
Dinh nghia kieu du lieu moi cua rieng minh
typedef struct node
{
	int data[10];
	struct node *p_next; // recursive - CORRECT.
//	node_t *p_next; // WRONG.
} node_t, *p_node_t;

node_t testStruct;
p_node_t p_testStruct = NULL;
node_t* testStruct2;

testStruct.data[i];
p_testStruct->data[i];
-----------------------------------------
Linked list
node_t* p_Head = NULL; //tao con tro p_Head de luu tru dia chi dau cua Head

Union (Big/Little)
Union cap phat 2 bytes (short 2 bytes va char 1 byte) --> short va char dung chung o nho.
typedef union ds_{
short s;
char c;
}ds;
ds object;
object.s = 0x0503;
printf("%d\n", object.c);
--> o nho cua c se la hoac 05 hoac 03 (tuy thuoc kien truc may tinh)

The concept of structure and union are same. Both are created to collect different data type in one variable.
The only difference is in memory management i.e. Memory requirement of the two. 
If we declared a structure with 1 char and two int variable then it we use 5byte of RAM while we execute program. 
If we declare struct1, struct2 of the above structure type then both structures will acquire 5 byte each 
i.e. Total 10 bytes will be used of RAM. On the other hand if we declare union with 1char and 2 int variable 
and declare to instance uni1 and uni2 then they will acquire only 5 bytes. 
If we access uni1 first then data we entered will be stored at uni1's variable and 
if we again enter value of variables for uni2 then these will be overwriten of the uni1 variables. 
Advantage of union over structure : - 
Less RAM space is required thus fast execution of program. 
DisAdvantage of Union over structure : - 
If we use 2 or more instance of single onion the data will be lost after data for second instance is entered. 
I think the concept of union and structure is clear to you.

Unions are used to save only one type of data at a time. 
If a value is reassigned the old value is overwritten and cannot be accessed. In your example int ,float and char members can all have different values at any time when used as a struct. Its not the case in union. So it depends on your program requirements and design. Check this article on when to use union. Google may give even more results.