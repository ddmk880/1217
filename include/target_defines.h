/*============================================================================*
 * FILE:                   T A R G E T _ D E F I N E S . H
 *============================================================================*
 *
 * COPYRIGHT (C) 1994 - 2004 BY
 *          CONDOR ENGINEERING, INC., SANTA BARBARA, CALIFORNIA
 *          ALL RIGHTS RESERVED.
 *
 *          THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND
 *          COPIED ONLY IN ACCORDANCE WITH THE TERMS OF SUCH LICENSE AND WITH
 *          THE INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR ANY
 *          OTHER COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE
 *          AVAILABLE TO ANY OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF THE
 *          SOFTWARE IS HEREBY TRANSFERRED.
 *
 *          THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT
 *          NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY CONDOR
 *          ENGINEERING.
 *
 *===========================================================================*
 *
 * FUNCTION:    Targer specific header file for BusTools API structures.
 *              Busapi.h includes this file.  Use this file to customize the
 *              installation for new targets.
 *
 *===========================================================================*/

/* $Revision:  5.05 Release $
   Date        Revision
  ----------   ---------------------------------------------------------------
  09/12/2001    Target_def.h added to the Busapi.h file
  01/31/2002    Update for modular API
  06/05/2002    Update for v4.52 release

******************************************************************************/
#define MAX_BTA   16    /* 16 1553 Channel on up to 16 boards are supported */

// Set common definition for Windows 32 bit environment
// Microsoft uses WIN32, Borland uses __WIN32__
#if defined(_WIN32) || defined(WIN32) /* MSVC for 32-bit WINDOWS PM  */
 #ifndef __WIN32__
 #define __WIN32__      /* This label is used in the API source code  */
 #endif
 #ifndef _Windows
 #define _Windows
 #endif
#endif

/************************************************************************************
 * Target defines for 32-Bit Windows for all supported 1553 boards                  *
 *                                                                                  *
*************************************************************************************/
#if defined(__WIN32__)    /*                                                        */
  #include <windows.h>    /*                                                        */
  #define WIN32_LEAN_AND_MEAN /*                                                    */
  #define INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME             */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #define HW_INTERRUPTS   /* Include HW interrupt code in 32-bit Windows            */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #define DEMO_CODE       /* Include the DEMO version of the API                    */
  #undef ADD_TRACE        /* Include the function call trace code                   */
  #define DO_BUS_LOADING  /* Include the bus loading code                           */
  #define _USER_INIT_     /*                                                        */
  #define _LABVIEW_       /*                                                        */
  #undef _LVRT_           /*                                                        */
  #define _USER_DLL_      /*                                                        */
  #define _PLAYBACK_      /*                                                        */
  #define INCLUDE_IP_1553 /*                                                        */
  #define INCLUDE_VME_1553/*                                                        */
  #define INCLUDE_VXI_1553/*                                                        */
  #define INCLUDE_PCCD    /* Include the dual channel PCCard-D1553                  */
  #define __uint64 unsigned __int64 /*                                              */
  #define LocalMalloc GlobalAlloc   /*                                              */
  #define LocalFree   GlobalFree    /*                                              */
  #define CCONV     _stdcall /*                                                     */
  #define NOMANGLE        /*                                                        */
  #define PACKED          /*                                                        */
  #define PRAGMA_PACK     /*  local pack directive                                  */
#endif                    /*                                                        */
/************************************************************************************/

/************************************************************************************
 * Target defines for Linux running for the PCI-1553, PMC-1553 and the cPCI-1553.   *
 * Also use this for the PCI-1553-IP.                                               */
/************************************************************************************/
#if defined(_LINUX_X86_)  /*                                                        */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _LINUXBOARDSETUP/*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #undef _PLAYBACK_       /*                                                        */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #define HW_INTERRUPTS   /* Exclude HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef DEMO_CODE        /* Exclude the DEMO version of the API                    */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef DO_BUS_LOADING   /* Exclude the bus loading code                           */
  #undef _USER_INIT_      /*                                                        */
  #undef _LABVIEW_        /*                                                        */
  #undef _USER_DLL_       /*                                                        */
  #define _PLAYBACK_      /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #define INCLUDE_PCCD    /*                                                        */
  #include <unistd.h>     /*                                                        */
  #include <string.h>     /*                                                        */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
  int linux_irq_setup(unsigned int,int,int);/*                                      */
