#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "Page.hpp"
#include "blocks.hpp"
#include "debug.hpp"
#include "visualize.hpp"
#include "PageBeginning.hpp"
#include "PageGame.hpp"

using std::cin;
using std::cout;
using std::endl;


void showLicense() 
{
    cout << "---------------------------------------------------------" << endl;
    cout << "SweepMine" << endl;
    cout << "Version: Developing" << endl;
    cout << "Author: LaNterN_AloNe & Hamster the Blue" << endl;
    cout << "Description: A simple minesweeper game." << endl;
    cout << "---------------------------------------------------------" << endl;
}