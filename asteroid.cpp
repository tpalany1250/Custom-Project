#include "asteroid.h"
#include "splashkit.h"


void load_asteroid_bitmaps()
{
    load_bitmap("pluto", "images/pluto.png");
    load_bitmap("venus", "images/venus.png");
    load_bitmap("star", "images/star.png");
}


bitmap ship_bitmap(asteroid_kind kind)
{
    switch (kind)
    {
    case PLUTO:
        return bitmap_named("pluto");
    case VENUS:
        return bitmap_named("venus");
    default:
        return bitmap_named("star");
    }
}


// asteroid_data new_asteroid()
// {
//     asteroid_data result;
//     result.score = 0;
//     bitmap default_bitmap = ship_bitmap(PLUTO);

//     // Create the sprite with 3 layers - we can turn on and off based
//     // on the ship kind selected
//     result.asteroid_sprite = create_sprite(default_bitmap);

//     sprite_add_layer(result.asteroid_sprite, ship_bitmap(VENUS), "GLIESE");
//     sprite_add_layer(result.asteroid_sprite, ship_bitmap(STAR), "PEGASI");

//     // Default to layer 0 = Aquarii so hide others
//     sprite_hide_layer(result.asteroid_sprite, 1);
//     sprite_hide_layer(result.asteroid_sprite, 2);

//     result.kind = PLUTO;

//     result.asteroid_sprite = create_sprite(ship_bitmap(result.kind));
//     sprite_set_dx(result.asteroid_sprite, ASTEROID_SPEED);  // Horizontal speed
//     sprite_set_dy(result.asteroid_sprite, ASTEROID_SPEED);  // Vertical speed

//     // Set the player's initial position to the center of the screen
//     sprite_set_x(result.asteroid_sprite, (screen_width() - sprite_width(result.asteroid_sprite)) / 2);
//     sprite_set_y(result.asteroid_sprite, (screen_height() - sprite_height(result.asteroid_sprite)) / 2);

//     // Set the initial velocity to 0
//     sprite_set_dx(result.asteroid_sprite, 0);
//     sprite_set_dy(result.asteroid_sprite, 0);

//     return result;
// }


asteroid_data new_asteroid(double x, double y)
{
    asteroid_data result;
    result.score = 0;
    bitmap default_bitmap = ship_bitmap(PLUTO);


    result.asteroid_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.asteroid_sprite, ship_bitmap(VENUS), "GLIESE");
    sprite_add_layer(result.asteroid_sprite, ship_bitmap(STAR), "PEGASI");

    sprite_hide_layer(result.asteroid_sprite, 1);
    sprite_hide_layer(result.asteroid_sprite, 2);

    result.kind = PLUTO;

    result.asteroid_sprite = create_sprite(ship_bitmap(result.kind));
    sprite_set_dx(result.asteroid_sprite, ASTEROID_SPEED);  // Horizontal speed
    sprite_set_dy(result.asteroid_sprite, ASTEROID_SPEED);  // Vertical speed

    // Set the initial position to the specified x and y coordinates
    sprite_set_x(result.asteroid_sprite, x);
    sprite_set_y(result.asteroid_sprite, y);

    // Set the initial velocity to 0
    sprite_set_dx(result.asteroid_sprite, 0);
    sprite_set_dy(result.asteroid_sprite, 0);

    return result;
}




void draw_asteroid(const asteroid_data &asteroid_to_draw)
{
    draw_sprite(asteroid_to_draw.asteroid_sprite);
}

// // Function to handle collision between the player and an asteroid
// void handle_player_collision(player_data &player, asteroid_data &asteroid)
// {
//     if (sprite_collision(player.player_sprite, asteroid.asteroid_sprite))
//     {
//         // Reduce the player's health when colliding with an asteroid
//         player.health_pct -= 0.1; // Decrease health by 10%

//         // Update the player's score (you can adjust this based on your game's scoring system)
//         player.score -= 50; // Decrease score by 50 points

//         // Remove the asteroid from the game
//         // ...
//     }
// }


void update_asteroid(asteroid_data &asteroid_to_update)
{
    // sprite asteroid_sprite = asteroid_to_update.asteroid_sprite;

 
    update_sprite(asteroid_to_update.asteroid_sprite);

    // Update the asteroid's position based on its velocity
    // sprite_set_x(asteroid_to_update.asteroid_sprite, sprite_x(asteroid_to_update.asteroid_sprite) + sprite_dx(asteroid_to_update.asteroid_sprite));
    // sprite_set_y(asteroid_to_update.asteroid_sprite, sprite_y(asteroid_to_update.asteroid_sprite) + sprite_dy(asteroid_to_update.asteroid_sprite));

    // Test edge of screen boundaries to adjust the camera
    // double left_edge = camera_x() + SCREEN_BORDER;
    // double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    // double top_edge = camera_y() + SCREEN_BORDER + 50;
    // double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // // Get the center of the player
    // point_2d sprite_center = center_point(asteroid_to_update.asteroid_sprite);

    // // Test if the player is outside the area and move the camera
    // // the player will appear to stay still and everything else
    // // will appear to move :)

    // // Test top/bottom of screen
    // if (sprite_center.y < top_edge)
    // {
    //     move_camera_by(0, sprite_center.y - top_edge);
    // }
    // else if (sprite_center.y > bottom_edge)
    // {
    //     move_camera_by(0, sprite_center.y - bottom_edge);
    // }

    // // Test left/right of screen
    // if (sprite_center.x < left_edge)
    // {
    //     move_camera_by(sprite_center.x - left_edge, 0);
    // }
    // else if (sprite_center.x > right_edge)
    // {
    //     move_camera_by(sprite_center.x - right_edge, 0);
    // }

}

