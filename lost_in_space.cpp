#include "lost_in_space.h"
#include "splashkit.h"

// creates game
game_data new_game() 
{
    game_data game;
    game.player = new_player(); // creates new player
    return game;
}

// Function to display HUD in game window
void display_HUD(const player_data &player)
{
    fill_rectangle(COLOR_BLUE_VIOLET, 0, 0, 1000, 100, option_to_screen());
    draw_text("SCORE: " + to_string(player.score), COLOR_WHITE, 0, 0, option_to_screen()); // writes SCORE
    draw_text("LOCATION: " + point_to_string(center_point(player.player_sprite)), COLOR_WHITE, 0, 10, option_to_screen()); // writes LOCATION
    draw_text("Fuel Gauge: " + to_string(player.fuel_pct * 100) + "%", COLOR_WHITE, 0, 35, option_to_screen()); // writes Fuel Guage
    draw_text("Shield: " + to_string(player.shield_pct * 100) + "%", COLOR_WHITE, 400, 40, option_to_screen()); // writes Shield
    draw_text("Health bar: " + to_string(player.health_pct * 100) + "%", COLOR_WHITE, 0, 75, option_to_screen()); // writes Health bar
    draw_bitmap("empty", 90, 20, option_to_screen()); // displays empty bar
    draw_bitmap("empty", 460, 20, option_to_screen()); // displays empty bar
    draw_bitmap("empty", 90, 55, option_to_screen()); // displays empty bar
    draw_bitmap("full" , 90, 20, option_part_bmp(0,0, bitmap_width("full")*player.fuel_pct, bitmap_height("full"), option_to_screen())); // Fuel Guage
    draw_bitmap("blue_bar_bubbles" , 460, 20, option_part_bmp(0,0, bitmap_width("blue_bar_bubbles")*player.shield_pct, bitmap_height("blue_bar_bubbles"), option_to_screen())); // Shield bar
    draw_bitmap("orange_bar_lines" , 90, 55, option_part_bmp(0,0, bitmap_width("orange_bar_lines")*player.health_pct, bitmap_height("orange_bar_lines"), option_to_screen())); // Health bar
} 

// Function to update game
void update_game(game_data &game) 
{
    handle_input(game.player); // updates the game state
    update_player(game.player); // updating the player

    // updates each power-up, checking for collisions between the player and power-ups
    for(auto &power_up: game.power_ups)
    {
        update_power_up(power_up);
    }

    for (auto &asteroid : game.asteroids)
    {
        update_asteroid(asteroid);
    }

    check_collisions(game);

    // // Calculate the new camera position to follow the player's position
    // point_2d playerPosition = center_point(game.player.player_sprite);
    // double cameraX = playerPosition.x - (screen_width() / 2);
    // double cameraY = playerPosition.y - (screen_height() / 2);

    // // Update the camera position
    // set_camera_position(point_at(cameraX, cameraY));
}

// Function to draw game
void draw_game(const game_data &game) 
{
    // draws players
    draw_player(game.player);

    // draws power-ups
    for(auto &power_up: game.power_ups)
    {
        draw_power_up(power_up);
    }

    for (auto &asteroid : game.asteroids)
    {
        draw_asteroid(asteroid);
    }
}

// Function to add power-up
void add_power_up(game_data &game) 
{
    // Only add a power-up if there are fewer than the maximum number of power-ups
    if (game.power_ups.size() < MAX_POWER_UPS)
    {
        double x = rnd(-1500.0, 1500.0); // x-coordinate in the range [-1500, 1500]
        double y = rnd(-1500.0, 1500.0); // y-coordinate in the same range
        game.power_ups.push_back(new_power_up(x, y));
    }
}

// Function to add asteroids
void add_asteroid(game_data &game)
{
    // Only add a asteroid if there are fewer than the maximum number of asteroids
    if (game.asteroids.size() < MAX_ASTEROIDS)
    {
        double x = rnd(-1500.0, 1500.0); // x-coordinate in the range [-1500, 1500]
        double y = rnd(-1500.0, 1500.0); // y-coordinate in the range [-1500, 1500]
        game.asteroids.push_back(new_asteroid(x, y));
        // add_asteroid(game, x, y);
    }
}




