/**
*   Copyright 2018 NXP
*   ALL RIGHTS RESERVED.
*   @file Usdhc_TC_0125.c
*
*   @brief   Test case 0125.
*   @details Function test case 0125.
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
#include "Usdhc_TC_0125.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


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
* @test_id        Usdhc_TC_0125
* @brief          Transfer (write read cmd) multiple blocks with AutoCMD12 false and send CMD12 manually using nonblocking.
* @details        This test case transfers (write/read) multiple blocks with enableAutoCMD12 false.
                  Multiple block transfers for memory require a CMD12 to stop the transaction,
                  with AutoCMD12 disabled, a CMD12 is issued manually to stop transmission.
* @pre            N/A
* @post           N/A
*
* @test_level     ComponentValidation
* @test_type      Functional
* @test_technique WhiteBox
* @test_procedure Steps:
*                     -# Initialize the uSDHC middle-ware module with card by calling uSDHC_Init()
*                     -# Verification point:
*                        - initialize uSDHC returns STATUS_SUCCESS
*                     -# Prepare data for writing to card
*                     -# Prepare data by erasing before reading from card
*                     -# Write multiple blocks data to card from block start
*                     -# - Check readonly card
*                     -# Verification point:
*                        - WRITE PROTECTED bit is set correctly in PRES_STATE
*                     -# - Wait for card buffer not full
*                     -# - Wait last write complete
*                     -# Verification point:
*                        - SDMMC_WaitWriteComplete function returns STATUS_SUCCESS
*                     -# - Configure command and data to be send (AutoCMD12 false, Multi blocks)
*                     -# - Send write cmd using transfer non-blocking
*                     -# Verification point:
*                        - uSDHC_DRV_Transfer function returns STATUS_SUCCESS
*                     -# Wait 2ms
*                     -# Send CMD12 aSDMMC_StopTransmission with response R1b to stop transmission
*                     -# Verification point:
*                        - Transfer CMD12 returns STATUS_SUCCESS
*                     -# Read multiple blocks data from card from block start
*                     -# - Wait last write complete
*                     -# Verification point:
*                        - SDMMC_WaitWriteComplete function returns STATUS_SUCCESS
*                     -# - Configure command and data to be send (AutoCMD12 false, Multi blocks)
*                     -# - Send read cmd using transfer non-blocking
*                     -# Verification point:
*                        - uSDHC_DRV_Transfer function returns STATUS_SUCCESS
*                     -# Wait 2ms
*                     -# Send CMD12 aSDMMC_StopTransmission with response R1b to stop transmission
*                     -# Verification point:
*                        - Transfer CMD12 returns STATUS_SUCCESS
*                     -# Compare content of read data with written data in the multiple blocks
*                     -# Verification point:
*                        - memory in multiple blocks should be matched between read result and writing operation
*                     -# De-initialize the uSDHC middle-ware module with card by calling uSDHC_DeInit()
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

void Usdhc_TC_0125(void)
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

    /* prepare by erasing data before reading */
    (void)memset(g_dataRead, T_uSDHC_ERASED_DATA, T_uSDHC_SINGLE_BLOCK*DATA_DEFAULT_BLOCK_SIZE);

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
    data.enableAutoCMD12 = false;
    data.blockSize = DATA_DEFAULT_BLOCK_SIZE;
    data.blockCount = T_uSDHC_MULTI_BLOCKS;
    data.txData = (uint32_t *)g_dataWrite;
    command.index = aSDMMC_WriteMultipleBlock;
    command.argument = blockAddress;
    command.responseType = uSDHC_RESPONSE_TYPE_R1;
    content.command = &command;
    content.data = &data;
    EU_ASSERT((status_t)STATUS_SUCCESS == uSDHC_DRV_Transfer(INST_USDHC1, &content));

    /* This delay is necessary before other cmd send */
    OSIF_TimeDelay(2U);

    /* send cmd12 aSDMMC_StopTransmission */
    command.index = aSDMMC_StopTransmission;
    command.argument = 0U;
    command.responseType = uSDHC_RESPONSE_TYPE_R1b;
    content.command = &command;
    content.data = NULL;
    EU_ASSERT((status_t)STATUS_SUCCESS == uSDHC_DRV_Transfer(INST_USDHC1, &content));

    /* This delay is necessary before other cmd send */
    OSIF_TimeDelay(2U);

    /* READ DATA FROM CARD
     * - Wait Last Write Complete
     * - Send Read CMD
     */
    /* wait last write complete */
    EU_ASSERT((common_status_t)STATUS_SUCCESS == SDMMC_WaitWriteComplete(card->host.instance, card->host.transfer, card->relativeAddress));

    /* send read cmd */
    data.enableAutoCMD12 = false;
    data.blockSize = DATA_DEFAULT_BLOCK_SIZE;
    data.blockCount = T_uSDHC_MULTI_BLOCKS;
    data.rxData = (uint32_t *)g_dataRead;
    command.index = aSDMMC_ReadMultipleBlock;
    command.argument = blockAddress;
    command.responseType = uSDHC_RESPONSE_TYPE_R1;
    content.command = &command;
    content.data = &data;
    EU_ASSERT((status_t)STATUS_SUCCESS == uSDHC_DRV_Transfer(INST_USDHC1, &content));

    /* This delay is necessary before other cmd send */
    OSIF_TimeDelay(2U);

    /* send cmd12 aSDMMC_StopTransmission */
    command.index = aSDMMC_StopTransmission;
    command.argument = 0U;
    command.responseType = uSDHC_RESPONSE_TYPE_R1b;
    content.command = &command;
    content.data = NULL;
    EU_ASSERT((status_t)STATUS_SUCCESS == uSDHC_DRV_Transfer(INST_USDHC1, &content));

    /* This delay is necessary before other cmd send */
    OSIF_TimeDelay(2U);

    /* Verification point: Compare memory read and write */
    EU_ASSERT(0U == memcmp(g_dataRead, g_dataWrite, (T_uSDHC_MULTI_BLOCKS*DATA_DEFAULT_BLOCK_SIZE)));

    /* De-initialize uSDHC module */
    (void)uSDHC_DeInit();
}

#ifdef __cplusplus
}
#endif

/** @} */
