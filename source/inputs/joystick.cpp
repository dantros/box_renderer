

#include "joystick.h"
#include <GLFW/glfw3.h>
#include <iomanip>
#include "../checks.h"

namespace Alice
{


std::ostream& operator<<(std::ostream& os, const Joystick& joystick)
{
    os << "buttons: ";
    for (bool button : joystick.buttons)
    {
        os << (button ? 1 : 0);
    }
    os << " axes: ";
    for (float ax : joystick.axes)
    {
        os << std::fixed << std::setprecision(2) << std::setfill('0') << ax << " ";
    }
    return os;
}

void pollJoysticks(JoystickContainer& joysticks)
{
    for (int joystickId = GLFW_JOYSTICK_1; joystickId < GLFW_JOYSTICK_LAST; ++joystickId)
    {
        int const joystickConnected = glfwJoystickPresent(joystickId);
        if (joystickConnected == GLFW_FALSE)
        {
            if (joysticks.count(joystickId) != 0)
            {
                /* joystickId has been disconnected.*/
                joysticks.erase(joystickId);
            }
            continue;
        }

        // At this point we have a joystick with this id.
        if (joysticks.count(joystickId) == 0)
        {
            /* joystickId has been connected.*/

            int buttonsCount;
            glfwGetJoystickButtons(joystickId, &buttonsCount);

            int axesCount;
            glfwGetJoystickAxes(joystickId, &axesCount);

            joysticks.emplace(joystickId, Joystick(buttonsCount, axesCount));
        }

        Joystick& joystick = joysticks.at(joystickId);

        int buttonsCount;
        const unsigned char* buttons = glfwGetJoystickButtons(joystickId, &buttonsCount);
        debugCheck(joystick.buttons.size() == buttonsCount);

        for (int buttonId = 0; buttonId < buttonsCount; ++buttonId)
        {
            joystick.buttons[buttonId] = buttons[buttonId] == GLFW_PRESS;
        }

        int axesCount;
        const float* axes = glfwGetJoystickAxes(joystickId, &axesCount);
        debugCheck(joystick.axes.size() == axesCount);

        for (int axesId = 0; axesId < axesCount; ++axesId)
        {
            joystick.axes[axesId] = axes[axesId];
        }
    }
}


} // namespace Alice