#endif /* end _LINUX_X86_                                                           */
/************************************************************************************/

/************************************************************************************
 * Target defines for Linux running for the PCI-1553, PMC-1553 and the cPCI-1553.   *
 * Also use this for the PCI-1553-IP.                                               */
/************************************************************************************/
#if defined(_LINUX_X86_VME_)  /*                                                    */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _LINUXVMEBOARDSETUP/*                                                     */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #undef HW_INTERRUPTS    /* Exclude HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef DEMO_CODE        /* Exclude the DEMO version of the API                    */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef DO_BUS_LOADING   /* Exclude the bus loading code                           */
  #undef _USER_INIT_      /*                                                        */
  #undef _LABVIEW_        /*                                                        */
  #undef _USER_DLL_       /*                                                        */
  #undef _PLAYBACK_       /*                                                        */
  #define INCLUDE_VME_1553/*                                                        */
  #undef INCLUDE_PCCD     /*                                                        */
  #include <unistd.h>     /*                                                        */
  #include <string.h>     /*                                                        */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
  int linux_irq_setup(unsigned int,int,int);/*                                      */
#endif /* end _LINUX_X86_                                                           */
/************************************************************************************/

/************************************************************************************
 * Target defines for Solaris SPARC running for the PCI-1553, PMC-1553 and the      *
 *  cPCI-1553.                                                                      */
/************************************************************************************/
#if defined(_SOLARIS_SPARC_)/*                                                      */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _SOLARISBOARDSETUP/*                                                      */
  #undef INCLUDE_IP_1553  /* Exclude IP-1553 support                                */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define REGISTERFUNCTION/*                                                        */
  #undef _PLAYBACK_       /*                                                        */
  #define  HW_INTERRUPTS  /* Exclude HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #undef  WORD_SWAP       /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
#endif /* end _SOLARIS_SPARC_                                                       */
/************************************************************************************/

/************************************************************************************
 * Target defines for Solaris SPARC running for the PCI-1553, PMC-1553 and the      *
 *  cPCI-1553. FORTE COMPILER (NATIVE SUN)                                          */
/************************************************************************************/
#if defined(_SOLARIS_FORTE_)/*                                                      */
#pragma pack(2)         /* Two byte alignment                                       */
#include <pthread.h>    /* pthread for H/W Interrupts                               */
#define _UNIX_          /*                                                          */
#define _FORTE_         /* Using FORTE compiler                                     */
#undef _Windows         /*                                                          */
#undef __WIN32__        /*                                                          */
#define _SOLARISBOARDSETUP/*                                                        */
#undef INCLUDE_IP_1553  /* Exclude IP-1553 support                                  */
#undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME                */
#define REGISTERFUNCTION/*                                                          */
#define  HW_INTERRUPTS  /* Exclude HW interrupt code                                */
#define FILE_SYSTEM     /* Include Dump and memory test output functions            */
#undef  DEMO_CODE       /* Exclude the DEMO version of the API                      */
#define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                                */
#define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)               */
#undef  WORD_SWAP       /* define the flipw macro                                   */
#undef  ADD_TRACE       /* Exclude the function call trace code                     */
#undef  DO_BUS_LOADING  /* Exclude the bus loading code                             */
#define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                            */
#endif /* end _SOLARIS_SPARC_                                                       */
/************************************************************************************/

/************************************************************************************
 * Target defines for Solaris x86 running for the PCI-1553, PMC-1553 and the        *
 *  cPCI-1553.                                                                      */
