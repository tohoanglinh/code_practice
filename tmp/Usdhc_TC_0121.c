/**
*   Copyright 2018 NXP
*   ALL RIGHTS RESERVED.
*   @file Usdhc_TC_0121.c
*
*   @brief   Test case 0121.
*   @details Function test case 0121.
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
#include "Usdhc_TC_0121.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define T_uSDHC_BLOCKSIZE_INDIVISIBLE_BY_4      511U

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
* @test_id        Usdhc_TC_0121
* @brief          Transfer (write cmd) a single block with block size not divisible by 4 using blocking.
* @details        This test case checks transfer (write cmd) a single block with block size not divisible by 4 using blocking.
* @pre            N/A
* @post           N/A
*
* @test_level     ComponentValidation
* @test_type      Functional
* @test_technique WhiteBox
* @test_procedure Steps:
*                     -# Initialize the uSDHC module and card by calling uSDHC_Init
*                     -# Verification points:
*                        - Function returns STATUS_SUCCESS
*                     -# Prepare data for writing
*                     -# Write a single block data to card from block start using ADMA2
*                     -# - Check readonly card
*                     -# Verification point:
*                        - WRITE PROTECTED bit is set correctly in PRES_STATE
*                     -# - Wait for card buffer not full
*                     -# - Wait last write complete
*                     -# Verification point:
*                        - SDMMC_WaitWriteComplete function returns STATUS_SUCCESS
*                     -# - Configure command and data to be send: single block, block size is not divisible by 4
*                     -# - Send write cmd using transfer blocking
*                     -# Verification point:
*                        - uSDHC_DRV_TransferBlocking function returns STATUS_ERROR
*                     -# De-initialize the uSDHC module and card by calling uSDHC_DeInit
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

void Usdhc_TC_0121(void)
{
    /* Local variable */
    common_status_t T_uSDHC_Status;
    uint32_t blockAddress = DATA_BLOCK_START;
    sd_card_t *card;
    card = &g_sd;
    usdhc_transfer_t content = {0};
    usdhc_command_t command = {0};
    usdhc_data_t data = {0};

    /* Initialize uSDHC module with card */
    T_uSDHC_Status = uSDHC_Init(true);
    EU_ASSERT((common_status_t)STATUS_SUCCESS == T_uSDHC_Status);

    /* prepare a new array of data to write */
    prepareData(g_dataWrite, T_uSDHC_SINGLE_BLOCK*DATA_DEFAULT_BLOCK_SIZE);

    /* WRITE DATA TO CARD
     * - Check ReadOnly Card
     * - Wait for card's buffer not full to write to improve write performance
     * - Wait Last Write Complete
     * - Send Write CMD
     */
    /* Check ReadOnly, card must be write enabled (WP=0 or WPSPL = 1) */
    Tg_uSDHC_PresentStatus = uSDHC_DRV_GetPresentStatusFlags(INST_USDHC1);
    EU_ASSERT(uSDHC_WRITE_PROTECTED == (Tg_uSDHC_PresentStatus & uSDHC_WRITE_PROTECTED));

    /* Wait for the card's buffer to be not full to write to improve the write performance. */
    while (!(uSDHC_DRV_GetPresentStatusFlags(INST_USDHC1) & uSDHC_DATA0_LINE_LEVEL))
    {
    }

    /* wait last write complete */
    EU_ASSERT((common_status_t)STATUS_SUCCESS == SDMMC_WaitWriteComplete(card->host.instance, card->host.transfer, card->relativeAddress));

    /* send write cmd */
    data.enableAutoCMD12 = true;
    data.blockSize = T_uSDHC_BLOCKSIZE_INDIVISIBLE_BY_4;
    data.blockCount = T_uSDHC_SINGLE_BLOCK;
    data.txData = (uint32_t *)g_dataWrite;
    command.index = aSDMMC_WriteSingleBlock;
    command.argument = blockAddress;
    command.responseType = uSDHC_RESPONSE_TYPE_R1;
    content.command = &command;
    content.data = &data;
    EU_ASSERT(STATUS_ERROR == uSDHC_DRV_TransferBlocking(INST_USDHC1, &content, T_uSDHC_TIMEOUT));

    /* De-initialize uSDHC module */
    (void)uSDHC_DeInit();
}

#ifdef __cplusplus
}
#endif

/** @} */
