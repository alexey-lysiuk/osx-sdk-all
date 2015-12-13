/*
 * des.h
 *
 * Copyright (C) 1987, 1988, 1989 by the Massachusetts Institute of Technology.
 * 
 * Export of this software from the United States of America is assumed
 * to require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 * 
 * Include file for the Data Encryption Standard library.
 */

/* only do the whole thing once	 */
#ifndef __KERBEROSDES__
#define __KERBEROSDES__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #if TARGET_RT_MAC_CFM
        #error "Use KfM 4.0 SDK headers for CFM compilation."
    #endif
#endif

#include <stdio.h>
#include <machine/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

#ifndef DES_INT32
    #define DES_INT32 int32_t
#endif
#ifndef DES_UINT32
    #define DES_UINT32 u_int32_t
#endif

/* There are some declarations in the system-specific header files which
   can't be done until DES_INT32 is defined.  So they are in a macro,
   which we expand here if defined.  */

#ifdef	DECL_THAT_NEEDS_DES_INT32
DECL_THAT_NEEDS_DES_INT32
#endif

typedef unsigned char des_cblock[8];	/* crypto-block size */
/* Key schedule */
typedef struct des_ks_struct { union { DES_INT32 pad; des_cblock _;} __; } des_key_schedule[16];

#define DES_KEY_SZ 	(sizeof(des_cblock))
#define DES_ENCRYPT	1
#define DES_DECRYPT	0

#ifndef NCOMPAT
#define C_Block des_cblock
#define Key_schedule des_key_schedule
#define ENCRYPT DES_ENCRYPT
#define DECRYPT DES_DECRYPT
#define KEY_SZ DES_KEY_SZ
#define mit_string_to_key des_string_to_key
#define string_to_key des_string_to_key
#define read_pw_string des_read_pw_string
#define random_key des_random_key
#define pcbc_encrypt des_pcbc_encrypt
#define key_sched des_key_sched
#define cbc_encrypt des_cbc_encrypt
#define cbc_cksum des_cbc_cksum
#define C_Block_print des_cblock_print
#define quad_cksum des_quad_cksum
typedef struct des_ks_struct bit_64;
#endif

#define des_cblock_print(x) des_cblock_print_file(x, stdout)

/* Function declarations */

int des_cbc_encrypt (des_cblock *in, 
                     des_cblock *out, 
                     long length, 
                     des_key_schedule schedule, 
                     des_cblock *ivec, 
                     int encrypt);

void des_3cbc_encrypt (des_cblock *in,
                       des_cblock *out,
                       long length,
                       des_key_schedule ks1, 
                       des_key_schedule ks2, 
                       des_key_schedule ks3, 
                       des_cblock *ivec, 
                       int encrypt);
                    
unsigned long des_cbc_cksum (des_cblock *in, 
                             des_cblock *out, 
                             long length, 
                             des_key_schedule schedule, 
                             des_cblock *ivec);

int des_ecb_encrypt (des_cblock *in, 
                     des_cblock *out, 
                     des_key_schedule schedule, 
                     int encrypt);

void des_3ecb_encrypt (des_cblock *in, 
                       des_cblock *out, 
                       des_key_schedule ks1, 
                       des_key_schedule ks2, 
                       des_key_schedule ks3, 
                       int encrypt);
                      
void des_fixup_key_parity (register des_cblock key);
int des_check_key_parity (register des_cblock key);

int des_pcbc_encrypt (des_cblock *in, 
                      des_cblock *out, 
                      long length, 
                      des_key_schedule schedule, 
                      des_cblock *ivec, 
                      int encrypt);

int make_key_sched (des_cblock *key, des_key_schedule schedule);

int des_key_sched (des_cblock k, des_key_schedule schedule);

int des_new_random_key (des_cblock key);
void des_init_random_number_generator (des_cblock key);
void des_set_random_generator_seed (des_cblock key);
void des_set_sequence_number (des_cblock new_sequence_number);
void des_generate_random_block (des_cblock block);

unsigned long des_quad_cksum (unsigned char *in,
                              DES_UINT32 *out,
                              long length,
                              int out_count,
                              des_cblock *c_seed);

int des_random_key (des_cblock *key);

int des_read_password (des_cblock *k, char *prompt, int verify);
int des_read_pw_string (char *s, int max, char *prompt, int verify);

int  des_string_to_key (char *str, des_cblock key);
void afs_string_to_key (char *str, char *cell, des_cblock key);

void des_cblock_print_file (des_cblock *x, FILE *fp);

int des_is_weak_key (des_cblock key);

char *des_crypt (const char *buf, const char *salt);
char *des_fcrypt (const char *buf, const char *salt, char *ret);

int des_set_key (des_cblock *key, des_key_schedule schedule);

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma enumsalwaysint reset
        #pragma import reset
    #endif
	#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __KERBEROSDES__ */
