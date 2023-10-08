#include "splashkit.h"
#include "power_up.h"

/**
 * The power_up bitmap function converts a power up kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power up you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap power_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case SHIELD:
        return bitmap_named("shield");
    case HEART:
        return bitmap_named("heart");
    case POWER:
        return bitmap_named("power");
    case FUEL:
        return bitmap_named("fuel");
    case DIAMOND:
        return bitmap_named("diamond");
    default:
        return bitmap_named("shield");
    }
}

/**
 * 
 *
 * @param  x,y  
 * @returns     
 */

power_up_data new_power_up(double x, double y)
{
    power_up_data result;
    result.kind = static_cast<power_up_kind>(rnd(6));

    //create the power up with any random power up bitmap
    result.power_up_sprite = create_sprite(power_bitmap(result.kind));


    // Position the sprite within the boundary
    sprite_set_x(result.power_up_sprite, rnd(-1500, 1500));
    sprite_set_y(result.power_up_sprite, rnd(-1500, 1500));

    // Add a random velocity to the power-up
    sprite_set_dx(result.power_up_sprite, rnd(-1, 1));
    sprite_set_dy(result.power_up_sprite, rnd(-1, 1));

    return result;
}

//drawing the power up
void draw_power_up(const power_up_data &power_up_to_draw)
{
    draw_sprite(power_up_to_draw.power_up_sprite);
}

//updating the power up
void update_power_up(power_up_data &power_up_to_update)
{
    // Update the power-up's sprite, which will move the power-up according to its velocity
    update_sprite(power_up_to_update.power_up_sprite);

    // Get the power-up's current position
    double x = sprite_x(power_up_to_update.power_up_sprite);
    double y = sprite_y(power_up_to_update.power_up_sprite);

    // If the power-up is outside the boundary, reverse its direction
    if (x < -1500.0 || x > 1500.0)
    {
        sprite_set_dx(power_up_to_update.power_up_sprite, -sprite_dx(power_up_to_update.power_up_sprite));
    }
    if (y < -1500.0 || y > 1500.0)
    {
        sprite_set_dy(power_up_to_update.power_up_sprite, -sprite_dy(power_up_to_update.power_up_sprite));
    }
}