/***************************************************************************//**
 * @file dynMemWrapper.c
 * @brief Wrap all malloc-related functions and force them to use Z-zone ones.
 *
 * @note: in this way we don't need heap, but we can (re) use z-zone.
 *
 *  Copyright (C) 2021-2023 by Nicola Wrachien
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 ******************************************************************************/

#include "z_zone.h"
#define WRAP_ENABLE 1
void *__wrap_malloc(size_t size)
{
#if WRAP_ENABLE
    return Z_Malloc2(size, PU_WRAP, 0, "mallocWrapper", false);
#else
    return __real_malloc(size);
#endif
}
void __wrap_free(void *ptr)
{
#if WRAP_ENABLE
  Z_Free(ptr);
#else
  return __real_free();
#endif
}
void *__wrap_calloc(size_t nitems, size_t size)
{
#if WRAP_ENABLE
  return Z_Calloc(nitems, size, PU_WRAP, NULL);
#else
  return __real_calloc(nitems, size);
#endif
}
void *__wrap_realloc(void *ptr, size_t size)
{
#if WRAP_ENABLE
  return Z_Realloc(ptr, size, PU_WRAP, NULL);
#else
  return __real_realloc(ptr, size);
#endif
}