/************************************************************************************/
#if defined(_SOLARIS_X86_)/*                                                        */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #include <pthread.h>    /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _SOLARISBOARDSETUP/*                                                      */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS   /* Exclude HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE      /* Exclude the DEMO version of the API                     */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
#endif /* end _SOLARIS_X86_                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks x86 BSP for the PCI-1553, PMC-1553 and the cPCI-1553. *
 * Also use this for the PCI-1553-IP.                                               *
 ************************************************************************************/
#if defined (VXW_PCI_X86) || defined (VXW_QPCI_X86) || defined (VXW_QCP_X86) || defined (VXW_Q104_X86)
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _X86BOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #undef REGISTERFUNCTION /*                                                        */
  #define HW_INTERRUPTS    /* Exclude HW interrupt code                             */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #undef INCLUDE_IP_1553 /*                                                         */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) taskDelay(p1/10+1) /* define the Sleep function                 */
#endif   /* end VXW-PCI-X86                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks x86 BSP for the VME-1553 and VME-1553-IP.             *
 ************************************************************************************/
#if defined (VXW_VME_X86) /*                                                        */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _VMEBOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS   /* Exclude HW interrupt code                              */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define INCLUDE_IP_1553 /*                                                        */
  #define INCLUDE_VME_1553/*                                                        */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) taskDelay(p1/10+1) /* define the Sleep function                 */
#endif   /* end VXW-PCI-X86                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks PowerPC BSP for the VME-1553 and                      *
 * VME-1553-IP on either the ACROMAG or GreenSpring carrier.                        */
/************************************************************************************/
#if defined (VXW_VME_PPC) /* For use with MVME-2xxx and related processor with the  */
  #define _UNIX_          /* VME Bus.                                               */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _VMEBOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS   /* Exclude HW interrupt code                              */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #define INCLUDE_VME_1553/* Include the support for the VME-1553                   */
  #define  INCLUDE_IP_1553/* Include the support for the VME-1553                   */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #undef ADD_TRACE       /* Exclude the function call trace code                    */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) sysUsDelay(p1*1000) /* Define the Sleep function                */
#endif   /* end VXW-VME-PPC                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks PowerPC BSP for the VME-1553 and                      *
 * VME-1553-IP on either the ACROMAG or GreenSpring carrier.                        */
/************************************************************************************/
#if defined (INTEGRITY_VME_PPC) /* For use with PPC and related processor with the  */
  #define _UNIX_          /* VME Bus.                                               */
  #undef _GCC_            /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _VMEBOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #undef HW_INTERRUPTS    /* Exclude HW interrupt code                              */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #define INCLUDE_VME_1553/* Include the support for the VME-1553                   */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #undef ADD_TRACE       /* Exclude the function call trace code                    */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) usleep(p1*1000) /* Define the Sleep function                    */
#endif   /* end VXW-VME-PPC                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks PowerPC BSP for the VME-1553 and                      *
 * VME-1553-IP on either the ACROMAG or GreenSpring carrier.                        */
/************************************************************************************/
#if defined (VXW_VME_SYNERGY) /* For use with Synergy PowerPC processor with the    */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _VMEBOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS    /* Exclude HW interrupt code                             */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #define INCLUDE_VME_1553/* Include the support for the VME-1553                   */
  #define  INCLUDE_IP_1553/* Include the support for the VME-1553                   */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #undef ADD_TRACE       /* Exclude the function call trace code                    */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) taskDelay(p1/10+1)  /* Define the Sleep function                */
#endif   /* end VXW-VME-PPC                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks Motorola 68K BSP for the VME-1553 and                 *
 * VME-1553-IP on either the ARCROMAG or GreenSpring carrier.                       */
/************************************************************************************/
#if defined (VXW_VME_68K) /* Use for Motorola 68K with VMEbus                       */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _VMEBOARDSETUP  /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #undef HW_INTERRUPTS    /* Exclude HW interrupt code                              */
  #undef REGISTERFUNCTION /* Exclude Register Function interrupts                   */
  #undef _WIN16_INTERRUPTS_/* Exclude Windowss 3.1 interrupts                       */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define INCLUDE_VME_1553/* Include the support for the VME-1553                   */
  #define INCLUDE_IP_1553 /* Include the support for the VME-1553                   */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) taskDelay(p1/10+1) /* Define the Sleep function                 */
