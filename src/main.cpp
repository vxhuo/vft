 
#include "../libvft/vec.hpp"


#include <raylib.h>


int main()
{
    constexpr vft::vec<float, 2> s1
    {
        .x = 100,
        .y = 100,
    };
  
    constexpr vft::vec<float, 2> e1
    {
        .x = 300,
        .y = 500,
    };
    
    
    constexpr vft::vec<float, 2> s2
    {
        .x = 490,
        .y = 200,
    };
    
     
    constexpr vft::vec<float, 2> e2
    {
        .x = 250,
        .y = 310,
    };

    

    vft::vec<float, 2> st;
    st.x = s1.x;
    st.y = s1.y;
    
    vft::vec<float, 2> et;
    et.x = e1.x;
    et.y = e1.y;


    InitWindow(500, 500, "hello world");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();


        DrawLineV({s1.x, s1.y}, {e1.x, e1.y}, MAGENTA);
        DrawLineV({s2.x, s2.y}, {e2.x, e2.y}, RED);

        DrawLineV({st.x, st.y}, {et.x, et.y}, GREEN);


        static float t{};
        if (t >= 1)
        {
            t = 0;
            st = s1;
            et = e1;
        }            
        t += 0.01f;
        st = vft::lerp(s1, s2, t);
        et = vft::lerp(e1, e2, t);


        EndDrawing();
    }
    CloseWindow();
}
