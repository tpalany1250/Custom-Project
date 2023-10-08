#ifndef LOST_IN_SPACE_GAME
#define LOST_IN_SPACE_GAME

#include "player.h"
#include "power_up.h"
#include "asteroid.h"
#include "splashkit.h"
#include <vector>

using namespace std;

#define MAX_POWER_UPS 50 // defines maximum allowed power-ups to be 60 per screen
#define MAX_ASTEROIDS 10

// holds information related to the game
struct game_data
{
    player_data player;
    vector<power_up_data> power_ups;
    vector<asteroid_data> asteroids;
};

// creates new game
// The function initializes the game's player and power-up data
game_data new_game();

// displays the heads-up display (HUD) for the player
// takes a constant reference to a player_data structure 
void display_HUD(const player_data &player);

// updates the game by updating the player and power-ups, checking for collisions, and applying power-ups
void update_game(game_data &game);

// responsible for drawing the game, including the player and power-ups, on the screen
void draw_game(const game_data &game);

// adds a new power-up to the game
void add_power_up(game_data &game);


void add_asteroid(game_data &game);



// checks for collisions between the player and power-ups in the game.
void check_collisions(game_data &game);

// applies a power-up to the player
void apply_power_up(game_data &game, int index);


// applies a power-down to the player (when asteroids touches the player)
void apply_collision(game_data &game, int index);



// removes a power-up from the game once collected by player
void remove_power_up(game_data &game, int index);

// removes asteroid from the game once collected by player
void remove_asteroid(game_data &game, int index);



#endif