#endif   /* end VXW-VME-68K                                                         */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks PowerPC or QPMC-1553 PMC-1553  or cPCI-1553           *
/************************************************************************************/
#if defined(VXW_PCI_PPC) || defined (VXW_PCI_THALES) /*                             */
  #ifndef VXW_PCI_PPC     /*                                                        */                                                
     #define VXW_PCI_PPC  /*                                                        */
  #endif                  /*                                                        */                           
  #define _UNIX_          /* For use with the PMC or PCI bus                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _PCIBOARDSETUP  /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS    /* Exclude HW interrupt code                             */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #define  WORD_SWAP      /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) sysUsDelay(p1*1000) /* Define the Sleep function                */
#endif   /* end VXW-PCI-PPC or VXW_PCI_THALES                                       */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks for MCP-750 QcP-1553                                  * 
/************************************************************************************/
#if defined(VXW_MCP750_PPC)  /* Use this for the MCP-750                            */
  #define VXW_PCI_PPC     /*                                                        */
  #define _UNIX_          /* For use with the PMC or PCI bus                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _PCIBOARDSETUP  /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define HW_INTERRUPTS    /* Exclude HW interrupt code                             */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #define  WORD_SWAP      /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) sysMsDelay(p1) /* Define the Sleep function                     */
#endif   /* end VXW_MCP750_PPC                                                      */
/************************************************************************************/

/************************************************************************************
 * Target Defines for VxWorks for MCP-750 QcP-1553                                  * 
/************************************************************************************/
#if defined(VXW_DY4_PCI_PPC)  /* Use this for the Dy4 PowerPC                       */
  #define VXW_PCI_PPC     /*                                                        */
  #define _UNIX_          /* For use with the PMC or PCI bus                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #define VXWORKS         /*                                                        */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _PCIBOARDSETUP  /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #undef HW_INTERRUPTS    /* Exclude HW interrupt code                              */
  #undef FILE_SYSTEM      /* Include Dump and memory test output functions          */
  #undef  DEMO_CODE       /* Exclude the DEMO version of the API                    */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #define  WORD_SWAP      /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef  DO_BUS_LOADING  /* Exclude the bus loading code                           */
  #define Sleep(p1) taskDelay(p1/10+1) /* Define the Sleep function                 */
#endif   /* end VXW_DY4_PCI_PPC                                                     */
/************************************************************************************/


/************************************************************************************
 * Target defines for QNX Neutrino for the PCI                                      *
 *                                                                                  */
/************************************************************************************/
#if defined(_QNXNTO_PCI_X86_)     /*                                                */
  #define _QNXNTO_        /*                                                        */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _LINUXBOARDSETUP/*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #define HW_INTERRUPTS   /* Include HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef DEMO_CODE        /* Exclude the DEMO version of the API                    */
  #undef  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                               */
  #undef  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)              */
  #undef  WORD_SWAP       /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef DO_BUS_LOADING   /* Exclude the bus loading code                           */
  #undef _USER_INIT_      /*                                                        */
  #undef _LABVIEW_        /*                                                        */
  #undef _USER_DLL_       /*                                                        */
  #undef _PLAYBACK_       /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #include <unistd.h>     /*                                                        */
  #include <string.h>     /*                                                        */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
  int linux_irq_setup(unsigned int,int,int);/*                                      */
#endif /* end _QNXNTO_                                                              */
/************************************************************************************/

/************************************************************************************
 * Target defines for QNX Neutrino for the QPMC-1553 on PowerPC                     *
 *                                                                                  */
