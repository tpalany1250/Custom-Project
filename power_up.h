#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different options for the kind of power ups.
 * Adjusts the image used.
 */
enum power_up_kind
{
    SHIELD,
    HEART,
    POWER,
    FUEL,
    DIAMOND
};

/** but for power up
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   kind            Current kind of player ship
 */
struct power_up_data
{
    sprite      power_up_sprite;
    power_up_kind   kind;
};

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 *
 * @param player_to_update      The player being updated
 */
bitmap power_up_bitmap(power_up_kind kind);

/**
 * Creates a new player in the centre of the screen with the default ship.
 * @param x,y
 * @returns     The new player data
 */
power_up_data new_power_up(double x, double y);

/**
 * Draws the player to the screen. 
 * 
 * @param power_up_to_draw    The player to draw to the screen
 */
void draw_power_up(const power_up_data &power_up_to_draw);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param power_up_to_update      The player being updated
 */
void update_power_up(power_up_data &power_up_to_update);

#endif 