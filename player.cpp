#include "player.h"
#include "splashkit.h"

/**
 * The ship bitmap function converts a ship kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    default:
        return bitmap_named("pegasi");
    }
}

player_data new_player()
{
    player_data result;
    result.score = 0;
    bitmap default_bitmap = ship_bitmap(AQUARII);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // Default to layer 0 = Aquarii so hide others
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);

    result.kind = AQUARII;

    result.player_sprite = create_sprite(ship_bitmap(result.kind));
    sprite_set_dx(result.player_sprite, PLAYER_SPEED);  // Horizontal speed
    sprite_set_dy(result.player_sprite, PLAYER_SPEED);  // Vertical speed

    // Set the player's initial position to the center of the screen
    double initial_x = (screen_width() - sprite_width(result.player_sprite)) / 2;
    double initial_y = (screen_height() - sprite_height(result.player_sprite)) / 2;
    sprite_set_x(result.player_sprite, initial_x);
    sprite_set_y(result.player_sprite, initial_y);
    
    // Set the initial velocity to 0
    sprite_set_dx(result.player_sprite, 0);
    sprite_set_dy(result.player_sprite, 0);


    //set percentage of guage of power ups
    result.fuel_pct = 0.75; // starts at 75% fuel
    result.health_pct = 0.25; // starts at 25% health
    result.shield_pct = 0.50; // starts at 50% shield

    return result;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    sprite player_sprite = player_to_update.player_sprite;

    // If there is still fuel, it will update the sprite and reduce fuel by 0.000278
    if (player_to_update.fuel_pct > 0 && (sprite_dx(player_sprite) != 0 || sprite_dy(player_sprite) != 0))
    {
        update_sprite(player_sprite);
        player_to_update.fuel_pct -= 0.00001;  // fuel reduction number

        if(sprite_x(player_sprite) < -1500) sprite_set_x(player_sprite, -1500);
        if(sprite_x(player_sprite) > 1500) sprite_set_x(player_sprite, 1500);
        if(sprite_y(player_sprite) < -1500) sprite_set_y(player_sprite, -1500);
        if(sprite_y(player_sprite) > 1500) sprite_set_y(player_sprite, 1500);
    }

    // Apply movement based on rotation and velocity in the sprite
    if (player_to_update.fuel_pct > 0)
    {
        update_sprite(player_to_update.player_sprite);
    }

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER + 50;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Test if the player is outside the area and move the camera
    // the player will appear to stay still and everything else
    // will appear to move :)

    // Test top/bottom of screen
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }

    // Ensures that fuel doesn't go below 0
    if (player_to_update.fuel_pct < 0)
    {
        player_to_update.fuel_pct = 0;
    }
}

/**
 * Switch the ship kind - will adjust which layer is hidden/shown
 */
void player_switch_to_ship(player_data &player, ship_kind target)
{
    // only do this if there is a change
    if (player.kind != target)
    {
        // show then hide layers
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.kind));

        // remember what is currently shown
        player.kind = target;
    }
}

void handle_input(player_data &player)
{
    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_to_ship(player, AQUARII);
    if (key_typed(NUM_2_KEY))
        player_switch_to_ship(player, GLIESE);
    if (key_typed(NUM_3_KEY))
        player_switch_to_ship(player, PEGASI);

    // Handle movement - rotating left/right and moving forward/back
    float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases
    if (key_typed(DOWN_KEY))
        sprite_set_dx(player.player_sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(player.player_sprite, dx + PLAYER_SPEED);
    
}