#ifndef STATE_H
#define STATE_H

// NOTE: In C++, struct is the same thing as class, except everything is public.
// NOTE: Additionally, C++ inheritance is private by default for classes, but public for structs.
// NOTE: So, ```struct foo : bar``` is equivalent to ```class foo: public bar```
// NOTE:   if bar is also a struct (or class, respectively)

struct State {
    virtual void init() {};
    virtual void update() = 0;
    virtual void draw() const = 0; // NOTE(andai): const means it should not modify the object
    virtual void unload() {};
    State* switchTo = nullptr;
    State* transTo = nullptr;
    // NOTE(andai): Adapted from C code. Unload appears to be for resources.
    // TODO(andai): Should Init and Unload be replaced with constructor and destructor?
    // TODO(andai): Is it appropriate to load and unload resources in constructor and destructor?
    // TODO(andai): Is that what RAII is? Why do game devs dislike RAII?
    //
    //              EDIT: Putting resource loading in constructor is apparently terrible
    //                    More generally, tying resources to class instances is also terrible.
};

#endif // header guard