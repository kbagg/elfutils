/* SH specific relocation handling.
   Copyright (C) 2000, 2001, 2002, 2005 Red Hat, Inc.
   This file is part of Red Hat elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2000.

   Red Hat elfutils is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 2 of the License.

   Red Hat elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with Red Hat elfutils; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301 USA.

   Red Hat elfutils is an included package of the Open Invention Network.
   An included package of the Open Invention Network is a package for which
   Open Invention Network licensees cross-license their patents.  No patent
   license is granted, either expressly or impliedly, by designation as an
   included package.  Should you wish to participate in the Open Invention
   Network licensing program, please visit www.openinventionnetwork.com
   <http://www.openinventionnetwork.com>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <elf.h>
#include <stddef.h>

#define BACKEND sh_
#include "libebl_CPU.h"


/* Return true if the symbol type is that referencing the GOT.  */
bool
sh_gotpc_reloc_check (Elf *elf __attribute__ ((unused)), int type)
{
  return type == R_SH_GOTPC;
}

/* Check for the simple reloc types.  */
Elf_Type
sh_reloc_simple_type (Ebl *ebl __attribute__ ((unused)), int type)
{
  switch (type)
    {
    case R_SH_DIR32:
      return ELF_T_WORD;
    default:
      return ELF_T_NUM;
    }
}

/* Check whether machine flags are valid.  */
bool
sh_machine_flag_check (GElf_Word flags)
{
  switch (flags & EF_SH_MACH_MASK)
    {
    case EF_SH_UNKNOWN:
    case EF_SH1:
    case EF_SH2:
    case EF_SH3:
    case EF_SH_DSP:
    case EF_SH3_DSP:
    case EF_SH4AL_DSP:
    case EF_SH3E:
    case EF_SH4:
    case EF_SH2E:
    case EF_SH4A:
    case EF_SH2A:
    case EF_SH4_NOFPU:
    case EF_SH4A_NOFPU:
    case EF_SH4_NOMMU_NOFPU:
    case EF_SH2A_NOFPU:
    case EF_SH3_NOMMU:
    case EF_SH2A_SH4_NOFPU:
    case EF_SH2A_SH3_NOFPU:
    case EF_SH2A_SH4:
    case EF_SH2A_SH3E:
      break;
    default:
      return false;
    }

  return ((flags &~ (EF_SH_MACH_MASK)) == 0);
}