/************************************************************************************/
#if defined(_QNXNTO_PCI_PPC_)     /*                                                */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _QNXNTO_        /*                                                        */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _LINUXBOARDSETUP/*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #define HW_INTERRUPTS   /* Include HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef DEMO_CODE        /* Exclude the DEMO version of the API                    */
  #define NON_INTEL_BIT_FIELDS  /* Non Intel Bit Ordering                           */
  #define NON_INTEL_WORD_ORDER  /* Non Intel Word Ordering (Little Endian)          */
  #define  WORD_SWAP      /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef DO_BUS_LOADING   /* Exclude the bus loading code                           */
  #undef _USER_INIT_      /*                                                        */
  #undef _LABVIEW_        /*                                                        */
  #undef _USER_DLL_       /*                                                        */
  #undef _PLAYBACK_       /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #undef INCLUDE_VME_1553 /*                                                        */
  #include <unistd.h>     /*                                                        */
  #include <string.h>     /*                                                        */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
  int linux_irq_setup(unsigned int,int,int);/*                                      */
#endif /* end _QNXNTO_PCI_PPC_                                                      */
/************************************************************************************/

/************************************************************************************
 * Target defines for QNX Neutrino for the QPMC-1553 on PowerPC                     *
 *                                                                                  */
/************************************************************************************/
#if defined(_QNXNTO_VME_PPC_)     /*                                                */
  #define _QNXNTO_        /*                                                        */
  #include <pthread.h>    /* pthread for H/W Interrupts                             */
  #define _UNIX_          /*                                                        */
  #define _GCC_           /* Using GCC compiler                                     */
  #undef _Windows         /*                                                        */
  #undef __WIN32__        /*                                                        */
  #define _LINUXBOARDSETUP/*                                                        */
  #undef INCLUDE_VMIC     /* 32-bit Windows code supports the VMIC VME              */
  #define REGISTERFUNCTION/* Use the RegisterFunction Interrupt Handling            */
  #define HW_INTERRUPTS   /* Include HW interrupt code                              */
  #define FILE_SYSTEM     /* Include Dump and memory test output functions          */
  #undef DEMO_CODE        /* Exclude the DEMO version of the API                    */
  #define NON_INTEL_BIT_FIELDS  /* Non Intel Bit Ordering                           */
  #define NON_INTEL_WORD_ORDER  /* Non Intel Word Ordering (Little Endian)          */
  #undef  WORD_SWAP       /* define the flipw macro                                 */
  #undef  ADD_TRACE       /* Exclude the function call trace code                   */
  #undef DO_BUS_LOADING   /* Exclude the bus loading code                           */
  #undef _USER_INIT_      /*                                                        */
  #undef _LABVIEW_        /*                                                        */
  #undef _USER_DLL_       /*                                                        */
  #define _PLAYBACK_      /*                                                        */
  #undef INCLUDE_IP_1553  /*                                                        */
  #define INCLUDE_VME_1553/*                                                        */
  #include <unistd.h>     /*                                                        */
  #include <string.h>     /*                                                        */
  #define Sleep(p1) usleep(p1*1000) /* Define Sleep marcro                          */
  #undef _PLAYBACK_       /*                                                        */
  int linux_irq_setup(unsigned int,int,int);/*                                      */
#endif /* end _QNXNTO_VME_PPC_                                                      */
/************************************************************************************/

/************************************************************************************
 * Target Defines on LynxOS PowerPC for the QVME-1553 and VME-1553                  */ 
/************************************************************************************/
#if defined(LYNXOS_VME_PPC)  /*                                                     */
  #define  LYNXOS	     /*							    */
  #define  _UNIX_            /*                                                     */
  #define  _GCC_             /* Using GCC compiler                                  */
  #define  INCLUDE_VME_1553  /*                                                     */
  #define  REGISTERFUNCTION  /* Include/Exclude Register Function interrupts        */
  #define  HW_INTERRUPTS     /* Include/Exclude HW interrupt code                   */
  #define  _LYNXOSBOARDSETUP /*                                                     */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #define  FILE_SYSTEM       /* Include Dump and memory test output functions       */
  #undef   VXWORKS           /*                                                     */
  #undef   _Windows          /*                                                     */
  #undef   __WIN32__         /*  	                                            */
  #undef   INCLUDE_IP_1553   /*                                                     */
  #undef   INCLUDE_VMIC      /*                                                     */
  #undef   DEMO_CODE         /* Exclude the DEMO version of the API                 */
  #undef   WORD_SWAP         /* undefine the flipw macro                            */
  #undef   ADD_TRACE         /* Exclude the function call trace code                */
  #undef   DO_BUS_LOADING    /* Exclude the bus loading code                        */
  #define  Sleep(p1) usleep(p1*1000) /* Define the Sleep function                   */
  #include <pthread.h>       /* pthread for H/W Interrupts                          */
