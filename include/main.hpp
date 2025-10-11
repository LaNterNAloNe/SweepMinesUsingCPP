#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "../include/Page.hpp"
#include "../include/blocks.hpp"
#include "../include/debug.hpp"
#include "../include/visualize.hpp"
#include "../include/PageBeginning.hpp"

using std::cin;
using std::cout;
using std::endl;


void showLicense() {
    cout << "---------------------------------------------------------" << endl;
    cout << "SweepMine" << endl;
    cout << "Version: Developing" << endl;
    cout << "Author: LaNterN_AloNe & Hamster the Blue" << endl;
    cout << "Description: A simple minesweeper game." << endl;
    cout << "---------------------------------------------------------" << endl;
}