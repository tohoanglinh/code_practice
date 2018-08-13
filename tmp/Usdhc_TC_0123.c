/**
*   Copyright 2018 NXP
*   ALL RIGHTS RESERVED.
*   @file Usdhc_TC_0123.c
*
*   @brief   Test case 0123.
*   @details Function test case 0123.
*
*   @addtogroup [USDHC_TESTS]
*   @{
*/
/*==================================================================================================
ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Linh To Hoang - nxf31152     20-May-2018      ASDK-12026   Initial version for MPC574X_SDK_RTM_1.0.0
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Usdhc_TC_0123.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define T_uSDHC_MULTI_BLOCKS_THAN_TABLESIZE 140U            /* number of blocks to transfer */
/* 
entries = (140 * 512) / (0xFFFF) + 1 = 2
tableSize / sizeof(usdhc_adma2_descriptor_t) = 8U  / 8 = 1U
*                 entries = ((dataBytes / uSDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) + 1U);
*                 if (entries > (tableSize / sizeof(usdhc_adma2_descriptor_t)))
*                 {
*                     error = STATUS_USDHC_OUT_OF_RANGE;
*                 }
*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*================================================================================================*/
/**
* @test_id        Usdhc_TC_0123
* @brief          Transfer (write) data much larger than number of ADMA tables using blocking.
* @details        This test case tests transfer the amount of data entries larger than the number of ADMA table using blocking.
* @pre            N/A
* @post           N/A
*
* @test_level     ComponentValidation
* @test_type      Functional
* @test_technique WhiteBox
* @test_procedure Steps:
*                     -# Initialize the uSDHC middle-ware module with card using ADMA2 mode by calling uSDHC_Init()
*                     -# with config0 is: tableSize = 8U; number of blocks = 140U;
*                     -# Verification point:
*                        - initialize uSDHC returns STATUS_SUCCESS
*                     -# Prepare data for writing and reading
*                     -# Write multiple blocks to card from block start using ADMA2
*                     -# Verification point:
*                        - uSDHC_SetAdmaTableConfig returns STATUS_USDHC_OUT_OF_RANGE
*                        - uSDHC_DRV_TransferBlocking returns STATUS_USDHC_PREPARE_ADMA_FAILED
*                        - Write multiple blocks returns NOT STATUS_SUCCESS
*                     -# Erase all data to make sure everything cleared
*                     -# Verification point:
*                        - Erase function returns STATUS_SUCCESS
*                     -# De-initialize the uSDHC middle-ware module with card by calling uSDHC_DeInit()
*                     -# Verification point:
*                        - De-initialize function returns STATUS_SUCCESS
*
* @pass_criteria  Verification points are successful
*
* @requirements   uSDHC_020_001, uSDHC_020_002, uSDHC_021_001, uSDHC_021_002, uSDHC_006_001,
*                 uSDHC_007_001, uSDHC_019_001, uSDHC_019_002
* @traceability   N/A
* @execution_type Automated
* @hw_depend      N/A
* @sw_depend      N/A
* @boundary_test  N/A
* @defects        N/A
* @test_priority  High
* @note           N/A
* @keywords
*/

void Usdhc_TC_0123(void)
{
    /* Local variable */
    common_status_t T_uSDHC_Status;
    uint32_t blockAddress = DATA_BLOCK_START;
    sd_card_t *card;
    card = &g_sd;
    common_status_t T_write_status;

    /* Initialize uSDHC module with card */
    T_uSDHC_Status = uSDHC_Init(true);
    EU_ASSERT((common_status_t)STATUS_SUCCESS == T_uSDHC_Status);

    /* prepare a new array of data to write */
    prepareData(g_dataWrite, sizeof(g_dataWrite));

    /* configure to use transfer blocking function */
    card->host.transfer = uSDHC_TransferBlockingFunction;

    /* write multiple blocks */
    T_write_status = SD_WriteBlocks(card, g_dataWrite, blockAddress, T_uSDHC_MULTI_BLOCKS_THAN_TABLESIZE);
    EU_ASSERT((common_status_t)STATUS_SUCCESS != T_write_status);

    /* erase data in multiple blocks */
    EU_ASSERT((common_status_t)STATUS_SUCCESS == SD_EraseBlocks(card, blockAddress, T_uSDHC_MULTI_BLOCKS_THAN_TABLESIZE));

    /* De-initialize uSDHC module */
    EU_ASSERT(STATUS_SUCCESS == uSDHC_DeInit());
}

#ifdef __cplusplus
}
#endif

/** @} */
