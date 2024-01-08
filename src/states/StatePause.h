#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H

struct StatePause : State {
    // void init();
    void update();
    void draw() const;
    // void unload();
    // virtual void unload(); // TODO(andai): did this work?
};

#endif // header guard