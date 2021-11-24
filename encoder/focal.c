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

#include "focal.h"
#include "common/common.h"
#include "macroblock.h"
#include "ratecontrol.h"
#include "focal_connect.h"

#include "time.h"
#include "math.h"

#define UNITY_PI            3.14159265359f

static int init = 0; //set to 1 once function is called for first time. Do Not Touch!

static x264_pthread_t connect_thread;
static x264_focal_input_t input_data = {};

// SIN( FOV / 4 ) = thresh / 2
static const float thresh = 1.2; //2 = 360degree, sqrt 2 = 180degree, 1 = 120degree, quest is 90 horizontal
static const int focal_diff = 5; //added/subtracted to qp depending whether mb is in focus
static int dd = 0; //The difference between original qp of first frame and current qp
static int rc_qp = 0;
  
static int valid_pos = 0;
x264_float3_t focal_point;

static float x_max = 0; //width of video in mb's
static float y_max = 0; //height of video in mb's

//TODO remove below vars
static int num = 1; //used to print qp every 100000 mb

static int stat_max_qp = -1;
static long double stat_total_qp = 1;
static long double stat_total_count = 1;

// Hardcoded Dimensions of center points for sphere halves on spherical video

static float lensCenter_right_x = (4575.319 / 6080);
static float lensCenter_right_y = (1521.183 / 3040);

static float lensRadius_right_x = (1430.017 / 6080);
static float lensRadius_right_y = (1430.017 / 3040);

static float lensCenter_left_x = (1530.073 / 6080);
static float lensCenter_left_y = (1515.421 / 3040);

static float lensRadius_left_x = (1425.675 / 6080);
static float lensRadius_left_y = (1425.675 / 3040);
static float HALF_BOUNDARY = (6080/2);

static float SCALE = 180/186;

// returns in-focus qp within valid range
int x264_focal_qp_improve( x264_t *h, int dist ){
    int out = x264_ratecontrol_mb_qp( h ) - focal_diff;
    if(out > stat_max_qp){
            stat_max_qp = out;
    }
    out = (out > 81) ? 81 : out;
    return (out < 0) ? 0 : out;
}

// returns out-of-focus qp within valid range
int x264_focal_qp_worsen( x264_t *h, int dist ){
    int out = x264_ratecontrol_mb_qp( h ) + dd;
    if(out > stat_max_qp){
            stat_max_qp = out;
    }
    out = (out < 0) ? 0 : out;
    return (out > 81) ? 81 : out;
}

int x264_focal_reallocate_qp( x264_t *h )
{
    char* disable_focal = getenv("DISABLE_FOCAL");
    int isFocalDisabled = 0; //this value should be 0
    if(disable_focal!=NULL) isFocalDisabled = atoi(disable_focal);
    
    //return x264_ratecontrol_mb_qp( h );
    //once at the beginning of each frame
    if(h->mb.i_mb_x == 0 && h->mb.i_mb_y == 0){
        //One time initialization at beginning of video
        if(init == 0){
            //start client routine
            if( x264_pthread_mutex_init( &input_data.mutex, NULL ) ){
                printf("focal_connect: failed creating mutex\n");
            }
            input_data.status = uninitialized;
            input_data.x = 0;
            input_data.y = 0;
            input_data.z = 0;
            if(x264_pthread_create(&connect_thread,NULL,x264_focal_connect,&input_data)){
                printf("Focal failed to create thread for focal_connect\n");
            }
            rc_qp = x264_ratecontrol_mb_qp( h );
            stat_total_qp = rc_qp;
            stat_total_count = 1;
            x_max = (float) h->mb.i_mb_width;
            y_max = (float) h->mb.i_mb_height;
            init = 1;
        }
        //int qp_new = x264_ratecontrol_mb_qp( h );
        //int delta = qp_new - rc_qp;
        // dd += delta;
        // rc_qp = qp_new;

        x264_pthread_mutex_lock(&input_data.mutex);
        valid_pos = (input_data.status == valid) ? 1 : 0;
        focal_point.x = input_data.x;
        focal_point.y = input_data.y;
        focal_point.z = input_data.z;
        x264_pthread_mutex_unlock(&input_data.mutex);
        if(isFocalDisabled)printf("Focal is Disabled!\n");
        printf("currqp %d, avgqp = %Lf. Sample size = %Lf\n", x264_ratecontrol_mb_qp( h ) ,(stat_total_qp / stat_total_count), stat_total_count);
        printf("x = %f, y = %f, z = %f\n",focal_point.x,focal_point.y,focal_point.z);
    }
    //calc distance from current mb to focal point
    x264_float2_t mb_pos;
    mb_pos.x = ( (float) h->mb.i_mb_x ) / x_max;
    mb_pos.y = ( (float) h->mb.i_mb_y ) / y_max;
    float dist = x264_focal_abs_distance(mb_pos);
    //apply qp changes
    int qp;
    if(dist < thresh){        
        qp = x264_ratecontrol_mb_qp( h );
        //qp = x264_focal_qp_improve(h, dist);
        stat_total_qp += qp;
        stat_total_count++;
        return qp;
    }
    if(isFocalDisabled) return x264_ratecontrol_mb_qp( h );
    return 80;
    //return x264_focal_qp_worsen(h, dist);
}