#endif   /* end (LYNXOS_VME_PPC)                                                    */
/************************************************************************************/

/************************************************************************************
 * Target Defines on LynxOS PowerPC for the QPMC-1553 and PMC-1553                  */ 
/************************************************************************************/
#if defined(LYNXOS_PMC_PPC)  /*                                                     */
  #define  LYNXOS	     /*	                                                    */
  #define  _UNIX_            /*                                                     */
  #define  _GCC_             /* Using GCC compiler                                  */
  #define  REGISTERFUNCTION  /* Include/Exclude Register Function interrupts        */
  #define  HW_INTERRUPTS     /* Include/Exclude HW interrupt code                   */
  #define  _LYNXOSBOARDSETUP /*                                                     */
  #define  NON_INTEL_BIT_FIELDS  /* Intel Bit Ordering                              */
  #define  NON_INTEL_WORD_ORDER  /* Intel Word Ordering (Little Endian)             */
  #define  FILE_SYSTEM       /* Include Dump and memory test output functions       */
  #undef   INCLUDE_VME_1553  /*                                                     */
  #undef   VXWORKS           /*                                                     */
  #undef   _Windows          /*                                                     */
  #undef   __WIN32__         /* 	                                            */
  #undef   INCLUDE_IP_1553   /*                                                     */
  #undef   INCLUDE_VMIC      /*                                                     */
  #undef   DEMO_CODE         /* Exclude the DEMO version of the API                 */
  #define  WORD_SWAP         /* undefine the flipw macro                            */
  #undef   ADD_TRACE         /* Exclude the function call trace code                */
  #undef   DO_BUS_LOADING    /* Exclude the bus loading code                        */
  #define  Sleep(p1) usleep(p1*1000) /* Define the Sleep function                   */
  #include <pthread.h>       /* pthread for H/W Interrupts                          */
#endif   /* end (LYNXOS_PMC_PPC)                                                    */
/************************************************************************************/
  
/************************************************************************************
 * Target Defines on LynxOS x86 for the Q104-1553P, QPCI-1553, and PCI-1553         */
/************************************************************************************/
#if defined(LYNXOS_X86)      /*                                                     */
  #define  LYNXOS	     /*	                                                    */
  #define  _UNIX_            /*                                                     */
  #define  _GCC_             /* Using GCC compiler                                  */
  #define  REGISTERFUNCTION  /* Include/Exclude Register Function interrupts        */
  #define  HW_INTERRUPTS     /* Include/Exclude HW interrupt code                   */
  #define  _LYNXOSBOARDSETUP /*                                                     */
  #define  FILE_SYSTEM       /* Include Dump and memory test output functions       */
  #undef   INCLUDE_VME_1553  /*                                                     */
  #undef   NON_INTEL_BIT_FIELDS /* Intel Bit Ordering                               */
  #undef   NON_INTEL_WORD_ORDER /* Intel Word Ordering (Little Endian)              */
  #undef   VXWORKS           /*                                                     */
  #undef   _Windows          /*                                                     */
  #undef   __WIN32__         /*                                                     */
  #undef   INCLUDE_IP_1553   /*                                                     */
  #undef   INCLUDE_VMIC      /*                                                     */
  #undef   DEMO_CODE         /* Exclude the DEMO version of the API                 */
  #undef   WORD_SWAP         /* undefine the flipw macro                            */
  #undef   ADD_TRACE         /* Exclude the function call trace code                */
  #undef   DO_BUS_LOADING    /* Exclude the bus loading code                        */
  #define  Sleep(p1) usleep(p1*1000) /* Define the Sleep function                   */
  #include <pthread.h>       /* pthread for H/W Interrupts                          */
