#ifndef SPACE_SHOOTER_GAMEPAD_H
#define SPACE_SHOOTER_GAMEPAD_H

#include <SDL/SDL.h>

class Gamepad {
public:
    Gamepad(const int index)
            : index_(index)
    { joystick_ = SDL_JoystickOpen(index_); }

    ~Gamepad() { if (joystick_)  SDL_JoystickClose(joystick_); }

    bool isConnected() const { return index_ < SDL_NumJoysticks(); }
    int getAxisState(int axis) const { return SDL_JoystickGetAxis(joystick_, axis); }
    bool isButtonPressed(int button) const { return SDL_JoystickGetButton(joystick_, button); }

private:
    int index_;
    SDL_Joystick* joystick_;
};

#endif //SPACE_SHOOTER_GAMEPAD_H
