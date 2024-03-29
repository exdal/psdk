#include "InputManager.h"

#include "app/App.h"

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

void InputManager::Update() {
    double xpos, ypos;
    glfwGetCursorPos(GetWindow()->GetHandle(), &xpos, &ypos);
    m_mousePos = { (float)xpos, (float)ypos };

    // loop over mouse first
    for (auto &&i : m_mouseState) {
        if (i.second == INPUT_KEY_STATE_RELEASED) {
            i.second = INPUT_KEY_STATE_CLICKED;
            continue;
        }

        if (i.second != INPUT_KEY_STATE_NONE && i.second != INPUT_KEY_STATE_PRESSED)
            m_mouseState.insert_or_assign(i.first, INPUT_KEY_STATE_NONE);
    }
}

bool InputManager::IsPressed(KeyCode key) {
    return (m_keyboardState.find(key) != m_keyboardState.end() && m_keyboardState.at(key) == INPUT_KEY_STATE_PRESSED);
}

bool InputManager::IsReleased(KeyCode key) {
    return (m_keyboardState.find(key) != m_keyboardState.end() && m_keyboardState.at(key) == INPUT_KEY_STATE_RELEASED);
}

bool InputManager::IsMousePressed(MouseCode key) {
    return (m_mouseState.find(key) != m_mouseState.end() && m_mouseState.at(key) == INPUT_KEY_STATE_PRESSED);
}

bool InputManager::IsMouseReleased(MouseCode key) {
    return (m_mouseState.find(key) != m_mouseState.end() && m_mouseState.at(key) == INPUT_KEY_STATE_RELEASED);
}

bool InputManager::IsMouseClicked(MouseCode key) {
    return (m_mouseState.find(key) != m_mouseState.end() && m_mouseState.at(key) == INPUT_KEY_STATE_CLICKED);
}

void InputManager::ProcessKeyboard(int key, int scancode, int action, int mods) {
    if (action == /*GLFW_PRESS*/ 1 || action == /*GLFW_RELEASE*/ 0) {
        uint8_t kmods = INPUT_KEY_MODS_NONE;
#if PLATFORM_WINDOWS
        if ((mods & GLFW_MOD_SHIFT) > 0)
            kmods |= INPUT_KEY_MODS_SHIFT;

        if ((mods & GLFW_MOD_CONTROL) > 0)
            kmods |= INPUT_KEY_MODS_CONTROL;

        if ((mods & GLFW_MOD_ALT) > 0)
            kmods |= INPUT_KEY_MODS_ALT;

        if ((mods & GLFW_MOD_SUPER) > 0)
            kmods |= INPUT_KEY_MODS_SUPER;

        if ((mods & GLFW_MOD_NUM_LOCK) > 0)
            kmods |= INPUT_KEY_MODS_NUM_LOCK;

        if ((mods & GLFW_MOD_CAPS_LOCK) > 0)
            kmods |= INPUT_KEY_MODS_CAPS_LOCK;
#endif
        m_mods = (KeyMods)kmods;
    }

    if (action == GLFW_PRESS) {
        m_keyboardState.insert_or_assign((KeyCode)key, INPUT_KEY_STATE_PRESSED);
    }

    if (action == GLFW_RELEASE) {
        m_keyboardState.insert_or_assign((KeyCode)key, INPUT_KEY_STATE_RELEASED);
    }
}

void InputManager::ProcessMouse(int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_mouseState.insert_or_assign((MouseCode)button, INPUT_KEY_STATE_PRESSED);
    } else {
        m_mouseState.insert_or_assign((MouseCode)button, INPUT_KEY_STATE_RELEASED);
    }
}