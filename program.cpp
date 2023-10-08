// SCREENCAST LINK: https://video.deakin.edu.au/media/t/1_kbjlszr2

#include "splashkit.h"
#include "lost_in_space.h"

int power_up_spawn_time = 15000;  // 15000 milliseconds, or 15 seconds
int asteroid_spawn_time = 20000;  // 20000 milliseconds, or 20 seconds
int time_since_last_spawn = 0;
int time_since_last_spawn_asteroid = 0;

// loads images needed for the HUD
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
    load_bitmap("orange_bar_lines","orange_bar_lines.png");
    load_bitmap("blue_bar_bubbles","blue_bar_bubbles.png");
    // load_bitmap("pluto", "pluto.png");
    // load_bitmap("venus", "venus.png");
    // load_bitmap("star", "star.png");
}

int main()
{
    timer game_timer; // declares a game timer

    // Opens game window
    open_window("Lost In Space", 1000, 800);
    load_resources();

    game_data game = new_game();
    add_power_up(game); // Add one power-up at the start of the game

    game_timer = create_timer("game_timer");
    start_timer(game_timer); // timer variable that starts when the game starts

    while (!window_close_requested(current_window())) 
    {
        int elapsed_time = timer_ticks(game_timer); 
        time_since_last_spawn += elapsed_time;
        time_since_last_spawn_asteroid += elapsed_time;
        
        if (time_since_last_spawn >= power_up_spawn_time)
        {
            add_power_up(game);
            time_since_last_spawn = 0;
            
            // Adjust power_up_spawn_time randomly here if desired
            power_up_spawn_time = rnd(55000, 105000);  // randomize spawn time between 55000 and 105000 miliseconds
        }

        if (time_since_last_spawn_asteroid >= asteroid_spawn_time)
        {
            add_asteroid(game);
            time_since_last_spawn_asteroid = 0;
            
            // Adjust asteroid_spawn_time randomly here if desired
            asteroid_spawn_time = rnd(55000, 105000);  // randomize spawn time between 55000 and 105000 miliseconds
        }

        process_events();
        update_game(game);
        clear_screen(COLOR_BLACK); // Background colour
        draw_game(game);
        display_HUD(game.player); // Heads-Up Display

        refresh_screen();
    }

    return 0;
}