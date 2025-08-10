# Project Setup

### Prerequisites

- cocos2d-x 2.2.3 ([from archive.org](https://archive.org/download/cocos2dx223/cocos2d-x-2.2.3.zip))

### 1. Set up `projects` folder

Once you have extracted the `cocos2d-x-2.2.3.zip` folder, create a folder named `projects` in the root cocos2d-x direcory (the once that contains `cocos2d`, `CocosDenshion` and all that good stuff)

### 2. Get the source code to your newly created `projects` folder
 You will need Git to do this step, which you can get [here](https://git-scm.com/downloads).
 
 Run this command in your `projects` folder to clone the repository to it: `git clone --recursive https://github.com/aloaf812/GD`

### 3. Import the resources from the APK/IPA (optional)

First, create a `Resources` folder in your new `GD` folder. Then, find and extract your APK/IPA and depending on which one you have:

#### APK
1. Extract your APK file and open the `Assets` folder in your extracted APK.

2. Copy all of the files in this directory and paste them info your new `Resources` folder.

#### IPA
1. Open your extracted IPA and open the `GeometryJump.app` directory inside of the `Payload` directory. 

2. Copy all of the files in this directory and paste them info your new `Resources` folder.

# How to build

- Make sure you have correctly set up the project using the steps listed above. 

#### Android
1. Download Android NDK r8e ([Windows](https://dl.google.com/android/ndk/android-ndk-r8e-windows-x86_64.zip) | [Linux](https://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2) | [Darwin (Mac)](https://dl.google.com/android/ndk/android-ndk-r8e-darwin-x86_64.tar.bz2)) and extract it somewhere on your drive.
2. Open the proj.android directory and run the `build_native.sh` file.
#### iOS
* Any version of **Mac OS X** compatible with your Xcode version 
* **[Xcode 4](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_4_and_ios_sdk_4.3__final/xcode_4_and_ios_sdk_4.3__final.dmg)** or above ([Xcode 5.1.1](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_5.1.1/xcode_5.1.1.dmg) was used to build 1.7)

### TODO: explain how to actually compile this

# Project Overview

- [`Classes`](https://github.com/aloaf812/GD/tree/1.7/Classes) The main decompiled code used across both iOS and Android

- [`proj.android`](https://github.com/aloaf812/GD/tree/1.7/proj.android) Eclipse project for generating APK
    - `jni` Makefiles and main.cpp
    - `res` App icons
    - `src` Decompiled Java code

- [`proj.ios`](https://github.com/aloaf812/GD/tree/1.7/proj.ios) Xcode project for iOS

- `Resources` Contains all of GD's assets. They can be extracted from either the APK or IPA (which will only render correctly on macOS). This folder isn't included in the repository to prevent piracy.