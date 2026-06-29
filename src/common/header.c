/*
 *
 * This piece of software is an implementation of the Generic Stream
 * Encapsulation (GSE) standard defined by ETSI for Linux (or other
 * Unix-compatible OS). The library may be used to add GSE
 * encapsulation/de-encapsulation capabilities to an application.
 *
 *
 * Copyright © 2016 TAS
 *
 *
 * This file is part of the GSE library.
 *
 *
 * The GSE library is free software : you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY, without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 *
 */

/****************************************************************************/
/**
 *   @file          header.c
 *
 *          Project:     GSE LIBRARY
 *
 *          Company:     THALES ALENIA SPACE
 *
 *          Module name: COMMON
 *
 *   @brief         Header functions
 *
 *   @author        Julien BERNARD / Viveris Technologies
 *
 */
/****************************************************************************/

#include "header.h"

#include <assert.h>

#include "constants.h"

/****************************************************************************
 *
 *   PUBLIC FUNCTIONS
 *
 ****************************************************************************/

size_t gse_compute_header_length(gse_payload_type_t payload_type,
                                 gse_label_type_t label_type)
{
  const int label_length = gse_get_label_length(label_type);

  switch(payload_type)
  {
    case GSE_PDU_COMPLETE:
      return GSE_MANDATORY_FIELDS_LENGTH +
             GSE_PROTOCOL_TYPE_LENGTH +
             (size_t)label_length;

    case GSE_PDU_FIRST_FRAG:
      return GSE_MANDATORY_FIELDS_LENGTH +
             GSE_FRAG_ID_LENGTH +
             GSE_TOTAL_LENGTH_LENGTH +
             GSE_PROTOCOL_TYPE_LENGTH +
             (size_t)label_length;

    case GSE_PDU_SUBS_FRAG:
    case GSE_PDU_LAST_FRAG:
      return GSE_MANDATORY_FIELDS_LENGTH + GSE_FRAG_ID_LENGTH;

    default:
      assert(0);
      return 0;
  }
}
