/*****************************************************************************
 * focal_connect.h: connects to remote server for position data used in
 *****************************************************************************
 * Copyright (C) 2003-2020 x264 project
 *
 * Authors: Ailin Saggau-Lyons <ailin.saggau@alumni.ubc.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/

#ifndef X264_ENCODER_FOCAL_CONNECT_H
#define X264_ENCODER_FOCAL_CONNECT_H

#include "common/common.h"
#include <netinet/in.h>

enum status {valid, stale, uninitialized}; //The status of position data 

typedef struct x264_focal_input
{
    x264_pthread_mutex_t mutex; //This mutex should be held when accessing this struct
    enum status status;
    float x;
    float y;
    float z;
} x264_focal_input_t;

#define x264_focal_connect x264_template(focal_connect)
void *x264_focal_connect();

#define x264_get_in_addr x264_template(get_in_addr)
void *x264_get_in_addr(struct sockaddr *sa);

#endif
