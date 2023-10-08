#ifndef LOST_IN_SPACE_ASTEROID
#define LOST_IN_SPACE_ASTEROID

#include "splashkit.h"
#include "player.h"
#include <vector>

using namespace std;

#define SCREEN_BORDER 100

const double ASTEROID_SPEED = 0.1; // The speed of the asteroid

// Enumeration to represent different asteroid kinds
enum asteroid_kind
{
    PLUTO,
    VENUS,
    STAR
};

// Structure to hold asteroid data
struct asteroid_data
{
    sprite      asteroid_sprite; // The sprite representing the asteroid
    asteroid_kind   kind;
    int         score; // The score gained when player touches the asteroid
    double      health_pct; // The health percentage of the player when player touches the asteroid
};

// Function to create a new asteroid
asteroid_data new_asteroid(double x, double y);

// Function to draw the asteroid on the screen
void draw_asteroid(const asteroid_data &asteroid_to_draw);

// Function to handle collision between the player and an asteroid
void handle_player_collision(player_data &player, asteroid_data &asteroid);

// Function to update the asteroid's position and behavior
void update_asteroid(asteroid_data &asteroid_to_update);



#endif