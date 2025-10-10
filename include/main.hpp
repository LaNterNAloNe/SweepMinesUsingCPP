#pragma once

#include <iostream>
#include <vector>
#include "../include/blocks.hpp"
#include "../include/debug.hpp"
#include "../include/visualize.hpp"
#include "../include/page_beginning.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

enum Page
{
    BEGINNING_PAGE,
    GAME_PAGE,
    ENDING_PAGE
};