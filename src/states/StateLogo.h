#ifndef STATE_LOGO_H
#define STATE_LOGO_H

struct StateLogo : State {
    void init();
    void update();
    void draw() const;
    // void unload(); // inherited
};

#endif // header guard