// calculate the distance between macroblock position and the head data projected onto the sphere
// if environment variable INPUT==PLANE then we want to use calculation for foveation from planar video source
// else do caluclations assuming spherical input video
float x264_focal_abs_distance(x264_float2_t mb_pos){
    // get enviornment variable to determine how distance is calculated for macroblock
    int isVideoPlane = 0;
    char* input_video_geometry = getenv("INPUT");
    if(input_video_geometry!=NULL) {
        // strcmp returns 0 if they are equal
        isVideoPlane = (!strcmp("PLANE", input_video_geometry));
    }
    x264_float3_t mb_point;
    // decision on how to calculate distance for macroblock position based on input video geometry
    if (isVideoPlane) {
        mb_point = x264_focal_getSpherePos(mb_pos);
        x264_float3_t delta;
        delta.x = mb_point.x - focal_point.x;
        delta.y = mb_point.y - focal_point.y;
        delta.z = mb_point.z - focal_point.z;
        return (float) sqrt( ( delta.x * delta.x ) + ( delta.y * delta.y ) + ( delta.z * delta.z ) );
    }
    // video is fisheye (spherical)
    mb_point = x264_focal_getSpherePos_sphereInput(mb_pos);
    float focal_mag = sqrt(pow(focal_point.x, 2) + pow(focal_point.y, 2) + pow(focal_point.z, 2));
    float mb_point_mag = sqrt(pow(mb_point.x, 2) + pow(mb_point.y, 2) + pow(mb_point.z,2));
    float mb_dot_focal = (focal_point.x * mb_point.x) + (focal_point.y * mb_point.y) + (focal_point.z * mb_point.z);
    float angle = acosf(mb_dot_focal/ (focal_mag * mb_point_mag));
    return sinf(angle/4) * 2;
}

x264_float3_t x264_focal_float3_normalize( x264_float3_t vector ){
    float magnitude = sqrt(pow(vector.x,2.0)+pow(vector.y,2.0)+pow(vector.z,2.0));
    vector.x /= magnitude;
    vector.y /= magnitude;
    vector.z /= magnitude;
    return vector; 
}

x264_float2_t x264_focal_float2_normalize( x264_float2_t vector ){
    float magnitude = sqrt(pow(vector.x,2.0)+pow(vector.y,2.0));
    vector.x /= magnitude;
    vector.y /= magnitude;
    return vector; 
}

x264_float3_t x264_focal_getSpherePos( x264_float2_t mb_pos){
    x264_float2_t sphereCoords;
    sphereCoords.x = mb_pos.x - .75;
    sphereCoords.y = mb_pos.y;
    float longitude = sphereCoords.x / 0.5 * UNITY_PI;
    float latitude = sphereCoords.y * UNITY_PI;
    x264_float3_t normalized_coords;
    normalized_coords.y = cosf(latitude);
    float radius = sinf(latitude);
    normalized_coords.x = -sinf(longitude) * radius;
    normalized_coords.z = -cosf(longitude) * radius;
    return normalized_coords;
}

// calculate normalized vector that passes through the macroblocks position on sphere in unity endpoint
x264_float3_t x264_focal_getSpherePos_sphereInput(x264_float2_t mb_pos) {
    int sign = -1;
    x264_float2_t lenseCenter; 
    lenseCenter.x = lensCenter_left_x;
    lenseCenter.y = lensCenter_left_y;
    float lenseRadius;
    lenseRadius = sqrtf(powf(lensRadius_left_x, 2) + powf(lensRadius_left_y, 2));
    if (mb_pos.x > HALF_BOUNDARY) {
        //right sphere corresponds to positive z
        sign = 1;
        lenseCenter.x = lensCenter_right_x;
        lenseCenter.y = lensCenter_right_y;
        lenseRadius = sqrtf(powf(lensRadius_right_x, 2) + powf(lensRadius_right_y, 2));
    }
    // calculate distance from center of sphere the macroblock lies on
    x264_float2_t radius;
    radius.x = mb_pos.x - lenseCenter.x;
    radius.y = mb_pos.y - lenseCenter.y;
    float scalar_r = (sqrtf(powf(radius.x, 2)) + powf(radius.y, 2));
    x264_float3_t sphereCoords;
    if (scalar_r > lenseRadius) {
        sphereCoords.x = 0;
        sphereCoords.y = 0;
        sphereCoords.z = 0;
        return sphereCoords;
    }
    scalar_r = scalar_r/lenseRadius;
    // lenses_Center+lense_Radius
    float temp_x = mb_pos.x / (scalar_r * lenseRadius);
    float temp_y = mb_pos.y / (scalar_r * lenseRadius);
    
    sphereCoords.z = sign * cosf(scalar_r / SCALE) * (UNITY_PI / 2);
    // find h -- note though the real x and y are scalar multiples of h
    // we know the output should be normalized so sqrt(x^2 + y^2 + z^2) = 1 
    // => x^2 + y^ 2 = 1 - z^2. We by the relation of x and y, h^2 = x^2 + y^2, so h = sqrt(1-z^2) 
    float h = sqrt(1 - pow(sphereCoords.z, 2));
    sphereCoords.x = temp_x * h;
    sphereCoords.y = temp_y * h;
    
    return sphereCoords;
}