#endif   /* end (LYNXOS_X86)                                                        */
/************************************************************************************/


/************************************************************************************
 * CVI use the __WIN32__ Block above.  These are modifications to that block to     *
 * allow CVI to compile.                                                            *
*************************************************************************************/
#if defined(_CVI_)
#define NO_ASSEMBLY
#undef  ADD_TRACE
#define  HW_INTERRUPTS
#define  REGISTERFUNCTION
#undef  _WIN16_INTERRUPTS_
#undef  _INTERRUPTS
#undef  _USER_DLL_
#define  _PLAYBACK_
#undef INCLUDE_VMIC
#undef  _USER_INIT_
#define __int64 double long
#endif
/***********************************************************************************/

#if defined(__BORLANDC__) || defined(_UNIX_)
#define _ftime ftime
#define _timeb timeb
#endif

#if defined(__BORLANDC__)
#undef PRAGMA_PACK
#pragma pack(2)
#endif

/************************************************************************
*  Create the standard WINDOWS typedef's if compiling for _UNIX_.
************************************************************************/
#ifdef _UNIX_

#ifdef _GCC_
  #define PACKED __attribute__ ((aligned(2),packed))  /* GCC Compiler Only */
#else
#define PACKED
#endif
 
#define INFINITE 0
#define NO_ASSEMBLY
#define HANDLE int
#define THREAD_PRIORITY_NORMAL 0
#define THREAD_PRIORITY_BELOW_NORMAL 0
#define THREAD_PRIORITY_CRITICAL 0
#define LocalMalloc malloc
#define LocalFree   free
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
#ifndef VXWORKS
typedef unsigned int    UINT;
#endif
typedef int             HWND;
typedef char  * LPSTR;
typedef int   * LPINT;
typedef WORD  * LPWORD;
typedef long  * LPLONG;
typedef DWORD * LPDWORD;
typedef void  * LPVOID;

#ifndef FALSE
#define FALSE           0
#endif
#ifndef TRUE
#define TRUE            1
#endif

#define VOID            void
#define CALLBACK
#define _stdcall
#define CCONV
#define NOMANGLE

#if defined (VXWORKS) | defined (_SOLARIS_SPARC_) | defined (_SOLARIS_X86_) || defined (_SOLARIS_FORTE_) || defined(_QNXNTO_)
#define __int64 long long
#define __uint64 unsigned long long
#else
#define __int64 int64_t               // Is this a long long?
#define __uint64 u_int64_t
#endif

extern DWORD timeGetTime();

#define LARGE_INTEGER __int64
#undef PRAGMA_PACK
#endif

#ifdef DEMO_CODE
#ifdef __WIN32__
  #define MY_GlobalAllocPtr(a,b)  GlobalAlloc(a,b)
  #define MY_GlobalFreePtr(a)     GlobalFree(a)
#else
#define MY_GlobalAllocPtr(a,b)  malloc(b)
#define MY_GlobalFreePtr(a)     free(a)
#endif
#endif

/**********************************************************************
*  Record the build options for the resource file:
**********************************************************************/

#if defined(HW_INTERRUPTS)
#define BUILD_OPTIONS_INT "Hardware Interrupts"
#else
#define BUILD_OPTIONS_INT "No HW Interrupts"
#endif
#if defined(ADD_TRACE) && defined(FILE_SYSTEM)
#define BUILD_OPTIONS "TRACE and DUMP enabled"
#elif defined(FILE_SYSTEM)
#define BUILD_OPTIONS "DUMP enabled, TRACE disabled"
#elif defined(ADD_TRACE)
#define BUILD_OPTIONS "Diagnostic TRACE enabled, DUMP disabled"
#else
#define BUILD_OPTIONS "No Trace or Dump enabled"
#endif
