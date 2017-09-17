/**HEADER********************************************************************
* Copyright (c) Freescale Semiconductor, Inc. All rights reserved.
* 
* Freescale Semiconductor, Inc.
* Proprietary & Confidential
* 
* This source code and the algorithms implemented therein constitute
* confidential information and may comprise trade secrets of Freescale Semiconductor, Inc.
* or its associates, and any use thereof is subject to the terms and
* conditions of the Confidential Disclosure Agreement pursual to which this
* source code was originally received.
*****************************************************************************
* $FileName: mem_management.h$
* $Version : 3.8.1.0$
* $Date    : Sept-12-2011$
*
* Comments: Memory management and profiling for WL Module 
*END************************************************************************/
#ifndef _mem_management_h_
#define _mem_management_h_


#define _mm_internal_alloc            malloc
#define _mm_internal_free             free
#define _mm_internal_zero(a, b)       memset(a, 0, b)

typedef uint32_t _mem_size;
#define MQX_INVALID_POINTER -1
#define MQX_OK  0

#define FALSE ((bool)0)
#define TRUE ((bool)1)

#define _PTR_ *

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern void * mm_alloc(_mem_size request_size, const char * file_name, 
    int file_loc, bool isZero, bool is_from_operator);
    extern uint32_t mm_free(void * buf);
    extern void mm_display(void);
    extern void mm_display_unfree(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#ifdef __cplusplus
#if defined(__IAR_SYSTEMS_ICC__) || defined(__CC_ARM) // TODO: IAR or KEIL
typedef unsigned int size_t;
#else
typedef _mem_size size_t;
#endif

void * operator new (size_t size, const char *fname, int floc);
void * operator new[] (size_t size, const char *fname, int floc);
void operator delete (void *p);
void operator delete[] (void *p);

#endif /* __cplusplus */

#endif /* _mem_management_h_ */

/* EOF */
