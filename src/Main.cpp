/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>
#include <raymath.h>
#include "Globals.h" // declare globals ("extern"): font, music, states
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <iostream>
#include <time.h> // seed randomness
#include <assert.h>
#include "VectorOverload.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through Globals.h
//----------------------------------------------------------------------------------
// GameScreen currentScreen = LOGO;

// NOTE(andai): States are global (Globals.h)
StateLogo stateLogo;
StateMenu stateMenu;
StatePause statePause;
StatePlay statePlay;
StateWin stateWin;

// NOTE(andai): states currently unused.
// TODO(andai): move GameWorld code into states?

State* state = &stateLogo;

Font font = { 0 };
Music music = { 0 };
//Sound fxCoin = { 0 };

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
//static const int screenWidth = 800;
//static const int screenHeight = 450;

bool gameOver = false;


Player player{
    Vector2{(float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT/2},
    Vector2{0,0},
    100
};

//#define ASTEROIDS_COUNT 1000
//#define ASTEROIDS_INIT_COUNT 100

//#define ASTEROIDS_COUNT 20000
//#define ASTEROIDS_INIT_COUNT 20000

// #define ASTEROIDS_COUNT 5000
// #define ASTEROIDS_INIT_COUNT 5000

#define ASTEROIDS_COUNT 1000
#define ASTEROIDS_INIT_COUNT 20

Asteroid asteroids[ASTEROIDS_COUNT];
size_t asteroids_idx = 0;
//
//
#define BULLETS_COUNT 500

Bullet bullets[BULLETS_COUNT];
size_t bullets_idx = 0;





// BANANA

void asteroids_init();
bool asteroids_spawn(float r);
void asteroids_spawn_at(Vector2 pos, Vector2 vel, float r);
void asteroids_update();
void asteroids_draw();
//
void bullets_spawn_at(Vector2 pos);
void bullets_update();
void bullets_draw();







// Required variables to manage screen transitions (fade-in, fade-out)
// static float transAlpha = 0.0f;
// static bool onTransition = false;
// static bool transFadeOut = false;


// static GameScreen nextState = UNKNOWN;

static State* nextState = nullptr;
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void SwitchToState(State* _state);     // Change to screen, no transition effect

// static void TransitionToScreen(State* _nextState); // Request transition to next screen
// static void updateTransition(void);         // Update transition effect
// static void drawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame(void);          // Update and draw one frame
static void update();
static void draw();

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{   
    std::cout << "main();\n";
    srand(time(NULL));


    SetTraceLogLevel(LOG_DEBUG);
    
    // Initialization
    //---------------------------------------------------------
    std::cout << "main() calling InitWindow();\n";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib game template");
    std::cout << "main() calling InitAudioDevice();\n";
    InitAudioDevice();      // Initialize audio device
    //GameWorld gameWorld;
    // Load global data (assets that must be available in all screens, i.e. font)
    // font = LoadFont("res/mecha.png");
    std::cout << "main() calling LoadFont();\n";
    font = LoadFont("res/Anonymous_Pro.ttf"); // TODO(andai): add credits page with scrolling font license lol
    // music = LoadMusicStream("res/pong_soundtrack.mp3"); // TODO(andai): replace with copyright-free music for release
    // fxCoin = LoadSound("res/coin.wav");

    // SetMusicVolume(music, 1.0f);
    //PlayMusicStream(music);


    player.pos = {
        (float)GetScreenWidth()/2,
        (float)GetScreenHeight()/2
    };

    asteroids_init(); // BANANA




    // Setup and init first screen
    // currentScreen = LOGO;
    // InitLogoScreen();
    // NOTE: states currently unused
    state = &stateLogo;
    // std::cout << "main() calling state->init();\n";
    // state->init();

#if defined(PLATFORM_WEB)
    std::cout << "main() calling emscripten_set_main_loop(UpdateDrawFrame);\n";
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    std::cout << "main() calling SetTargetFPS(60);\n";
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        std::cout << "main() calling UpdateDrawFrame();\n";
        UpdateDrawFrame();
    }
#endif

    state->unload();

    // Unload global data loaded
    UnloadFont(font);
    // UnloadMusicStream(music);
    // UnloadSound(fxCoin);

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


static void SwitchToState(State* _state)
{
    state->unload();
    state = _state;
    state->init();
}






// // Request transition to next screen
// static void TransitionToScreen(State* _nextState)
// {
//     onTransition = true;
//     transFadeOut = false;
//     nextState = _nextState;
//     transAlpha = 0.0f;
// }


// // Update transition effect (fade-in, fade-out)
// static void updateTransition(void)
// {
//     if (!transFadeOut)
//     {
//         transAlpha += 0.05f;

//         // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
//         // For that reason we compare against 1.01f, to avoid last frame loading stop
//         if (transAlpha > 1.01f)
//         {
//             transAlpha = 1.0f;

//             SwitchToState(nextState);

//             // Activate fade out effect to next loaded screen
//             transFadeOut = true;
//         }
//     }
//     else  // Transition fade out logic
//     {
//         transAlpha -= 0.02f;

//         if (transAlpha < -0.01f)
//         {
//             transAlpha = 0.0f;
//             transFadeOut = false;
//             onTransition = false;
//             nextState = nullptr;
//         }
//     }
// }


// // Draw transition effect (full-screen rectangle)
// static void drawTransition(void)
// {
//     DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
// }







/////////////

static void UpdateDrawFrame()
{
    std::cout << "UpdateDrawFrame();\n";
    update();
    draw();
}

static void update()
{
    std::cout << "update();\n";
    // UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

#ifdef PONG_USING_STATES
    if (!onTransition) {
        state->update();
        if (state->transTo) {
            TransitionToScreen(state->transTo);
            state->transTo = nullptr;
        }
        if (state->switchTo) {
            SwitchToState(state->switchTo);
            state->switchTo = nullptr;
        }

    }else updateTransition();    // Update transition (fade-in, fade-out)
#endif
    //gameWorld.HandleInput();
    //gameWorld.Update();

    // BANANA
    asteroids_update();
    bullets_update();


    player.update();
}



static void draw()
{
    std::cout << "draw();\n";
    BeginDrawing();
    {
        // ClearBackground(RAYWHITE); // State handles bg
        ClearBackground(Color{32, 32, 32});

#ifdef PONG_USING_STATES
        state->draw();

        // Draw full screen rectangle in front of everything
        if (onTransition) drawTransition();
#endif
        //gameWorld.Draw();


        // BANANA
        asteroids_draw();
        bullets_draw();



        player.draw();
        //DrawLineEx(Vector2{ 200,300 }, Vector2{300,400}, 10.f, RED);

        if (gameOver) {
            // void DrawText(const char *text, int posX, int posY, int fontSize, Color color);  
            const char* text = "GAME OVER";
            DrawText(text, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 48, RED);  
        }

        DrawFPS(10, 10); // raylib builtin
    }
    EndDrawing();
}






// BANANA
void asteroids_init() {
    std::cout << "asteroids_init();\n";
    //player.color = LIME;
    //for (int i = 0; i < ASTEROIDS_INIT_COUNT; i++) {
    //    float r = 100.f; // TODO: based on difficulty?
    //    r = 3 * 10.f;
    //    asteroids[i] = Asteroid(r);
    //}
    for (int i = 0; i < ASTEROIDS_INIT_COUNT; i++) {
        asteroids_spawn(-1);
    }
    std::cout << "END asteroids_init();\n";
}



bool asteroids_spawn(float r = -1) {
    static int dbg_spawn = 0;
    std::cout << "asteroids_spawn(" << r << "); count: " << dbg_spawn << "\n";
    dbg_spawn++;

    //std::cout << "asteroids_spawn(" << r << ");\n";

    auto rand_int = [](int min, int max) {
        if (max < min) {
            int tmp = min;
            min = max;
            max = min;
        }
        int range = max - min + 1; // note: +1 ensures output includes max
        return min + rand() % range;
        // NOTE: rand() Returns a pseudo-random integer between 0 and RAND_MAX.
    };

    auto rand_float = [rand_int]() {
        return ((float)rand_int(0, 1000000)) / 1000000;
    };

    if (r == -1) // no r passed, make random radius
        r = 15 + rand_float() * 60; // formerly 1000
        // r = 10 + rand_float() * 30; // formerly 1000


    // find a dead one to overwrite
    size_t asteroids_idx_orig = asteroids_idx;
    while (asteroids[asteroids_idx].alive) {
        asteroids_idx++;
        asteroids_idx %= ASTEROIDS_COUNT;
        if (asteroids_idx == asteroids_idx_orig) return false; // checked all asteroids, found them alive, cannot spawn
    }
    asteroids[asteroids_idx] = Asteroid(r);
    asteroids_idx++;
    asteroids_idx %= ASTEROIDS_COUNT;
    return true;
}

void asteroids_spawn_at(Vector2 pos, Vector2 vel, float r) {
    if (!asteroids_spawn(r)) return;

    // ugly sorry
    // ideally we'd have an API that returns a size_t OR false .. but i'm not sure how to combine that in C++
    // I could make a special struct just for this but... ehh
    size_t spawn_idx;
    if (asteroids_idx == 0)
        spawn_idx = ASTEROIDS_COUNT - 1;
    else
        spawn_idx = asteroids_idx - 1;

    asteroids[spawn_idx].pos = pos;
    asteroids[spawn_idx].vel = vel;
    asteroids[spawn_idx].r = r;

 }

void asteroids_update() {
    std::cout << "asteroids_update();\n";


    if (IsKeyPressed(KEY_G)) {
        for (size_t i = 0; i < ASTEROIDS_COUNT; i++) {
            asteroids_spawn();
        }
    }

    //// spawn
    //// TODO spawn freq depend on score
    //int time_ms = (int)(GetTime() * 1000);
    //std::cout << "time: " << time_ms << "\n";
    //int frame_time = 16; // TODO make game frame rate independent, add deltaTime etc...
    //int n = 5; // every n frames
    //if (time_ms% (frame_time*5)==0)
    //    asteroids_spawn();

    // static unsigned int ast_tick = 0;
    // if (ast_tick % 30 == 0)
    //     asteroids_spawn();
    // ast_tick++;

    asteroids_spawn(-1);

    //asteroids_spawn();

    // collide
    //player.color = LIME;
    for (int i = 0; i < ASTEROIDS_COUNT; i++) {
        if (!asteroids[i].alive) continue;
        asteroids[i].update();
        if (ShapeGuy::Overlaps(player, asteroids[i])) {

            player.takeDamage((int)(asteroids[i].r/2));
            if (player.hp <= 0) {
                gameOver = true;
            }
            ////////////////////////////////////////
            // // on second thought, this was silly
            //if (player.r > asteroids[i].r) { // small asteroid
            //    asteroids[i].vel *= -0.7f; // just bounce if small asteroid
            //    asteroids[i].pos += asteroids[i].vel * 3; // remove to prevent further collision
            //    asteroids[i].vel += player.vel;

            //    player.vel += asteroids[i].vel / 2;

            //} else { // big asteroid
            //    //asteroids[i].vel *= 0.5f;
            //    //asteroids[i].vel += player.vel / asteroids[i].r;
            //    player.vel += asteroids[i].vel;
            //}

            Vector2 distVec = asteroids[i].pos - player.pos;
            asteroids[i].vel += Vector2Normalize(distVec) * 2;
            asteroids[i].pos += Vector2Normalize(distVec) * 5;


            //player.color = asteroids[i].color = RED;
        }
        else {
            //asteroids[i].color = LIME;
        }
    }
}

void asteroids_draw() {
    std::cout << "asteroids_draw();\n";
    for (int i = 0; i < ASTEROIDS_COUNT; i++) {
        if (!asteroids[i].alive) continue;
        asteroids[i].draw();
    }
}





// BANANA 2

void bullets_update() {
    std::cout << "bullets_update();\n";
    // TODO just make a random.cpp already
    auto rand_int = [](int min, int max) {
        if (max < min) {
            int tmp = min;
            min = max;
            max = min;
        }
        int range = max - min + 1; // note: +1 ensures output includes max
        return min + rand() % range;
        // NOTE: rand() Returns a pseudo-random integer between 0 and RAND_MAX.
    };


    //if (IsKeyPressed(KEY_SPACE)) {
    if (IsKeyDown(KEY_SPACE)) {

        //std::cout << "SPAWN bullet index: " << bullets_idx << "\n";


        bullets[bullets_idx] = Bullet(player.pos, player.angle);
        bullets[bullets_idx].pos += bullets[bullets_idx].vel * 0.33;
        bullets_idx++;
        bullets_idx %= BULLETS_COUNT;

        bullets[bullets_idx] = Bullet(player.pos, player.angle);
        bullets[bullets_idx].pos += bullets[bullets_idx].vel * 0.66;
        bullets_idx++;
        bullets_idx %= BULLETS_COUNT;

        bullets[bullets_idx] = Bullet(player.pos, player.angle);
        bullets_idx++;
        bullets_idx %= BULLETS_COUNT;


        // note: this overwrites oldest bullet. that's OK
    }

    //std::cout << "bullets_update();\n";
    for (int i = 0; i < BULLETS_COUNT; i++) {
        if (!bullets[i].alive) continue;
        bullets[i].update();
        //std::cout << "UPDATE bullet index: " << i << "\n";
        for (int k = 0; k < ASTEROIDS_COUNT; k++) {
            if (!asteroids[k].alive) continue;
            if (!bullets[i].alive) break;
            if (ShapeGuy::Overlaps(bullets[i], asteroids[k])) {

                Vector2 ast_p = asteroids[k].pos;
                Vector2 ast_v = asteroids[k].vel;
                float ast_r = asteroids[k].r;

                asteroids[k].takeDamage(bullets[i].dmg);
                bullets[i].takeDamage(asteroids[k].dmg); // TODO asteroid dmg?

                if (asteroids[k].alive) {
                    asteroids[k].vel += bullets[i].vel / asteroids[k].r * 0.3f;

                }else{
                    if (ast_r < 16) {
                        // small asteroid, do not spawn  child asteroids
                        // instead, spawn bullets!
                        for (int n = 0; n < 3; n++) {
                            bullets_spawn_at(ast_p);
                        }
                    }else {
                        // large asteroid, spawn child asteroids
                        for (int n = 0; n < asteroids[k].r/2 ; n++) {
                            asteroids_spawn_at(ast_p,
                                ast_v/2 // inherit parent velocity
                                  + Vector2{ (float)rand_int(-2, 2), (float)rand_int(-2, 2) } // slightly randomize dir
                                  + bullets[i].vel/15, // inherit bullet dir
                                ast_r * 0.7f);
                        }
                    }
                }
                //break; // stop checking for collision with this bullet // edit: bullets have hp now
                // NOTE: there must not be any code after this, in the outer loop,
                // else game will run code on dead bullet
            }
        }
    }
}

void bullets_spawn_at(Vector2 pos) {
    std::cout << "bullets_spawn_at();\n";
    float angle = (float)((GetRandomValue(0, PI * 2 * 1000)) / 1000);
    bullets[bullets_idx] = Bullet(pos, angle);
    bullets[bullets_idx].dmg = 300;
    bullets[bullets_idx].color = Color{255,255,0,255};
    bullets[bullets_idx].draw(); // always draw on spawn frame
    bullets_idx++;
    bullets_idx %= BULLETS_COUNT;
}

void bullets_draw() {
    std::cout << "bullets_draw();\n";
    //std::cout << "asteroids_draw();\n";
    for (int i = 0; i < BULLETS_COUNT; i++) {
        if (!bullets[i].alive) continue;
        bullets[i].draw();
    }
}