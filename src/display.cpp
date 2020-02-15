#include "mbdl/display.h"

namespace mbdl::display {
Object::~Object()
{
    lv_obj_del(obj);
}

void Object::setX(std::int16_t x)
{
    lv_obj_set_x(obj, x);
}

void Object::setY(std::int16_t y)
{
    lv_obj_set_y(obj, y);
}

void Object::setPos(std::int16_t x, std::int16_t y)
{
    lv_obj_set_pos(obj, x, y);
}

void Object::setWidth(std::int16_t w)
{
    lv_obj_set_width(obj, w);
}

void Object::setHeight(std::int16_t h)
{
    lv_obj_set_height(obj, h);
}

void Object::setSize(std::int16_t w, std::int16_t h)
{
    lv_obj_set_size(obj, w, h);
}

Button::Button(const char text[], lv_action_t func, lv_obj_t* parent)
{
    if (parent == nullptr) {
        parent = lv_scr_act();
    }
    obj = lv_btn_create(parent, NULL);
    label = lv_label_create(obj, NULL);
    setCallback(func);
    setText(text);
}

void Button::setText(const char text[])
{
    lv_label_set_text(label, text);
}

void Button::setCallback(lv_action_t func)
{
    lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, func);
}

ButtonGroup::ButtonGroup(const char* map[], lv_btnm_action_t func, lv_obj_t* parent)
{
    if (parent == nullptr) {
        parent = lv_scr_act();
    }
    obj = lv_btnm_create(parent, NULL);
    lv_btnm_set_map(obj, map);
    lv_btnm_set_action(obj, func);
}

Label::Label(const char text[], lv_obj_t* parent)
{
    if (parent == nullptr) {
        parent = lv_scr_act();
    }
    obj = lv_label_create(parent, NULL);
    setText(text);
}

void Label::setText(const char text[])
{
    lv_label_set_text(obj, text);
}

Tabs::Tabs(std::initializer_list<const char*> list, lv_obj_t* parent)
{
    if (parent == nullptr) {
        parent = lv_scr_act();
    }
    obj = lv_tabview_create(parent, NULL);
    size = list.size();
    tabs = new lv_obj_t*[size];
    std::initializer_list<const char*>::iterator listPointer = list.begin();
    for (int i = 0; i < size; i++) {
        tabs[i] = lv_tabview_add_tab(obj, *(listPointer + i));
    }
}

lv_obj_t* Tabs::operator[](std::uint8_t i)
{
    return tabs[i];
};

namespace lcd {
    void on()
    {
        pros::lcd::initialize();
    }

    void off()
    {
        if (pros::lcd::is_initialized()) {
            pros::lcd::shutdown();
        }
    }

    bool left()
    {
        return (pros::lcd::read_buttons() == LCD_BTN_LEFT);
    }

    bool center()
    {
        return (pros::lcd::read_buttons() == LCD_BTN_CENTER);
    }

    bool right()
    {
        return (pros::lcd::read_buttons() == LCD_BTN_RIGHT);
    }

    void waitUntilReleased()
    {
        while ((pros::lcd::read_buttons() != 0)) {
            pros::delay(10);
        }
    }

    void print(std::uint8_t line, std::string text)
    {
        pros::lcd::set_text(line, text);
    }

    void setCallback(std::uint8_t btn, void (*func)())
    {
        switch (btn) {
        case LCD_BTN_LEFT:
            pros::lcd::register_btn0_cb(func);
            break;
        case LCD_BTN_CENTER:
            pros::lcd::register_btn1_cb(func);
            break;
        case LCD_BTN_RIGHT:
            pros::lcd::register_btn2_cb(func);
            break;
        }
    }
}
}