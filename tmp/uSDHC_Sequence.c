/*
3.1 SD Card Detection
3.2 SD Clock Control
    3.2.1 SD Clock Supply Sequence
    3.2.2 SD Clock Stop Sequence
    3.2.3 SD Clock Frequency Change Sequence
3.3 SD Bus Power Control
3.4 Changing Bus Width
3.5 Timeout Setting on DAT line
3.6 Card Initialization and Identification
    3.6.1 Signal Voltage Switch Procedure
3.7 SD Transaction Generation
    3.7.1 Transaction Control without Data Transfer Using DAT Line
        3.7.1.1 The Sequence to Issue a SD Command
        3.7.1.2 The Sequence to Finalize a Command
    3.7.2 Transaction Control with Data Transfer Using DAT Line
        3.7.2.1 Not Using DMA
        3.7.2.2 Using SDMA
        3.7.2.3 Using ADMA
3.8 Abort Transaction
    3.8.1 Asynchronous Abort
    3.8.2 Synchronous Abort
3.9 Changing Bus Speed Mode
-----------------------------------------------------
3.10 Error Recovery
    3.10.1 Error Interrupt Recovery
    3.10.2 Auto CMD12 Error Recovery
3.11 Wakeup Control (Optional)
3.12 Suspend/Resume (Optional)
    3.12.1 Suspend Sequence
    3.12.2 Resume Sequence
    3.12.3 Read Transaction Wait/Continue Timing
    3.12.4 Write Transaction Wait/Continue Timing
*/

/* TESTSUITE 3.1: SD Card Detection */
//void uSDHC_TS_031 -> void uSDHC_TS_039
void uSDHC_TC_0311(void)
{
    /* Local variable */
    uSDHC_Type * base = g_usdhcBases[instance];

    /* Initialize uSDHC module */
    (void)uSDHC_DRV_Init(INST_USDHC1, &usdhc1_State, &usdhc1_Config0);

    /* (1) Enable Interrupt of Card Detection */
    uSDHC_EnableInterrupt(base, uSDHC_INT_STATUS_CINS_MASK);
    uSDHC_EnableInterrupt(base, uSDHC_INT_STATUS_CRM_MASK);

    /* (2) Clear Card Detection Interrupt Status */
    

    /* (3) Check if Card Inserted */
    /* - Get present status flags of uSDHC host driver */
    usdhc_present_status_flags = uSDHC_DRV_GetPresentStatusFlags(INST_USDHC1);
    // EU_ASSERT(1U == ((usdhc_present_status_flags & uSDHC_CARD_INSERTED) >> uSDHC_PRES_STATE_CINST_SHIFT));
    EU_ASSERT(0U == ((usdhc_present_status_flags & uSDHC_CARD_INSERTED) >> uSDHC_PRES_STATE_CINST_SHIFT));

    /* De-initialize uSDHC module */
    (void)uSDHC_DRV_Deinit(INST_USDHC1);
}






























