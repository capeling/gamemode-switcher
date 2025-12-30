#pragma once

namespace switcher {

enum class Action {
    None = -1,
    
    Cube = 0,
    Ship = 1,
    Ball = 2,
    Bird = 3,
    Dart = 4,
    Robot = 5,
    Spider = 6,
    Swing = 7,

    Speed0p5x = 8,
    Speed1x = 9,
    Speed2x = 10,
    Speed3x = 11,
    Speed4x = 12,

    PlatformerToggle = 13,
    ScaleToggle = 14,
    GravityToggle = 15,
    ReverseToggle = 16,
    PortalsToggle = 17,
};

}