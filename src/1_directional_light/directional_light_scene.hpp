#ifndef DIRECTIONAL_LIGHT_SCENE_HPP
#define DIRECTIONAL_LIGHT_SCENE_HPP

#define GLM_FORCE_CXX11
#include <glm/glm.hpp>

#include <scene.hpp>
#include <shader.hpp>
#include <mesh/mesh.hpp>
#include <textures/texture2d.hpp>
#include <camera/camera.hpp>
#include <camera/controllers/fly_camera_controller.hpp>

enum TextureType {
    ALBEDO = 0,
    SPECULAR = 1,
    ROUGHNESS = 2,
    AMBIENT_OCCLUSION = 3,
    EMISSIVE = 4
};

class DirectionalLightScene : public Scene {
private:
    Shader* shader;
    Shader* skyShader;
	Shader* terrainShader;
    Mesh* ground;
	Mesh* plane;
    Mesh* sky;
    Mesh* model;
	Mesh* ghost;
	Mesh* table;
	Mesh* chair;
	Mesh* Bigtree;
	Mesh*wolfff;
	Mesh* bird1;

	Texture2D*List_1_dom_derevnja;
	Texture2D*List_2_dom_derevnja;
	Texture2D*List_4_dom_derevnja;
	Texture2D* heightmap;
	Texture2D* bottomTex;
	Texture2D*	topTex;
    Texture2D* metal[5];
    Texture2D* wood[5];
	Texture2D* wood2[5];
    Texture2D* asphalt[5];
    Texture2D* checkers[5];
	Texture2D* grass[5];
	Texture2D* wolf[5];
	Texture2D *birdd[5];

    Camera* camera;
    FlyCameraController* controller;
	Texture2D*bigtreetexture;
	Texture2D*wolftexture;
	Texture2D*birdtexture;
	float dinasoreRotation;

	int mvpLoc ,
	texLoc,
	tilingLoc,
	bottomLoc , 
	topLoc ;

    float sunYaw, sunPitch;
	float modelFront, modelSide, fly, fly2, moveing;
	float x, y, z;
public:
    DirectionalLightScene(Application* app): Scene(app) {}

    void Initialize() override;
    void Update(double delta_time) override;
    void Draw() override;
    void Finalize() override;
};

#endif