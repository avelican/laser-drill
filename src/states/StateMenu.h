#ifndef STATE_MENU_H
#define STATE_MENU_H

struct StateMenu : State {
    void init();
    void update();
    void draw() const;
    // void unload(); // inherited
};

#endif // header guard