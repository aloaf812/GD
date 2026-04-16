maybe a rewrite of this entire file should be considered due to how messy it is
# Contributing

## The Process

js gimme some time i'll add it soon

## Resources

### - [GD Docs:](https://wyliemaster.github.io/gddocs/) provides useful information on some aspects of the game.
### - [Geode Docs:](https://docs.geode-sdk.org/) provides variable names, classes, and return types as well as some other useful infoformation.
- [Geode's 1.920 bindings](https://github.com/geode-sdk/bindings/blob/main/bindings/1.920/GeometryDash.bro) are also extremely useful with minimal differences to 1.710, containing discovered variable names, ordering, and types.
### - [Library of Geometria:](https://a-zalt.github.io/) Provides knowledge on the game's technical quirks and changes between versions.
## Previous Decompilation Attempts
- [ProjectReversio](https://github.com/ProjectReversio/GeometryDash) (2.113 + lite versions)
- [WylieMaster](https://github.com/WylieMaster/GD-Decompiled) (2.113)
- [CallocGD](https://github.com/callocgd/gd-2.205-decompiled) (2.205) [fork of wylie's decomp]
- [OpenGD](https://github.com/open-gd/opengd) (2.2) [uses Axmol as its engine]
## Disassemblers

### Setup
- *"If you want to decompile a game, first you need to know what the game does."*

    ***aloaf812***

That's why we use tools like **Ghidra** (free) or **[IDA Pro](https://hex-rays.com/ida-proz/)** (for those who have $1k+ to spare) to give us pseudocode representations of an app's binaries into something that's much more easily understandable for a human.

For this project I'm using Ghidra since I can't afford IDA and I already have past experience with it.

Before you get started decompiling a binary, you need to [**Install Ghidra**](https://github.com/NationalSecurityAgency/ghidra#Install).

todo: finish this usage/contribution/decompilation guide

# IDE Setup

### VS Code: 
lowkey can't do this part yet

### Xcode: 
also this part



# Project Setup
i might make a script to do all of this without having to follow a guide
### Prerequisites

- cocos2d-x 2.2.3 ([from my github repo](https://github.com/aloaf812/cocos2d-x))

### 1. Set up `projects` folder

Once you have extracted the `cocos2d-x-2.2.3.zip` folder, create a folder named `projects` in the root cocos2d-x direcory (the one that contains `cocos2d`, `CocosDenshion` and all that good stuff)

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
- [`proj.wp8`](https://github.com/aloaf812/GD/tree/1.7/proj.wp8) Source code for the Windows Phone version
- [`proj.ios`](https://github.com/aloaf812/GD/tree/1.7/proj.ios) Xcode project for iOS

- `Resources` Contains all of GD's assets. They can be extracted from either the APK or IPA (which will only render correctly on macOS). This folder isn't included in the repository to prevent piracy.