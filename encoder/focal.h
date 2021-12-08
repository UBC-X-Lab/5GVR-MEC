/*****************************************************************************
 * focal.h: reallocate bitrate to areas of video being looked at
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

#ifndef X264_ENCODER_FOCAL_H
#define X264_ENCODER_FOCAL_H

#include "common/common.h"

typedef struct x264_float2
{
    float x;
    float y;
} x264_float2_t;

typedef struct x264_float3
{
    float x;
    float y;
    float z;
} x264_float3_t;

#define x264_focal_qp_improve x264_template(focal_qp_improve)
int x264_focal_qp_improve( x264_t *h, int dist );

#define x264_focal_qp_worsen x264_template(focal_qp_worsen)
int x264_focal_qp_worsen( x264_t *h, int dist );

#define x264_focal_reallocate_qp x264_template(focal_reallocate_qp)
int x264_focal_reallocate_qp( x264_t *h );

#define x264_focal_abs_distance x264_template(focal_abs_distance)
float x264_focal_abs_distance(x264_float2_t mb_pos);

#define x264_focal_float3_normalize x264_template(focal_float3_normalize)
x264_float3_t x264_focal_float3_normalize( x264_float3_t vector );

#define x264_focal_float2_normalize x264_template(focal_float2_normalize)
x264_float2_t x264_focal_float2_normalize( x264_float2_t vector );

#define x264_focal_getSpherePos x264_template(focal_getSpherePos)
x264_float3_t x264_focal_getSpherePos( x264_float2_t mb_pos);

#define x264_focal_getSpherePos_sphereInput x264_template(focal_getSpherePos_sphereInput)
x264_float3_t x264_focal_getSpherePos_sphereInput( x264_float2_t mb_pos);

#define x264_focal_float3_norm x264_template(focal_float3_norm)
float x264_focal_float3_norm(x264_float3_t vect);

#define x264_focal_float2_norm x264_template(focal_float2_norm)
float x264_focal_float2_norm(x264_float2_t vect);

#define x264_focal_float2_add x264_template(focal_float2_add)
x264_float2_t x264_focal_float2_add(x264_float2_t vect1, x264_float2_t vect2); 

#define x264_focal_float3_add x264_template(focal_float3_add)
x264_float3_t x264_focal_float3_add(x264_float3_t vect1, x264_float3_t vect2);

#define x264_focal_float2_scalar_mult x264_template(focal_float2_scalar_mult)
x264_float2_t x264_focal_float2_scalar_mult(float scalar, x264_float2_t vect); 

#define x264_focal_float3_scalar_mult x264_template(focal_float3_scalar_mult)
x264_float3_t x264_focal_float3_scalar_mult(float scalar, x264_float3_t vect);

#endif