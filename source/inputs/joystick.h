#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

namespace Alice
{

/* A simple struct handling all axes and button inputs of a joystick. */
struct Joystick
{
    std::vector<bool> buttons;
    std::vector<float> axes;

    Joystick(std::size_t const numberOfButtons, std::size_t const numberOfAxes):
        buttons(numberOfButtons, false), axes(numberOfAxes, 0.0f)
    {
    }
};

std::ostream& operator<<(std::ostream& os, const Joystick& joystick);

/* A convenient type to identify specific joysticks. */
using JoystickId = std::size_t;

/* Convenient storage for all joysticks. They can be accessed by their id.
 * Do note that due to connections and disconnections, the joystick ids may not be succesive numbers.
 * This way, to use an std::vector would require additional logic. */
using JoystickContainer = std::unordered_map<JoystickId, Joystick>;

/* joysticks is not const as we detect connections and disconnections of joystics. */
void pollJoysticks(JoystickContainer& joysticks);

} // namespace Alice