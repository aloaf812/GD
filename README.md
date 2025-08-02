# Geometry Dash Decompilation (1.7 branch)

Disclaimer: This is a **work-in-progress** decompilation of Geometry Dash version 1.700. It is not in a usable state and cannot be used to play Geometry Dash.

## Build Instructions

### Prerequisites
* cocos2d-x 2.2.3 (the github version is missing some files so download it through [this](https://archive.org/download/cocos2dx223/cocos2d-x-2.2.3.zip) link)
### Android

1. Download Android NDK r8e ([Windows](https://dl.google.com/android/ndk/android-ndk-r8e-windows-x86_64.zip) | [Linux](https://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2) | [Darwin (Mac)](https://dl.google.com/android/ndk/android-ndk-r8e-darwin-x86_64.tar.bz2)) and extract it somewhere on your drive.
2. Go to the proj.android directory and run the `build_native.sh` file. This should generate the `assets`, `jni`, `libs`, and `obj` folders.
#### iOS
* Any version of **Mac OS X** compatible with your Xcode version 
* **[Xcode 4](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_4_and_ios_sdk_4.3__final/xcode_4_and_ios_sdk_4.3__final.dmg)** or above ([Xcode 5.1.1](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_5.1.1/xcode_5.1.1.dmg) was used to build 1.7)

### TODO: Finish this README or turn it into a wiki


## Why decompile 1.7?

GD 1.7 was the first and only version to use [cocos2d-x 2.2.3](https://github.com/cocos2d/cocos2d-x/releases/tag/cocos2d-x-2.2.3) without any modifications, which removes the need to decompile the engine, making decompilation much more straightforward.

## SHA-1 File Hashes
### Android

* APK File: `4d445903218646cb55bb39a88004a0c488ad2cde`

  **libcocos2dcpp.so:**
  * armeabi: `1234cb7af26dd2b68db084c752747c3ea72cbd01`
  * armeabi-v7a: `79a55b31a96d845a40e12398ef9090dbab9dc5c0`
  * x86: `e474a0ff454a5111d7a037d5f163b9e8e0732d7d`

###  iOS

* IPA File: `269eef85b33ff75cba487b7cce77f0eb947d4ab0`
* GeometryJump (executable): `f1dfe8232462155c02bd610f6b62942118f9cbfa`