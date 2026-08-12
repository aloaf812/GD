# Contributing

## Resources
- [GD Docs:](https://boomlings.dev/) provides useful information on a lot of server-side and some client-side aspects of the game.

- [Geode Docs:](https://docs.geode-sdk.org/) provides variable names, classes, and return types as well as some other useful infoformation.

- [Geode's 1.920 bindings](https://github.com/geode-sdk/bindings/blob/main/bindings/1.920/GeometryDash.bro) are also extremely useful with minimal differences to 1.710, containing discovered variable names, ordering, and types.

- [Library of Geometria:](https://a-zalt.github.io/gdknowledge) Provides knowledge on the game's technical quirks and changes between versions.

## Previous Decompilation Attempts
- [ProjectReversio](https://github.com/ProjectReversio/GeometryDash) (2.113 + lite versions)
- [WylieMaster](https://github.com/WylieMaster/GD-Decompiled) (2.113)
- [CallocGD](https://github.com/callocgd/gd-2.205-decompiled) (2.205) [fork of wylie's decomp]
- [OpenGD](https://github.com/open-gd/opengd) (2.2) [uses Axmol as its engine]
## Disassemblers

- *"If you want to decompile a game, first you need to know what the game does."*

    ***aloaf812***

That's why we use tools like **[Ghidra](https://github.com/NationalSecurityAgency/ghidra)** (free) or **[IDA Pro](https://hex-rays.com/ida-pro/)** (for those who have $1k+ to spare) to give us pseudocode representations of an app's binaries into something that's much more easily understandable for a human.

For this project I'm using Ghidra since I can't afford IDA and I already have past experience with it.

Before you get started decompiling a binary, you need to [**Install Ghidra**](https://github.com/NationalSecurityAgency/ghidra#Install).

# (Extended) Project Setup
This is a continuation of the [building guide](https://github.com/aloaf812/GD#building) from the README.

### 1. Import the resources from the APK or IPA (optional)

First, create a `Resources` folder in your new `GD` folder. Then, find and extract your APK or IPA and depending on which one you have:

#### APK
1. Extract your APK file and open the `Assets` folder in your extracted APK.

2. Copy all of the files in this directory and paste them info your new `Resources` folder.

#### IPA
1. Open your extracted IPA and open the `GeometryJump.app` directory inside of the `Payload` directory. 

2. Copy all of the files in this directory and paste them info your new `Resources` folder.

... this is still an unfinished guide so this next section is quite irrelevant, give me a little bit of time to finish the guides...

# How to build

- Make sure you have correctly set up the project using the steps listed above. 

#### Android
1. Download Android NDK r8e ([Windows](https://dl.google.com/android/ndk/android-ndk-r8e-windows-x86_64.zip) | [Linux](https://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2) | [Darwin (Mac)](https://dl.google.com/android/ndk/android-ndk-r8e-darwin-x86_64.tar.bz2)) and extract it somewhere on your drive.
2. Open the proj.android directory and run the `build_native.sh` file.
#### iOS
* Any version of **Mac OS X** compatible with your Xcode version 
* **[Xcode 4](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_4_and_ios_sdk_4.3__final/xcode_4_and_ios_sdk_4.3__final.dmg)** or above ([Xcode 5.1.1](https://developer.apple.com/services-account/download?path=/Developer_Tools/xcode_5.1.1/xcode_5.1.1.dmg) was used to build 1.7)

### TODO: explain how to actually compile this

# Project Structure

- [`cocos2d-x`](https://github.com/aloaf812/cocos2d-x) The root directory where all of cocos2d-x's source files are. This is a fork of the main cocos2d-x code due to some changes RobTop made to it and is kept in a separate repository for simplicity's sake.

    - `projects` The projects folder which (obviously) contains cocos2d-x projects.

        - [`GD`](https://github.com/aloaf812/GD) The actual folder containing all of the decomp's files and code.

            - [`Classes`](https://github.com/aloaf812/GD/tree/1.7/Classes) The main decompiled code used across both iOS and Android.

            - [`proj.android`](https://github.com/aloaf812/ tree/1.7/proj.android) Eclipse project for generating the APK file.
                - `jni` Makefiles and main.cpp
                - `res` App icons
                - `src` Decompiled Java code

            - [`proj.ios`](https://github.com/aloaf812/GD/tree/1.7/proj.ios) Xcode project for iOS.
            
            - [`proj.wp8-xaml`](https://github.com/aloaf812/GD/tree/1.7/proj.wp8-xaml) Source code for the Windows Phone 8 version.

            - `Resources` Contains all of GD's assets. They can be extracted from either the APK or IPA (which will only render correctly on macOS). This folder isn't included in the repository to prevent piracy.