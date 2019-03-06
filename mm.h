/* ====================================================================
 * Copyright (c) 1999-2007 Ralf S. Engelschall <rse@engelschall.com>
 * Copyright (c) 1999-2007 The OSSP Project <http://www.ossp.org/>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by
 *     Ralf S. Engelschall <rse@engelschall.com>."
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by
 *     Ralf S. Engelschall <rse@engelschall.com>."
 *
 * THIS SOFTWARE IS PROVIDED BY RALF S. ENGELSCHALL ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL RALF S. ENGELSCHALL OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

/*
**
**  mm.h -- Shared Memory library API header
**
*/

#ifndef _MM_H_
#define _MM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
**  ____ Public Part (I) of the API ________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef enum {
    MM_LOCK_RD, MM_LOCK_RW
} mm_lock_mode;

/*
**  ____ Public Part (II) of the API _______________________
*/

#if defined(MM_PRIVATE)
typedef mem_pool MM;
#else
typedef void MM;
#endif

/* Global Malloc-Replacement API */
int     MM_create(size_t, const char *);
int     MM_permission(mode_t, uid_t, gid_t);
void    MM_reset(void);
void    MM_destroy(void);
int     MM_lock(mm_lock_mode);
int     MM_unlock(void);
void   *MM_malloc(size_t);
void   *MM_realloc(void *, size_t);
void    MM_free(void *);
void   *MM_calloc(size_t, size_t);
char   *MM_strdup(const char *);
size_t  MM_sizeof(const void *);
size_t  MM_maxsize(void);
size_t  MM_available(void);
char   *MM_error(void);

/* Standard Malloc-Style API */
MM     *mm_create(size_t, const char *);
int     mm_permission(MM *, mode_t, uid_t, gid_t);
void    mm_reset(MM *);
void    mm_destroy(MM *);
int     mm_lock(MM *, mm_lock_mode);
int     mm_unlock(MM *);
void   *mm_malloc(MM *, size_t);
void   *mm_realloc(MM *, void *, size_t);
void    mm_free(MM *, void *);
void   *mm_calloc(MM *, size_t, size_t);
char   *mm_strdup(MM *, const char *);
size_t  mm_sizeof(MM *, const void *);
size_t  mm_maxsize(void);
size_t  mm_available(MM *);
char   *mm_error(void);
void    mm_display_info(MM *);

/* Low-Level Shared Memory API */
void   *mm_core_create(size_t, const char *);
int     mm_core_permission(void *, mode_t, uid_t, gid_t);
void    mm_core_delete(void *);
size_t  mm_core_size(const void *);
int     mm_core_lock(const void *, mm_lock_mode);
int     mm_core_unlock(const void *);
size_t  mm_core_maxsegsize(void);
size_t  mm_core_align2page(size_t);
size_t  mm_core_align2word(size_t);

/* Internal Library API */
void    mm_lib_error_set(unsigned int, const char *);
char   *mm_lib_error_get(void);
int     mm_lib_version(void);

#ifdef __cplusplus
}
#endif

#endif /* _MM_H_ */