// Function to check for collisions between the player and each power-up
void check_collisions(game_data &game) 
{
    // What happen when player comes in contact with power-up
    for(int i = game.power_ups.size() - 1; i >= 0; i--)
    {
        if(sprite_collision(game.player.player_sprite, game.power_ups[i].power_up_sprite))
        {
            apply_power_up(game, i); // applies the power-up to the player
            remove_power_up(game, i); // then removes power-up from the screen
        }
    }


    // Check for collisions between the player and asteroids
    for (int i = game.asteroids.size() - 1; i >= 0; i--)
    {
        if (sprite_collision(game.player.player_sprite, game.asteroids[i].asteroid_sprite))
        {
            apply_collision(game, i);
            // Remove the asteroid from the game when it collides with the player
            // game.asteroids.erase(game.asteroids.begin() + i);
            remove_asteroid(game, i);
        }
    }
}

// Function to increase power up within the player
void apply_power_up(game_data &game, int index) 
{
    // loads sound of when player collects power-up
    load_sound_effect("powerup", "power_up.wav");

    switch(game.power_ups[index].kind)
    {
        case SHIELD:
            game.player.shield_pct = min(1.0, game.player.shield_pct + 0.25); // increases shield by 25%
            play_sound_effect("powerup"); // Play sound effect when SHIELD is collected
            break;
        case HEART:
            game.player.health_pct = min(1.0, game.player.health_pct + 0.25); // increases health by 25%
            play_sound_effect("powerup"); // Play sound effect when HEART is collected
            break;
        case POWER:
            sprite_set_dx(game.player.player_sprite, sprite_dx(game.player.player_sprite) + PLAYER_SPEED); // increases speed
            play_sound_effect("powerup"); // Play sound effect when POWER is collected
            break;
        case FUEL:
            game.player.fuel_pct = min(1.0, game.player.fuel_pct + 0.25); // increases fuel by 25%
            play_sound_effect("powerup"); // Play sound effect when FUEL is collected
            break;
        case DIAMOND:
            game.player.score += 50; // increases score by 50 
            play_sound_effect("powerup"); // Play sound effect when DIAMOND is collected
            break;
        default:
            break;
    }
}

void apply_collision(game_data &game, int index)
{
    // Load sound effect for collision
    load_sound_effect("collision", "a.mp3");
    
    // Decrease shield and health when colliding with an asteroid
    game.player.shield_pct = max(0.0, game.player.shield_pct - 0.1); // Decrease shield by 10%
    game.player.health_pct = max(0.0, game.player.health_pct - 0.1); // Decrease health by 10%
    
    // Decrease player speed
    sprite_set_dx(game.player.player_sprite, sprite_dx(game.player.player_sprite) - PLAYER_SPEED);
    
    // Decrease player score
    game.player.score -= 50; // Decrease score by 50
    
    play_sound_effect("collision"); // Play sound effect when collision occurs

    // Adjust the player's position to ensure it stays within bounds
    double playerX = sprite_x(game.player.player_sprite);
    double playerY = sprite_y(game.player.player_sprite);
    double playerWidth = sprite_width(game.player.player_sprite);
    double playerHeight = sprite_height(game.player.player_sprite);
    
    // Keep the player within the screen boundaries
    if (playerX < 0) sprite_set_x(game.player.player_sprite, 0);
    if (playerX + playerWidth > screen_width()) sprite_set_x(game.player.player_sprite, screen_width() - playerWidth);
    if (playerY < 0) sprite_set_y(game.player.player_sprite, 0);
    if (playerY + playerHeight > screen_height()) sprite_set_y(game.player.player_sprite, screen_height() - playerHeight);

}

// Function to remove power-ups from the screen
void remove_power_up(game_data &game, int index) 
{
    game.power_ups.erase(game.power_ups.begin() + index); // erases power-up
}

// Function to remove asteroid from the screen
void remove_asteroid(game_data &game, int index) 
{
    game.asteroids.erase(game.asteroids.begin() + index); // erases asteroid
}
