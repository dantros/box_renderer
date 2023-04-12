#pragma once

#include <functional>
#include <unordered_map>
#include <deque>
#include "keyboard.h"

namespace Alice
{

using Action = std::function<void()>;
using KeyActions = std::unordered_map<::Alice::Key, Action>;
using ActiveKeys = std::deque<::Alice::Key>;

/* \brief true returned on successful operation. */
class Controller
{
public:
    Controller() = default;

    bool onKeyPress(::Alice::Key key, Action action);

    bool deleteAction(::Alice::Key key);

    void processInputs();

    void press(::Alice::Key key);

private:
    KeyActions mKeyActions;
    ActiveKeys mActiveKeys;
};


} // namespace Alice