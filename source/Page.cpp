#include "../include/Page.hpp"

// Get the name of the page, coloring the name string.
const char *getPageName(const int page)
{
    switch (page)
    {
    case BEGINNING_PAGE:
        return "\033[36mBEGINNING_PAGE\033[0m";
    case GAME_PAGE:
        return "\033[36mGAME_PAGE\033[0m";
    case ENDING_PAGE:
        return "\033[36mENDING_PAGE\033[0m";
    default:
        return "\033[36m?UNKNOWN?\033[0m";
    }
}

// Check if the page exists in the map.
bool isPageExist(const int currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    return pages.find(currentPage) != pages.end();
}