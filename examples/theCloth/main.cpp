#include <iostream>

#include <raylib.h>
#include <raymath.h> //Needed for most Raylib math functions
#include <cyclone/cyclone.h>
#include <imgui.h>
#include <rlImGui.h>
#include <vector>

#include <ew/camera.h>

#include "ew/conversions.h"

struct AppSettings {
    float spinSpeed = 2.0f; //Radians per second
    Vector3 position; //Position of the cube
    Vector2 mousePosition;

    int currentLayout = 0;
    Color cubeColor = RED;
    std::vector<cyclone::Vector3> pointList;

}_appSettings;

enum class Layouts {
    TopAnchored = 0,
    OneAnchor,
    TwoAnchors,
    FourAnchors,
    COUNT // Helper to track total items
};

int main() {
    // Initialization
   //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Hello World");

    rlImGuiSetup(true);
    Camera3D camera = { 0 };
    camera.position = {0.0f, 10.0f, 15.0f };   // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };       // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };           // Camera up vecto
    camera.fovy = 45.0f;                        // Camera vertical field-of-view in degrees
    camera.projection = CAMERA_PERSPECTIVE;     // Camera projection type - perspective vs orthographic

    // Function Introduction
    void SetupLayout(int layout);

    const char* layoutNames[] = { "TopAnchored", "OneAnchor", "TwoAnchors", "FourAnchors" };
    static_assert(IM_ARRAYSIZE(layoutNames) == static_cast<int>(Layouts::COUNT), "Array size mismatch");

    // Cube Stuff
    cyclone::Vector3 cubePosition(0.0f, 0.0f, 0.0f);
    float cubeYaw = 0.0f;
    Model cubeModel = LoadModelFromMesh(GenMeshCube(2, 2, 2));
    Model sphereModel = LoadModelFromMesh(GenMeshSphere(0.5, 4, 4));

    // Point Stuff
    SetupLayout(0);

    while (!WindowShouldClose()) {
        //Seconds between previous frame and this one
        float deltaTime = GetFrameTime();
        
        //Input
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            DisableCursor();
        }
        if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
            EnableCursor();
        }
        //Only allow movement if the cursor is hidden
        if (IsCursorHidden()) {
            ew::UpdateFlyCamera(&camera, deltaTime);
        }

        //Spin the cube
        cubeYaw += _appSettings.spinSpeed * deltaTime;

        //Model.transform allows us to modify the model (local->world) matrix directly
        //Concatenation order is left to right
        //Note that Raylib does come with optional operator overloads for C++!
        cubeModel.transform = MatrixRotateY(cubeYaw) * MatrixTranslate(cubePosition.x, cubePosition.y, cubePosition.z);

        //Drawing
        BeginDrawing();

        //3D mode draws objects in right-handed vector space
        BeginMode3D(camera);
        ClearBackground(SKYBLUE);


        switch (_appSettings.currentLayout)
        {
            default: // This is top anchor
                for (int i = 0; i < _appSettings.currentLayout + 1; i++)
                {
                    DrawModel(cubeModel, {static_cast<float>(i) * 5, 0, 0}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(cubeModel, { static_cast<float>(i) * 5,0,0 }, 1.0f, BLACK);

                }
                for (auto point: _appSettings.pointList)
                {
                    DrawModel(sphereModel, { ew::CTR(point)}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(sphereModel, { ew::CTR(point)}, 1.0f, BLACK);
                }

                break;

            case static_cast<int>(Layouts::OneAnchor):
                for (int i = 0; i < _appSettings.currentLayout + 1; i++)
                {
                    DrawModel(cubeModel, {static_cast<float>(i) * 5, 0, 0}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(cubeModel, { static_cast<float>(i) * 5,0,0 }, 1.0f, BLACK);
                }
                for (auto point: _appSettings.pointList)
                {
                    DrawModel(sphereModel, { ew::CTR(point)}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(sphereModel, { ew::CTR(point)}, 1.0f, BLACK);
                }

                break;

            case static_cast<int>(Layouts::TwoAnchors):
                for (int i = 0; i < _appSettings.currentLayout + 1; i++)
                {
                    DrawModel(cubeModel, {static_cast<float>(i) * 5, 0, 0}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(cubeModel, { static_cast<float>(i) * 5,0,0 }, 1.0f, BLACK);
                }
                for (auto point: _appSettings.pointList)
                {
                    DrawModel(sphereModel, { ew::CTR(point)}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(sphereModel, { ew::CTR(point)}, 1.0f, BLACK);
                }

                break;

            case static_cast<int>(Layouts::FourAnchors):
                for (int i = 0; i < _appSettings.currentLayout + 1; i++)
                {
                    DrawModel(cubeModel, {static_cast<float>(i) * 5, 0, 0}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(cubeModel, { static_cast<float>(i) * 5,0,0 }, 1.0f, BLACK);
                }
                for (auto point: _appSettings.pointList)
                {
                    DrawModel(sphereModel, { ew::CTR(point)}, 1.0f, _appSettings.cubeColor);
                    DrawModelWires(sphereModel, { ew::CTR(point)}, 1.0f, BLACK);
                }

                break;
        }

        DrawGrid(100, 1.0f);

        EndMode3D();

        //Outside of 3D mode, we can draw 2D things directly to the screen in pixel coordinates
        DrawCircle(32, 32, 16.f, BLUE);
        DrawText("RayLib Text!", 64, 16, 32, WHITE);
        DrawFPS(GetScreenWidth() - 128, 16);

        //ImGUI
        //All ImGui calls must be between rlGuiBegin() and rlImGuiEnd()
        rlImGuiBegin();
        ImGui::Begin("SETTINGS");
        ImGui::DragFloat("SpinSpeed", &_appSettings.spinSpeed);

        ImGui::Text("Room Layout");

        if (ImGui::Combo(" ", &_appSettings.currentLayout, layoutNames, IM_ARRAYSIZE(layoutNames)))
        {
            SetupLayout((int)_appSettings.currentLayout);
        }

        ImGui::End();

        // ImGui::ShowDemoWindow(&open);

        rlImGuiEnd();

        EndDrawing();
    }
    UnloadModel(cubeModel);
    CloseWindow();
}

void SetupLayout(int layout)
{
    switch (layout)
    {
        default: // This is top anchor
            _appSettings.cubeColor = RED;
            _appSettings.pointList.clear();

            for (int i = 0; i < layout + 1; i++)
            {
                float angle = (2.0f * PI * static_cast<float>(i)) / static_cast<float>(layout) + 1.0f;
                _appSettings.pointList.emplace_back( cosf(angle), sinf(angle) + 5, 0 );
            }
            break;

        case 1:
            _appSettings.cubeColor = BLUE;
            _appSettings.pointList.clear();

            for (int i = 0; i < layout + 1; i++)
            {
                float angle = (2.0f * PI * i) / layout + 1;
                _appSettings.pointList.emplace_back( cosf(angle), sinf(angle) + 5, 0 );
            }
            break;

        case 2:
            _appSettings.cubeColor = GREEN;
            _appSettings.pointList.clear();

            for (int i = 0; i < layout + 1; i++)
            {
                float angle = (2.0f * PI * i) / layout + 1;
                _appSettings.pointList.emplace_back( cosf(angle), sinf(angle) + 5, 0 );
            }
            break;

        case 3:
            _appSettings.cubeColor = YELLOW;
            _appSettings.pointList.clear();

            for (int i = 0; i < layout + 1; i++)
            {
                float angle = (2.0f * PI * i) / layout + 1;
                _appSettings.pointList.emplace_back( cosf(angle), sinf(angle) + 5, 0 );
            }
            break;
    }
}