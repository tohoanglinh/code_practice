/*****************************************************************************
* Copyright 2016 NXP
*****************************************************************************/

/**
*
* @file testMenu.h
*
* @author 
*
* @date 
*
* @brief 
*
*
******************************************************************************/

/*****************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "test_menu.h"

/*****************************************************************************
* DEFINES
*****************************************************************************/

/*****************************************************************************
* TYPE DEFINITIONS
*****************************************************************************/

/*****************************************************************************
* INTERNAL TYPE DEFINITIONS
*****************************************************************************/

/*****************************************************************************
* EXPORTED VARIABLES
*****************************************************************************/

/*****************************************************************************
* INTERNAL VARIABLES
*****************************************************************************/
void test_menu_display(menu_item_t *menu, uint8_t size);

/* main menu */
void shortCommandMenuFunction(void);
void extReadCommandMenuFunction(void);
void extWriteCommandMenuFunction(void);

/* short command menu */
void NopCommandTestMenuFunction(void);
void setModeControlTestMenuFunction(void);

void NopCommandTestCase1(void);
void NopCommandTestCase2(void);

void exitMenuFunction(void);

/*****************************************************************************
* INTERNAL FUNCTION DECLARATIONS
*****************************************************************************/
menu_item_t mainMenu[] = 
{
    {shortCommandMenuFunction, "Short command menu"},
    {extReadCommandMenuFunction, "Extended read command menu"},
    {extWriteCommandMenuFunction, "Extended write command menu"},
    {exitMenuFunction,"Exit"}
};

menu_item_t shortCommandMenu[] = 
{
    {NopCommandTestMenuFunction, "NOP command"},
    {setModeControlTestMenuFunction, "SetModeControl command"},
    {exitMenuFunction,"Exit"}
};

menu_item_t NopCommandTestMenu[] = 
{
    {NopCommandTestCase1, "NOP command test case 1"},
    {NopCommandTestCase2, "NOP command test case 2"},
    {exitMenuFunction,"Exit"}
};

bool exitMenu = false;
/*****************************************************************************
* FUNCTIONS
*****************************************************************************/
void shortCommandMenuFunction(void)
{
    PRINTF("\r\nshortCommandMenu\n\r\n");
    do {
        test_menu_display(shortCommandMenu, sizeof(shortCommandMenu)/sizeof(menu_item_t));
    } while (false == exitMenu);
    exitMenu = false;
}

void extReadCommandMenuFunction(void)
{
    PRINTF("\r\nextReadCommandMenu\n\r\n");
}

void extWriteCommandMenuFunction(void)
{
    PRINTF("\r\nextWriteCommandMenu\n\r\n");
}

void NopCommandTestMenuFunction(void)
{
    PRINTF("\r\nNopCommandTestMenu\n\r\n");
    do {
        test_menu_display(NopCommandTestMenu, sizeof(NopCommandTestMenu)/sizeof(menu_item_t));
    } while (false == exitMenu);
    exitMenu = false;
}

void setModeControlTestMenuFunction(void)
{
    PRINTF("\r\nsetModeControlTestMenu\n\r\n");
}

void NopCommandTestCase1(void)
{
    PRINTF("\r\nNopCommandTestCase1\n\r\n");
}

void NopCommandTestCase2(void)
{
    PRINTF("\r\nNopCommandTestCase2\n\r\n");
}

void exitMenuFunction(void)
{
    PRINTF("\r\nexitMenu\n\r\n");
    exitMenu = true;
}

void test_menu_display(menu_item_t *menu, uint8_t size)
{
    uint8_t choice, ch;
    uint8_t i;

    PRINTF("\r\nSelect the desired operation\n\r\n");

    choice = 'a';
    for (i=0; i< size; i++)
    {
        PRINTF("\r\n%c. %s", choice++, menu[i].menu_description);
    }
    
    fflush(stdin);
    ch = GETCHAR();
   
    choice = ch - 'a';
    if(choice >= size)
    {
        printf("\r\nThis option is not supported. Please select other ...");
    }
    else
    {
        if(menu[choice].menu_function != NULL)
        {
            menu[choice].menu_function();
        }
    }
}

void main_menu_display(void)
{
    test_menu_display(mainMenu, sizeof(mainMenu)/sizeof(menu_item_t));
}
