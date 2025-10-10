这里是用cpp模拟扫雷游戏的一个项目

本项目使用SFML库进行可视化展示，编译环境是g++，使用MSYS2（UCRT64 工具链）
为安装SFML库，需要在MSYS2中安装SFML的UCRT64版本。可以使用以下命令安装：
pacman -S mingw-w64-ucrt-x86_64-sfml

然后，在项目目录下，使用以下命令编译项目：
g++ source/main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
或者，直接运行buildgame.ps1脚本
这样，你可以直接在项目根目录下运行main.exe文件，即可看到可视化的扫雷游戏界面。

