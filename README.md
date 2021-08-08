# Augmented-x264
A modification of the x264 library for real time AR/VR video streaming that redistributes bitrates to areas of the frame that are within the field of view.

# Branches

The master branch of this project takes a .mp4 input video as a source file

The profiler branch does an X11ScreenGrab to capture and encode your display

# Project components

Augmented-X264 is the modified X264 Library that does the magic. It is located in the root directory of this project.
It is modified from native x264 in the function x264_macroblock_analyse in the file encoder/analyse.c. Here a call to x264_ratecontrol_mb_qp (a native function) is replaced by a call to x264_focal_reallocate_qp (a newly added function). x264_focal_reallocate_qp as well as all other modification are encoder/focal(.c/.h) and encoder/focal_connect(.c/.h).

MinimalEncoder is responsible for low-latency streaming of encoded video. It uses the FFMPEG library and Augmented-X264.

VR_Endpoint is unity application that interfaces with the VR headset. It receives the video stream and renders it into 3D space that can be navigated by the VR headset. In addition it collects headtracking information from the VR headset and sends it back to the Augmented-X264 Encoder

The Scripts folder contains compile scripts for FFMPEG

The NativeRenderingPlugin TODO: write description and add to git repo

# Build Environment

The encoding side: Augmented-X264 and MinimalEncoder were designed and tested in Ubuntu running in a VirtualBox virtual machine

The receiving side: VR_Endpoint was designed and tested in Unity 2019 LTS running on Windows 10 Pro.

# Building the Project

Augmented-X264 can be configured by running ./configure in the root directory of the project and made with make

FFMPEG can be built using the compile scripts in the Scripts folder. These scripts are designed to run from your home directory and should be copied there before running.
the RecompileFFMPEG.sh script will download FFMPEG and all of it's dependencies and place them into the correct folders. It should be run once to setup FFMPEG
the CustomRecompileFFMPEG.sh script will use the resources created by the previous script. It compiles FFMPEG with Augmented-X264 instead of native X264

After both scripts have been run you can make MinimalEncoder by running make in the /MinimalEncoder/ directory of the project

The VR_Endpoint can be imported into and run in the 2019LTS version of Unity. It uses Oculus features which may not be supported by newer versions of Unity.

The NativeRenderingPlugin TODO: Write build instructions

# Configuring the Project

The project uses multiple network connections to communicate between portions of the project. In order to function it must be compiled with the correct IP addresses.

Headtracking data is sent from VR_Endpoint to Augmented_X264. The IP address of the device Augmented_X264 is running on must be specified in TODO find location

Video data is send from MinimalEncoder to the NativeRenderingPlugin used by VR_Endpoint. The IP address of the device running VR_Endpoint must be specifed in /MinimalEncoder/focal_transmit.c line 65.

# Running the Project

Once the project is configured and built, running is as simple as pressing play in unity and then running ./MinimalEncoder/FocalEncoder. FocalEncoder takes a single argument corresponding to the bitrate that the video should be sent with.

# Contact

If you have any questions email ailin.saggau@alumni.ubc.ca
