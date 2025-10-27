# Project: SweepMine
这里是用cpp模拟扫雷游戏的一个项目。

# Feature:
- 拥有扫雷最基本的功能。
- 支持基本的窗口适配，你可以随意拉伸窗口，游戏界面会自动缩放以适应新的窗口大小。

# Requirements:
本项目使用SFML（版本应为2.6.1）库进行可视化展示，编译环境是GCC 14.2.0（默认 C++17），需要为自己的编译环境安装该库。

## MSYS2（UCRT64 工具链）
为安装SFML库，需要在MSYS2中安装SFML的UCRT64版本。可以使用以下命令安装：
pacman -S mingw-w64-ucrt-x86_64-sfml

## MinGW
如果使用MinGW，需要手动安装该库，下载地址：https://www.sfml-dev.org/download.php

获取到库文件后，将其中内容分别复制到bin lib include 目录下。

特别注意！这种方式安装的sfml的dll与本项目代码编译时链接的dll不一致，会出现编译通过运行报错的情况，需要再手动替换dll文件。可以在本项目根目录的dll-if_needed文件夹下找到多个名为sfml-*-2.dll的文件，将它们分别替换到bin目录下的对应文件即可（除了openal32.dll）。

# Run:
直接运行：执行StartGame.ps1即可。

编译后运行：执行buildgame.ps1脚本，编译完成后，会自动打开游戏窗口。