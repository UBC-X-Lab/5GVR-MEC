/*****************************************************************************
 * focal_client.h: prototype client that connects to remote server for position data used in
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

//TODO cite beej's guide for client.

#ifndef X264_ENCODER_FOCAL_CLIENT_H
#define X264_ENCODER_FOCAL_CLIENT_H

#include "common/common.h"
#include <netinet/in.h>

#define x264_get_in_addr x264_template(get_in_addr)
void *x264_get_in_addr(struct sockaddr *sa);

#define x264_focal_receive x264_template(focal_receive)
int x264_focal_receive( char* hostname);

#define x264_focal_client_init x264_template(focal_client_init)
int x264_focal_client_init(char* host);

#define x264_get_focal_x x264_template(get_focal_x)
int x264_get_focal_x();

#define x264_get_focal_y x264_template(get_focal_y)
int x264_get_focal_y();

#define x264_focal_client_update x264_template(x264_focal_client_update)
void x264_focal_client_update(char* buf);

#endif