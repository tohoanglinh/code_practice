// #include "main.h" [UT] Comment to fix build error
#include "TestMod1.h"
//#include "TestMod2.h" [UT] Comment to fix build error
//#include "TestMod3.h" [UT] Comment to fix build error

enum MODE
{
    INIT,
    GETDATA,
    SETDATA,
    SORTDATA,
    AVGDATA,
    DIAGNOSIS,
    MODECNT
};

BYTE gu8TurnData[MAXDATA];
BYTE gu8AveTurnData;
BYTE gu8HighAveTurnData;
BYTE gu8LowAveTurnData;
STATUS gu8Status;

extern void Mod2_BubbleSort(BYTE *inData, BYTE *outdata, U8 count);
extern BYTE Mod3_GetADData();
void Mod1_Init(void);
void Mod1_TestTask(void);
void Mod1_SetTurnData(BYTE data);

static BOOL     bErrFlag;
//static U8       u8DataCount;
U8       u8DataCount;

//-------------------------------
// Function name：Mod1_Init
// Argument: None
// Return value ： None
// Describe: initialization of each variable
//-------------------------------
void Mod1_Init(void)
{
    int i;

    for(i = 0; i < MAXDATA; i++)
    {
        gu8TurnData[i] = 0;                 // Clear rotation data
    }

    gu8AveTurnData = 0;                     // Clear average rotation data
    gu8HighAveTurnData = 0;                 // Clear the upper average rotation data
    gu8LowAveTurnData = 0;                  // Clear lower average rotation data

    bErrFlag = FALSE;                       // Clear ErrFlag to FALSE
    u8DataCount = 0;                        // Clear data count
}

//-------------------------------
// Function：Mod1_Test10mTask
// Argument: None
// Return value ： None
// Features: Run every 10m, to the processing by each mode
//-------------------------------
void Mod1_Test10mTask(void)
{
    BYTE data = 0;
    BYTE tmpdata1 = 0, tmpdata2 = 0, tmpdata3 = 0;  // For the calculation
    int i;

    static int TimerCnt = 0;                // Timer counter
    static enum MODE ModeFlag = INIT;       // Mode flag
    static BYTE sortdata[MAXDATA];          // Variables of acquiring the result of sorting the rotation data.
                                            // LinhTH8 fixes bug1
    switch (ModeFlag)
    {
        // Initialization
        case INIT:
            Mod1_Init();                        // Initialization call
            TimerCnt = 0;                       // To clear the counter
            ModeFlag = GETDATA;                 // The mode to the data acquisition
            break;

        // Get data
        case GETDATA:
            if((TimerCnt % CNT10M) == 0)
            {
                data = Mod3_GetADData();                    // Get data

                // If the data is from 0 to 255, set data
                if((data >= LOWLIMIT) && (data <= HIGHLIMIT)) // LinhTH8 fixes bug2
                {
                    Mod1_SetTurnData(data);
                }
                else
                {
                    bErrFlag = TRUE;                        // set ErrFlag to true
                }

                // If the data counter is equal to or greater than the buffer size
                if(u8DataCount >= MAXDATA)
                {
                    ModeFlag = SORTDATA;                    // set mode flag to sort
                }
            }
            break;

        // Sort data
        case SORTDATA:
            Mod2_BubbleSort(gu8TurnData, sortdata, u8DataCount);
            ModeFlag = AVGDATA;                                     // Set the mode to calculate average value
            break;

        // Calculate average value
        case AVGDATA:
            /* Clear temporary */
            tmpdata1 = 0;
            tmpdata2 = 0;

            for(i = 0; i < 5; i++)
            {
                tmpdata1 += sortdata[i];                            // Calculate the lower five data total
                tmpdata2 += sortdata[i+5];                          // Calculate the top five data total
                tmpdata3 += (tmpdata1 + tmpdata2);                  // Calculate all
            }

            // Calculate average value
            gu8LowAveTurnData = (BYTE)(((float)tmpdata1 / (float)5) + 0.5);
            gu8HighAveTurnData = (BYTE)(((float)tmpdata2 / (float)5) + 0.5);
            gu8AveTurnData = (BYTE)(((float)tmpdata3 / (float)10) + 0.5);
            break;

        // Diagnosis
        case DIAGNOSIS:
            if(u8DataCount == MAXDATA)
            {
                // Lower average value of 25 or less, or if the higher average value of 195 or more
                if((gu8LowAveTurnData <=  LOWTHHOLD) || (gu8HighAveTurnData >= HITHHOLD)) // LinhTH8 fixes bug4
                {
                    gu8Status = SHIFTMODE;          // set status to shiftmode
                }
                else
                {
                    gu8Status = CONTROL;            // set status to control
                }
            }

            break;
        default:
            break;
    }
    TimerCnt++;
}


//-------------------------------
// Function ： Mod1_SetTrunData
// Argument：BYTE data
// Return value： None
// Function: set the data in the data buffer
//-------------------------------
void Mod1_SetTurnData(BYTE data)
{
    static int Idx = 0;                     // Data index

    // If Idx is was more than the buffer index of data
    if(Idx >= MAXDATA)
    {
        Idx = 0;                            // clear the index to 0
    }

    gu8TurnData[Idx] = data;                // set the data

    // If the data counter is larger than the buffer size
    if(u8DataCount < MAXDATA)
    {
        u8DataCount++;                      // Increments the data counter
    }
    Idx++;                                  // Incrementing the index
}
