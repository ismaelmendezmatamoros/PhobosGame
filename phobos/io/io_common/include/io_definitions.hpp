#pragma once

#include <variant>

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
    

    enum class KeyStatus: int {
        NotPressed,
        Pressed,
        StillPressed,
        Released,
        Unknown
    };

    struct ControlAxisData {
        KeyStatus status;
        float x{0};
        float y{0};
        float pressure{0};
    };

    struct ControllerStatus {
        ControlAxisData leftJoy;
        ControlAxisData rightJoy;
        /// TODO
    };

    struct BasicAction {
        float up;
        float down;
        float left;
        float right;
        bool shot;
        bool jump;
        bool start;
    };

    using DeviceElementDescriptor = std::variant<KeyStatus>;
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
        Key_J,
        Key_K,
        Key_L,
        Key_Ñ,
        Key_Z,
        Key_X,
        Key_C,
        Key_V,
        Key_B,
        Key_N,
        Key_M,
        Key_LSHIFT,
        Key_RSHIFT,
        Key_LCTRL,
        Key_ALT,
        Key_SPACE,
        Key_ALTGR,
        Key_RCTRL,
        Key_APOSTROPHE,
        Key_COMMA,
        Key_MINUS,
        Key_PERIOD,
        Key_SLASH,
        Unknown,
        Count
    };

    //using int = std::variant<KeyBoardKeyType>;

    struct KeyInfo {
        KeyBoardKeyType keyId;
        KeyStatus status{KeyStatus::NotPressed};
    };


}
