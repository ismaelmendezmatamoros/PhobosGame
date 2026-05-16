#pragma once

namespace Phobos::Io {

    enum class DeviceType : int {
        keyboard,
        Mouse,
        Controller,
    };

    enum class InitializeDeviceMaskType : int {
        None = 0,
        Keyboard = 1,
        Mouse = 2,
        Controller = 4,
        All = -1
    };

    struct IoConfiguration {
        int InitializeDeviceMask{static_cast<int>(InitializeDeviceMaskType::All)};
    };
    
    enum class KeyStatus {
        NotPressed,
        Pressed,
        StillPressed,
        Released
    };

    enum class KeyType: int;
    struct KeyInfo {
        int keyId;
        KeyStatus status{KeyStatus::NotPressed};
        double pressureX{0.0};
        double pressureY{0.0};
    };

    enum class KeyBoardKeyType: int {
        Key_Q,
        Key_W,
        Key_E,
        Key_R,
        Key_T,
        Key_Y,
        Key_U,
        Key_I,
        Key_O,
        Key_P,
        Key_A,
        Key_S,
        Key_D,
        Key_F,
        Key_G,
        Key_H,
        Count
    };
}
