#ifndef _MBDL_DISPLAY_H_
#define _MBDL_DISPLAY_H_

#include "pros/apix.h"

namespace mbdl::display {
class Style {
public:
    /**
	 * Initializes the style based on a LVGL base style
	 * 
	 * @param base the pointer to the base style
	 */
    Style(lv_style_t* base);

    /**
	 * Returns a modifiable reference to the style
	 */
    lv_style_t& set();

    /**
	 * Returns a non-modifiable reference to the style
	 */
    const lv_style_t& get();

private:
    lv_style_t data;
};

class Object {
public:
    /**
	 * Deletes the object
	 */
    ~Object();

    /**
	 * Sets the x position of the object
	 * 
	 * @param x the x position where (0, 0) is the top left corner
	 */
    void setX(std::int16_t x);

    /**
	 * Sets the y position of the object
	 *  
	 * @param y the y position where (0, 0) is the top left corner
	 */
    void setY(std::int16_t y);

    /**
	 * Sets the x, y position of the object
	 * 
	 * @param x the x position where (0, 0) is the top left corner
	 * @param y the y position where (0, 0) is the top left corner
	 */
    void setPos(std::int16_t x, std::int16_t y);

    /**
	 * Sets the width and height of the object
	 * 
	 * @param w the width of the object
	 * @param h the height of the object
	 */
    void setSize(std::int16_t w, std::int16_t h);

    /**
	 * Sets the height of the object
	 * 
	 * @param h the height of the object
	 */
    void setHeight(std::int16_t h);

    /**
	 * Sets the width of the object
	 * 
	 * @param w the width of the object
	 */
    void setWidth(std::int16_t w);

    /**
	 * Sets the style of the object
	 * 
	 * @param style the reference to the style pointer
	 */
    void setStyle(Style& style);

    lv_obj_t* obj;
};

class Button : public Object {
public:
    /**
	 * Creates a button object with a text label and callback
	 * 
	 * @param text the text for the internal label
	 * @param func the callback function
	 * @param parent the parent object to render inside of
	 */
    Button(const char text[], lv_action_t func, lv_obj_t* parent = nullptr);

    /**
	 * Sets the text of the label
	 * 
	 * @param text the text for the internal label
	 */
    void setText(const char text[]);

    /**
	 * Sets the callback for the button
	 * 
	 * @param func the callback function
	 */
    void setCallback(lv_action_t func);

private:
    lv_obj_t* label;
};

class ButtonGroup : public Object {
public:
    /**
	 * Creates a button group
	 * 
	 * @param text the text for the internal label
	 * @param func the callback function
	 * @param parent the parent object to render inside of
	 */
    ButtonGroup(const char* map[], lv_btnm_action_t func, lv_obj_t* parent = nullptr);
};

class Label : public Object {
public:
    /**
	 * Creates a label with the specified text
	 * 
	 * @param text the text for the label
	 * @param parent the parent object to render inside of
	 */
    Label(const char text[], lv_obj_t* parent = nullptr);

    /**
	 * Sets the text of the label
	 * 
	 * @param text the text for the label
	 */
    void setText(const char text[]);
};

class Tabs : public Object {
public:
    /**
	 * Creates a tabview
	 * 
	 * @param list the list of the names of the tabs
	 * @param parent the parent object to render inside of
	 */
    Tabs(std::initializer_list<const char*> list, lv_obj_t* parent = nullptr);

    /**
	 * Returns a pointer to a tabs object
	 * 
	 * @param i the index of the tab
	 */
    lv_obj_t* operator[](std::uint8_t i);

private:
    std::uint8_t size;
    lv_obj_t** tabs;
};

namespace lcd {
    /**
	 * Turns on the LLEMU and fills the screen
	 */
    void on();

    /**
	 * Turns of the LLEMU and clears the screen
	 */
    void off();

    /**
	 * Tests if the left button is pressed
	 * 
	 * @return whether the button is pressed or not
	 */
    bool left();

    /**
	 * Tests if the center button is pressed
	 * 
	 * @return whether the button is pressed or not
	 */
    bool center();

    /**
	 * Tests if the center button is pressed
	 * 
	 * @return whether the button is pressed or not
	 */
    bool right();

    /**
	 * Blocks until all buttons are released
	 */
    void waitUntilReleased();

    /**
	 * Prints text to the LLEMU screen
	 * 
	 * @param line the line to print the text
	 * @param text the text to print on the line
	 */
    void print(std::uint8_t line, std::string text);

    /**
	 * Registers a callback to the specified button
	 * 
	 * @param line the line to print the text (ex: LCD_BTN_LEFT)
	 * @param text the text to print on the line
	 */
    void setCallback(std::uint8_t btn, void (*func)());
}
}

#endif