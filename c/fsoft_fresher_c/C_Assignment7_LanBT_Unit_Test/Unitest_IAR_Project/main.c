/* Function description
 * Test code
 * Run tests
 * Report tests
 */

#include "TestMod1.h"
#define PASS 1
#define FAIL !PASS

  /*
  @ID TC_Mod1_Init_001
  @detail This test to verify that Mod1_Init will initialize global variables:
  gu8HighAveTurnData, gu8LowAveTurnData to 0

  @Expected result lobal variables:  gu8HighAveTurnData, gu8LowAveTurnData to 0

  @Actual result
  @Test step
  1. Set one of these global variables to non zero
  2. Call function Mod1_Init()
  3. Check value of these global veriables
  @Note

  */
U8 TC_Mod1_Init_001()
{
  U8 test_result = PASS;
  gu8HighAveTurnData = 123;
  Mod1_Init();
  if ((0 != gu8HighAveTurnData) ||
        (0 != gu8LowAveTurnData))
  {
    test_result = FALSE;
  }
  return test_result;
}
int main()
{
  U8 result;
  result = TC_Mod1_Init_001();
  return 0;
}
