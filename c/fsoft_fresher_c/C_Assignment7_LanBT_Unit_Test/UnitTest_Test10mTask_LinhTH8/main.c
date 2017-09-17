/*****************************************************************************************
 @dev: LinhTH8
 @men: LanBT
 @top: UnitTest
 @dat: 13-02-2017
 @req: test function Mod1_test10mTask
 *****************************************************************************************/
 
  /*---------------------------------FUNCTION DESCRIPTION---------------------------------
  @Func: Mod1_Test10mTask
  @Description:
  - Initialize global and count variables
  - Each 10 time, get data and assign to an array (TurnData)
  - Until number of elements (DataCount = MAX = 10)
        --> sort data using bubblesort
        --> calculate average data (AveTurnData)
  -
  @Features:
  - INIT
  - GETDATA (each 10 timer)
  - SORTDATA (each 10x10 timer)
  - AVGDATA (after SORTDATA)
  - DIAGNOSIS (each 10x10 timer)
  -----------------------------------------------------------------------------------------*/
  
  /*---------------------------------BUGS REPORT-------------------------------------------
  @Bug 1: TestMod1.c, Line 70: sortdata need to be allocated heap memory (malloc), otherwise
  program is buggy (suspended) at tmpdata += sortdata[].
  Solution 1.1: sortdata = (BYTE *) malloc (MAXDATA);
                free(sortdata);
  Solution 1.2: static BYTE sortdata[MAXDATA]; // We choose the 2nd solution
  @Bug 2: TestMod1.c, Line 88: incorrect partitioning
  Solution 2:  if((data >= LOWLIMIT) || (data <= HIGHLIMIT))
    --> if((data >= LOWLIMIT) && (data <= HIGHLIMIT))

  @Bug 3: TestMod1.h, Line 10: incorrect value of define for HITHHOLD (compare to comment)
  Solution 3:  #define HITHHOLD 198 --> #define HITHHOLD 195

  @Bug 4: TestMod1.c, Line 135: incorrect partitioning based on decision comment
  Solution 4:  if((gu8LowAveTurnData >=  LOWTHHOLD) || (gu8HighAveTurnData <= HITHHOLD))
    --> if((gu8LowAveTurnData <=  LOWTHHOLD) || (gu8HighAveTurnData >= HITHHOLD))
    
  @Bug 5: TestMod1.c: there is no statement case to switch to DIAGNOSIS
  -----------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "TestMod1.h"
#define PASS 1
#define FAIL !PASS

U8 TC_Mod1_Test10mTask_001(void);
void printData(U8 index);
U8 checkData(U8 index);

BOOL TC_Mod1_Test10mTask_002(BYTE data);

  /*---------------------------------TEST CODE - TEST CASE REPORT---------------------------
  @ID TC_Mod1_Test10mTask_001
  @detail This test to verify that Mod1_Test10mTask will get data correctly after each 10 timer count
          Timer (index) values are chosen based on boundary value testing

  @Expected result global variable: gu8TurnData = A (10), AA (20), AAAAAAAAAA (100), AAAAAAAAAA (120)
            ModeFlag, u8DataCount, TimerCnt are observed on debug watch
   TimerCnt   at 0: ModeFlag = INIT, initialization steps --> ModeFlag = GETDATA, TimerCnt += 1
              at 10: data 'A' is added, 'A', u8DataCount = 1 < MAXDATA --> ModeFlag = GETDATA
              at 20: data 'A' is added, 'AA', u8DataCount = 2 < MAXDATA --> ModeFlag = GETDATA
              at 100: data 'A' is added, 'AAAAAAAAAA', u8DataCount = 10 = MAXDATA --> ModeFlag = SORTDATA
  @Actual result:
            A
            AA
            AAAAAAAAAA
            AAAAAAAAAA
            PASS
  @Test steps
  1. Set return data in Mod3_GetADData() = TEST_DATA = 'A'
  2. To debug and observe results, set breakpoint at TestMod1.c, Line 149: TimerCnt++;
  2. Call function Mod1_Test10mTask
  3. Check value of these global veriables and static local variables in debug and output on screen
  -----------------------------------------------------------------------------------------*/
U8 TC_Mod1_Test10mTask_001(void)
{
    U8 test_result = PASS;

    U8 i, j;

    for (i = 0; i < 121; i++)
    {
        Mod1_Test10mTask();
        
        if (i == 10)
        {
            /* expect 'A' */
            printData(i);
            
            checkData(i);
        }

        if (i == 20)
        {
            /* expect 'AA' */
            printData(i);
            
            checkData(i);
        }

        if (i == 100)
        {
            /* expect 'AAAAAAAAAA' */
            printData(i);
            
            checkData(i);
        }
        
        if (i == 120)
        {
            /* expect 'AAAAAAAAAA' */
            printData(i);
            
            checkData(i);
        }
    }
    
    return test_result;
}

U8 checkData(U8 index)
{
    U8 j;
    U8 test_result = PASS;
    for (j = 0 ; j < 2; j++)
    {
        if (*(gu8TurnData+j) == 'A' &&  *(gu8TurnData+j) != '0')
        {
            test_result = test_result & PASS;
        }
        else
        {
            test_result = test_result & FAIL;
        }
    }
    return test_result;
}

void printData(U8 index)
{
    U8 j;
    
    printf("Turn Data at %d: ", index);
    
    for (j = 0 ; j < sizeof(gu8TurnData); j++)
    {
        printf("%c", *(gu8TurnData+j));
    }
    printf("\n");
}

  /*---------------------------------TEST CODE - TEST CASE REPORT---------------------------
  @ID TC_Mod1_Test10mTask_002
  @detail This test to verify that in Mod1_Test10mTask, if data is outside of [LOWLIMIT, HIGHLIMIT]
          --> bErrFlag should be set to true

  @Expected result bErrFlag = TRUE (1)

  @Actual result bErrFlag = FALSE (0)

  @Test steps
  1. Set input function, data at boundary value test
        case 1: -1
        case 2: 256
  2. Call function Mod1_SetTurnData(data)
  3. Check value of data
  @Note
  data is BYTE type --> from 0 - 255. If data is outside, then is overflow
    -1 --> ~ 255
    256 --> ~ 0
  -----------------------------------------------------------------------------------------*/
BOOL TC_Mod1_Test10mTask_002(BYTE data)
{
    BOOL bErrFlag = FALSE;
    
    // If the data is from 0 to 255, set data
    if((data >= LOWLIMIT) && (data <= HIGHLIMIT)) // LinhTH8 fixes bug2
    {
        Mod1_SetTurnData(data);
    }
    else
    {
        bErrFlag = TRUE;                        // set ErrFlag to true
    }
    
    return bErrFlag;
}

int main()
{
    U8 result;
    BYTE data;

    /* Test case 001 */
    result = TC_Mod1_Test10mTask_001();

    if (result == PASS)
    {
        printf("Result: PASS");
    }
    else
    {
        printf("Result: FAIL");
    }

    getchar();
    
    /* Test case 002 */
    data = -1;
    printf("Data = %d --> Overflow --> Error ? %d\n", data, TC_Mod1_Test10mTask_002(data));
    data = 256;
    printf("Data = %d --> Overflow --> Error ? %d", data, TC_Mod1_Test10mTask_002(data));

    return 0;
}
