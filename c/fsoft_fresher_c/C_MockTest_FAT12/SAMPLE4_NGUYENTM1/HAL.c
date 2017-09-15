#include "HAL.h"
#include <stdio.h>

/*******************************************************************************
 * Variables
 ******************************************************************************/
FILE *file;

/*******************************************************************************
 * Codes
 ******************************************************************************/

/*read a sector*/
uint32_t kmc_read_sector(unsigned long index, unsigned char *buff)
{
    /*specify position of wanted sector*/
    unsigned long ReadPosition;
    /*open file and enable to read and write*/
    file = fopen("floppy.img", "rb");

    /*if inputs are not satisfied*/
    if(file==NULL||index<0||buff==NULL)
    {
        return 1;
    }

    /*if inputs are valid*/
    /*1 sector = 512 bytes so index sector = index * 512 bytes*/
    ReadPosition = index << ShiftByte;

    /*move to wanted position*/
    fseek(file, ReadPosition, SEEK_SET);

    /*read bytes of sector to buff*/
    fread(buff, sizeof(unsigned char), SectorRange, file);

    /*close file*/
    fclose(file);

    /*return number's bytes of sector*/
    return SectorRange;
}


/*read multiple sectors*/
uint32_t kmc_read_multi_sector(unsigned long index, uint32_t num, unsigned char *buff)
{
    /*specify position of wanted sector*/
    unsigned long ReadPosition;

    /*specify number of bytes to read*/
    unsigned long ByteNumber;

    /*open file and enable to read and write*/
    file = fopen("floppy.img", "rb");

    /*if inputs are not satisfied*/
    if(file==NULL||index<0||buff==NULL||num<0)
    {
        return 1;
    }

    /*1 sector = 512 bytes so index sector = index * 512 bytes*/
    ReadPosition = index << ShiftByte;

    /*the number of byte coresponds to the number of sector*/
    ByteNumber = num << ShiftByte;

    /*move to wanted position*/
    fseek(file, ReadPosition, SEEK_SET);

    /*read bytes of sector to buff*/
    fread(buff, sizeof(unsigned char), ByteNumber, file);

    /*close file*/
    fclose(file);

    /*return number's bytes of sector*/
    return ByteNumber;
}
