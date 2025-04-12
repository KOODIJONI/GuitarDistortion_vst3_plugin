# GuitarDistortion_vst3_plugin🎸
GuitarDistortion_vst3_plugin - A basic guitar distortion effect, available as a VST3 plugin and a standalone application.

<img src="https://github.com/user-attachments/assets/fd42be34-3ff8-4549-99b8-14603a6bea04" width="200">

# Features⭐
__On/Off Button:__ Toggles the guitar effect on or off.

__Gain:__ Adjusts the input gain to control the level of distortion.

__Treble:__ Controls the frequency of the high-pass filter to shape the high-end response.

__Bass:__ Controls the frequency of the low-pass filter to shape the low-end response.

__Dry/Wet:__ Mixes the distorted and original signals for a more subtle or aggressive effect.

__Volume:__ Adjusts the output gain to control the final volume of the effect.


# How it works
This plugin works by using a soft-clip function on the user’s audio signal. Soft-clipping changes the sound by gently cutting the highest peaks of the signal, which creates a type of distortion.

Unlike hard-clipping, which cuts the sound sharply, soft-clipping makes the peaks rounder and smoother. This gives the sound a warmer and more natural feel, instead of making it harsh.

You can control how strong the effect is using gain knob — from a light, warm touch to a heavier, more distorted sound.

__Visualization__

Lets imagine this sine wave is our sound signal.  

<img src="https://github.com/user-attachments/assets/51eb3347-b54e-4d72-86d5-3d7e7a3b666c" width="400">

This curve shows how input values are transformed when soft clipping is applied.
It compresses the peaks while keeping the waveform smooth.

<img src="https://github.com/user-attachments/assets/d1464efc-ad0d-4394-ab96-509eb8e74c7a" width="200">
<img src="https://github.com/user-attachments/assets/f9e10bc1-b80f-4aa4-afee-721bf9a9f552" width="400">





Here’s what the sine wave looks like after passing through the soft-clip function.

<img src="https://github.com/user-attachments/assets/11cc43a1-7581-4f1b-925b-2f3a155cf3e7" width="400">

When we increase the input gain, the effect of the soft-clip becomes more pronounced.
The waveform is more compressed at the peaks, resulting in more harmonic content and a warmer, saturated sound.

<img src="https://github.com/user-attachments/assets/ecc72974-1396-4917-a777-ced59dd9db4b" width="400">


# Installation📁
 __For VST3:__   
Copy the .vst3 file to your VST3 folder from [vst plugin folder](https://github.com/KOODIJONI/GuitarDistortion_vst3_plugin/tree/main/rokPedal_vst3).

# Usage🎵
Open your favorite VST3-compatible Digital Audio Workstation (DAW).

Make sure your DAW has scanned for new VST3 plugins.

Load the plugin onto an audio track and start playing!

# Requirements❗
**Operating System:**   Windows 10/11, macOS 10.13  or Modern Linux distro

**DAW:** Must support VST3 plugins.

**Plugin Folder:** Make sure your DAW is scanning the correct folder where VST3 plugins are located.


