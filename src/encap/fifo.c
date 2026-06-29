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
 *   @file          fifo.c
 *
 *          Project:     GSE LIBRARY
 *
 *          Company:     THALES ALENIA SPACE
 *
 *          Module name: FIFO
 *
 *   @brief         FIFO for GSE encapsulation context
 *
 *   @author        Julien BERNARD / Viveris Technologies
 *
 */
/****************************************************************************/

#include "fifo.h"

#include <stdlib.h>
#include <assert.h>


/****************************************************************************
 *
 *   PUBLIC FUNCTIONS
 *
 ****************************************************************************/

gse_status_t gse_init_fifo(fifo_t *fifo, size_t size)
{
  assert(fifo != NULL);

  if(size == 0)
  {
    return GSE_STATUS_FIFO_SIZE_NULL;
  }

  /* Each FIFO value is an encapsulation context */
  fifo->values = calloc(size, sizeof(gse_encap_ctx_t));
  if(fifo->values == NULL)
  {
    return GSE_STATUS_MALLOC_FAILED;
  }
  /* Initialize the FIFO */
  fifo->size = size;
  fifo->first = 0;
  /* When the first element is created fifo->last become 0 */
  fifo->last = size - 1;
  fifo->elt_nbr = 0;
  /* Initialize the mutex on the FIFO */
  if(pthread_mutex_init(&fifo->mutex, NULL) != 0)
  {
    return GSE_STATUS_PTHREAD_MUTEX;
  }

  return GSE_STATUS_OK;
}

gse_status_t gse_release_fifo(fifo_t *fifo)
{
  gse_status_t status = GSE_STATUS_OK;
  gse_status_t stat_mem = GSE_STATUS_OK;

  assert(fifo != NULL);

  if(pthread_mutex_lock(&fifo->mutex) != 0)
  {
    return GSE_STATUS_PTHREAD_MUTEX;
  }

  /* Free fragments in each encapsulation context */
  for(size_t i = fifo->first;
      i != (fifo->last + 1) % fifo->size;
      i = (i + 1) % fifo->size)
  {
    status = gse_free_vfrag(&(fifo->values[i].vfrag));
    if(status != GSE_STATUS_OK)
    {
      stat_mem = status;
    }
  }

  free(fifo->values);

  if(pthread_mutex_unlock(&fifo->mutex) != 0)
  {
    return GSE_STATUS_PTHREAD_MUTEX;
  }

  if(pthread_mutex_destroy(&fifo->mutex) != 0)
  {
    return GSE_STATUS_PTHREAD_MUTEX;
  }

  return stat_mem;
}

gse_status_t gse_pop_fifo(fifo_t *fifo)
{
  gse_status_t status = GSE_STATUS_OK;

  assert(fifo != NULL);

  if(pthread_mutex_lock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
    goto error_mutex;
  }

  if(fifo->elt_nbr <= 0)
  {
    status = GSE_STATUS_FIFO_EMPTY;
    goto unlock;
  }
  fifo->first = (fifo->first + 1) % fifo->size;
  fifo->elt_nbr--;

unlock:
  if(pthread_mutex_unlock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
  }
error_mutex:
  return status;
}

gse_status_t gse_push_fifo(fifo_t *fifo, gse_encap_ctx_t **context,
                           gse_encap_ctx_t ctx_elts)
{
  gse_status_t status = GSE_STATUS_OK;

  assert(fifo != NULL);
  assert(context != NULL);

  if(pthread_mutex_lock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
    goto error_mutex;
  }

  if(fifo->elt_nbr >= fifo->size)
  {
    status = GSE_STATUS_FIFO_FULL;
    goto unlock;
  }
  fifo->last = (fifo->last + 1) % fifo->size;
  fifo->elt_nbr++;

  /* Return the context address */
  *context = &(fifo->values[fifo->last]);
  /* Copy elements in the context */
  **context = ctx_elts;

unlock:
  if(pthread_mutex_unlock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
  }
error_mutex:
  return status;
}

gse_status_t gse_get_fifo_elt(fifo_t *fifo, gse_encap_ctx_t **context)
{
  gse_status_t status = GSE_STATUS_OK;

  assert(fifo != NULL);
  assert(context != NULL);

  if(pthread_mutex_lock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
    goto error_mutex;
  }

  if(fifo->elt_nbr == 0)
  {
    status = GSE_STATUS_FIFO_EMPTY;
    goto unlock;
  }
  *context = &(fifo->values[fifo->first]);

unlock:
  if(pthread_mutex_unlock(&fifo->mutex) != 0)
  {
    status = GSE_STATUS_PTHREAD_MUTEX;
  }
error_mutex:
  return status;
}

int gse_get_fifo_elt_nbr(fifo_t *const fifo)
{
  assert(fifo != NULL);

  if(pthread_mutex_lock(&fifo->mutex) != 0)
  {
    return -1;
  }

  const int nbr = fifo->elt_nbr;
  if(pthread_mutex_unlock(&fifo->mutex) != 0)
  {
    return -1;
  }

  return nbr;
}
