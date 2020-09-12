#include <application.hpp>
#include "directional_light_scene.hpp"

#include <mesh/mesh_utils.hpp>
#include <textures/texture_utils.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void DirectionalLightScene::Initialize() {
    shader = new Shader();
    shader->attach("assets/shaders/directional.vert", GL_VERTEX_SHADER);
    shader->attach("assets/shaders/directional.frag", GL_FRAGMENT_SHADER);
    shader->link();

    skyShader = new Shader();
    skyShader->attach("assets/shaders/sky.vert", GL_VERTEX_SHADER);
    skyShader->attach("assets/shaders/sky.frag", GL_FRAGMENT_SHADER);
    skyShader->link();

	terrainShader = new Shader();
	terrainShader->attach("assets/shaders/terrain.vert", GL_VERTEX_SHADER);
	terrainShader->attach("assets/shaders/terrain.frag", GL_FRAGMENT_SHADER);
	terrainShader->link();
    ground = MeshUtils::Plane({0,0}, {5,5});
    sky = MeshUtils::Box();
    model = MeshUtils::LoadObj("assets/models/House/House.obj");
	ghost = MeshUtils::LoadObj("assets/models/House/Ghost.obj");

	table = MeshUtils::LoadObj("assets/models/House/table.obj");
	chair = MeshUtils::LoadObj("assets/models/House/chair.obj");

	Bigtree = MeshUtils::LoadObj("assets/models/House/Hazelnut.obj");
	wolfff = MeshUtils::LoadObj("assets/models/Wolf/Wolf.obj");
	bird1 = MeshUtils::LoadObj("assets/models/Carcharodontosaurus/carcar.obj");

	x = y = z = 1;


	dinasoreRotation = 124;
	dinasoreRotation = glm::wrapAngle(dinasoreRotation);

	//GL_REPEAT: The default behavior for textures.Repeats the texture image.
//	GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
//	GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
//	GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.

	List_1_dom_derevnja = TextureUtils::Load2DTextureFromFile("assets/models/House/House.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	List_4_dom_derevnja = TextureUtils::Load2DTextureFromFile("assets/models/House/wood.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	bottomTex = TextureUtils::Load2DTextureFromFile("assets/textures/grass_ground_d.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	topTex = TextureUtils::Load2DTextureFromFile("assets/textures/mntn_white_d.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);



	bigtreetexture = TextureUtils::Load2DTextureFromFile("assets/models/House/leavefinn.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	wolftexture = TextureUtils::Load2DTextureFromFile("assets/models/House/grey.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	birdtexture = TextureUtils::Load2DTextureFromFile("assets/models/House/grey.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	grass[ALBEDO] = bigtreetexture;
	grass[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/grassspec.jpeg");
	grass[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/grass_rough.jpeg");
	grass[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/leavefin.jpg");
	grass[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });


	wolf[ALBEDO] = wolftexture;
	wolf[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/greyspec.png");
	wolf[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/greyrough.png");
	wolf[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/greyocc.png");
	wolf[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });

	birdd[ALBEDO] = birdtexture;
	birdd[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/greyspec.png");
	birdd[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/greyrough.png");
	birdd[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/greyocc.png");
	birdd[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });


	mvpLoc = glGetUniformLocation(shader->getID(), "MVP");
	texLoc = glGetUniformLocation(shader->getID(), "tex");
	tilingLoc = glGetUniformLocation(shader->getID(), "tiling");
	bottomLoc = glGetUniformLocation(shader->getID(), "bottom");
	topLoc = glGetUniformLocation(shader->getID(), "top");


    wood[ALBEDO] = List_1_dom_derevnja;
    wood[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/Wood_spc.jpg");
    wood[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/Wood_rgh.jpg");
    wood[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/wood.jpg");
    wood[EMISSIVE] = TextureUtils::SingleColor({0,0,0,1});

	wood2[ALBEDO] = List_4_dom_derevnja;
	wood2[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/Wood_spc.jpg");
	wood2[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/Wood_rgh.jpg");
	wood2[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/wood.jpg");
	wood2[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });

    asphalt[ALBEDO] = TextureUtils::Load2DTextureFromFile("assets/textures/Asphalt_rgh.jpg");
    asphalt[SPECULAR] = TextureUtils::Load2DTextureFromFile("assets/textures/Asphalt_spc.jpg");
    asphalt[ROUGHNESS] = TextureUtils::Load2DTextureFromFile("assets/textures/Asphalt_rgh.jpg");
    asphalt[AMBIENT_OCCLUSION] = TextureUtils::Load2DTextureFromFile("assets/textures/Asphalt_rgh.jpg");
    asphalt[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });

	checkers[ALBEDO] = bottomTex;
	checkers[SPECULAR] = TextureUtils::CheckerBoard({ 2048, 2048 }, { 128, 128 }, { 0.2f,0.2f,0.2f,1 }, { 0.2f,0.2f,0.2f,1 });
	checkers[ROUGHNESS] = TextureUtils::CheckerBoard({ 2048, 2048 }, { 128, 128 }, { 0.5f,0.9f,0.9f,1 }, { 0.5f,0.9f,0.9f,1 });
	checkers[AMBIENT_OCCLUSION] = TextureUtils::SingleColor({ 0.1,0.1,0.1,1 });
	checkers[EMISSIVE] = TextureUtils::SingleColor({ 0,0,0,1 });

    camera = new Camera();
    glm::ivec2 windowSize = getApplication()->getWindowSize();
    camera->setupPerspective(glm::pi<float>()/2, (float)windowSize.x / windowSize.y, 0.1f, 1000.0f);
    camera->setUp({0, 1, 0});

    controller = new FlyCameraController(this, camera);
    controller->setYaw(-glm::half_pi<float>());
    controller->setPitch(-glm::quarter_pi<float>());
    controller->setPosition({0, 2, 5});

    sunYaw = sunPitch = glm::quarter_pi<float>();

	modelFront = modelSide = 0.0;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.88f,0.68f,0.15f,0.0f);
}

void DirectionalLightScene::Update(double delta_time) {
    controller->update(delta_time);
    Keyboard* kb = getKeyboard();
	modelFront = glm::clamp(modelFront, -1.0f*glm::quarter_pi<float>() / 5, glm::quarter_pi<float>() / 5);
	modelSide = glm::clamp(modelSide, -1.0f*glm::quarter_pi<float>() / 3, glm::quarter_pi<float>() / 3);
	float pitch_speed = 1.0f, yaw_speed = 1.0f;
	float angleMoving;
	angleMoving = (float)delta_time *1.5f;//(sin(glfwGetTime() * 15.0f) * glm::quarter_pi<float>()) / 5;//
	fly = sin(glfwGetTime()*3.0f)*0.15f;

	fly2 = sin(glfwGetTime()*3.0f + 5.0f)*0.15f;

	moveing = sin(glfwGetTime())*2.0f;
    if(kb->isPressed(GLFW_KEY_I)) sunPitch += (float)delta_time * pitch_speed;
    if(kb->isPressed(GLFW_KEY_K)) sunPitch -= (float)delta_time * pitch_speed;
    if(kb->isPressed(GLFW_KEY_L)) sunYaw += (float)delta_time * yaw_speed;
    if(kb->isPressed(GLFW_KEY_J)) sunYaw -= (float)delta_time * yaw_speed;

	if (kb->isPressed(GLFW_KEY_W)) modelFront += angleMoving;
	if (kb->isPressed(GLFW_KEY_S)) modelFront -= angleMoving;
	if (kb->isPressed(GLFW_KEY_A)) modelSide += angleMoving;
	if (kb->isPressed(GLFW_KEY_D)) modelSide -= angleMoving;
	if (kb->justReleased(GLFW_KEY_W) || kb->justReleased(GLFW_KEY_S)) { modelFront = 0.0; }
	if (kb->justReleased(GLFW_KEY_A) || kb->justReleased(GLFW_KEY_D)) { modelSide = 0.0; }

	if (kb->isPressed(GLFW_KEY_T)) x+=.05; y+=.05; z+=.05; 
	if (kb->isPressed(GLFW_KEY_Y)) x-=.05; y-=.05; z-=.05;
    
    if(sunPitch < -glm::half_pi<float>()) sunPitch = -glm::half_pi<float>();
    if(sunPitch > glm::half_pi<float>()) sunPitch = glm::half_pi<float>();
    sunYaw = glm::wrapAngle(sunYaw);
}

inline glm::vec3 getTimeOfDayMix(float sunPitch){
    sunPitch /= glm::half_pi<float>();
    if(sunPitch > 0){
        float noon = glm::smoothstep(0.0f, 0.5f, sunPitch);
        return {noon, 1.0f - noon, 0};
    } else {
        float dusk = glm::smoothstep(0.0f, 0.25f, -sunPitch);
        return {0, 1.0f - dusk, dusk};
    }
}

void DirectionalLightScene::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear colors and depth

	glm::mat4 trans;
	trans = glm::scale(trans, glm::vec3(x, y, z));
	
	//rotate 
	glm::mat4 j3 = glm::rotate(glm::mat4(), dinasoreRotation, { 1,0,0 });
	// glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(j3));
    glm::mat4 janimatedrotate = glm::rotate(glm::mat4(), dinasoreRotation, { 0,fly,0 });


	glm::mat4 VP = camera->getVPMatrix();
    glm::vec3 cam_pos = camera->getPosition();
    glm::vec3 sun_direction = glm::vec3(glm::cos(sunYaw), 0, glm::sin(sunYaw)) * glm::cos(sunPitch) + glm::vec3(0, glm::sin(sunPitch), 0);

    const glm::vec3 noonSkyColor = {0.53f, 0.81f, 0.98f};
    const glm::vec3 sunsetSkyColor = {0.99f, 0.37f, 0.33f};
    const glm::vec3 duskSkyColor = {0.04f, 0.05f, 0.19f};

    const glm::vec3 noonSunColor = {0.9f, 0.8f, 0.6f};
    const glm::vec3 sunsetSunColor = {0.8f, 0.6f, 0.4f};
    const glm::vec3 duskSunColor = {0.0f, 0.0f, 0.0f};
    
    glm::vec3 mix = getTimeOfDayMix(sunPitch);

    glm::vec3 skyColor = mix.x * noonSkyColor + mix.y * sunsetSkyColor + mix.z * duskSkyColor;
    glm::vec3 sunColor = mix.x * noonSunColor + mix.y * sunsetSunColor + mix.z * duskSunColor;

    shader->use();

	unsigned int transformLoc = glGetUniformLocation(shader->getID(), "ChangeColor");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    shader->set("VP", VP);
    shader->set("cam_pos", cam_pos);
    shader->set("light.color", sunColor);
    shader->set("light.direction", -sun_direction);
    shader->set("ambient", 0.5f*skyColor);

    shader->set("material.albedo", 0);
    shader->set("material.specular", 1);
    shader->set("material.roughness", 2);
    shader->set("material.ambient_occlusion", 3);
    shader->set("material.emissive", 4);

    shader->set("material.albedo_tint", {1,1,1});
    shader->set("material.specular_tint", {1,1,1});
    shader->set("material.roughness_scale", 1.0f);
    shader->set("material.emissive_tint", {1,1,1});
	

	glm::mat4 ground_mat = glm::scale(glm::mat4(), glm::vec3(50, 1, 50));
    shader->set("M", ground_mat);
    shader->set("M_it", glm::transpose(glm::inverse(ground_mat)));
    for(int i = 0; i < 5; i++){
        glActiveTexture(GL_TEXTURE0+i);
        checkers[i]->bind();
    }
	ground->draw();



	glActiveTexture(GL_TEXTURE1);
	bottomTex->bind();
	glUniform1i(bottomLoc, 1);

	glActiveTexture(GL_TEXTURE2);
	topTex->bind();
	glUniform1i(topLoc, 2);

	glUniform2f(tilingLoc, 20, 20);
	ground->draw();



	
	
	



	glm::mat4 model2_mat = glm::translate(glm::mat4(), { 0, 0, 0 })* glm::scale(glm::mat4(), glm::vec3(1.5f, 1.5f, 1.5f));
	shader->set("M", model2_mat);

	shader->set("M_it", glm::transpose(glm::inverse(model2_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wood[i]->bind();
	}
	model->draw();



	glm::mat4 model_mat = glm::translate(glm::mat4(), camera->getPosition()) * glm::translate(glm::mat4(), { 0, -1 * fly , 0 }) * glm::rotate(glm::mat4(), modelFront, camera->Left()) * glm::rotate(glm::mat4(), modelSide, camera->Back()) *glm::rotate(glm::mat4(), -controller->getYaw(), camera->Up())*glm::rotate(glm::mat4(), -controller->getPitch(), camera->Left())*glm::translate(glm::mat4(), { 1,1.5,0 })  *glm::scale(glm::mat4(), glm::vec3(0.3, 0.3, 0.3));
	shader->set("M", model_mat);
	shader->set("M_it", glm::transpose(glm::inverse(model_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		asphalt[i]->bind();
	}
	ghost->draw();

	glm::mat4 table_mat = glm::translate(glm::mat4(), { -1, 1, 0 })* glm::translate(glm::mat4(), { 0, fly , 0 }) * glm::scale(glm::mat4(), glm::vec3(0.035f, 0.03f, 0.035f));
	shader->set("M", table_mat);

	shader->set("M_it", glm::transpose(glm::inverse(table_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wood2[i]->bind();
	}
	table->draw();

	glm::mat4 chair_mat = glm::translate(glm::mat4(), { -0.2, 0.25, 0 })* glm::translate(glm::mat4(), { 0, 0, moveing })* glm::translate(glm::mat4(), { 0, fly2 , 0 }) *glm::scale(glm::mat4(), glm::vec3(0.6f, 0.6f, 0.6f));
	shader->set("M", chair_mat);

	shader->set("M_it", glm::transpose(glm::inverse(chair_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wood2[i]->bind();
	}
	chair->draw();

	glm::mat4 model3_mat = glm::translate(glm::mat4(), { -20, 0, 0 });
	shader->set("M", model3_mat);

	shader->set("M_it", glm::transpose(glm::inverse(model3_mat)));

	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		grass[i]->bind();
	}
	Bigtree->draw();

	glm::mat4 model4_mat = glm::translate(glm::mat4(), { 20, 0, 0 });
	shader->set("M", model4_mat);

	shader->set("M_it", glm::transpose(glm::inverse(model4_mat)));

	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		grass[i]->bind();
	}
	Bigtree->draw();



	glm::mat4 modell_mat = glm::translate(glm::mat4(), { 10, 0, 20 });
	shader->set("M", modell_mat);
	shader->set("M_it", glm::transpose(glm::inverse(modell_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wolf[i]->bind();
	}
	wolfff->draw();

	glm::mat4 modell1_mat = glm::translate(glm::mat4(), { -20, 6, 20 })*j3* glm::translate(glm::mat4(), { 0, 0 , -4 * fly });
	shader->set("M", modell1_mat);
	shader->set("M_it", glm::transpose(glm::inverse(modell1_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		birdd[i]->bind();
	}
	bird1->draw();


	glm::mat4 modell2_mat = glm::translate(glm::mat4(), { -10, 0, 20 });
	shader->set("M", modell2_mat);
	shader->set("M_it", glm::transpose(glm::inverse(modell2_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wolf[i]->bind();
	}
	wolfff->draw();


	glm::mat4 modelll_mat = glm::translate(glm::mat4(), { -10, 0, 30 });
	shader->set("M", modelll_mat);
	shader->set("M_it", glm::transpose(glm::inverse(modelll_mat)));
	for (int i = 0; i < 5; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		wolf[i]->bind();
	}
	wolfff->draw();

    //Draw SkyBox
    skyShader->use();

	unsigned int transformLoc2 = glGetUniformLocation(skyShader->getID(), "ChangeColor");
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans));

    skyShader->set("VP", VP);
    skyShader->set("cam_pos", cam_pos);
    skyShader->set("M", glm::translate(glm::mat4(), cam_pos));
    skyShader->set("sun_direction", sun_direction);
    skyShader->set("sun_size", 0.02f);
    skyShader->set("sun_halo_size", 0.02f);
    skyShader->set("sun_brightness", 1.0f);
    skyShader->set("sun_color", sunColor);
    skyShader->set("sky_top_color", skyColor);
    skyShader->set("sky_bottom_color", 1.0f-0.25f*(1.0f-skyColor));
    skyShader->set("sky_smoothness", 0.5f);
    glCullFace(GL_FRONT);
    sky->draw();
    glCullFace(GL_BACK);
	

}

void DirectionalLightScene::Finalize() {
    delete controller;
    delete camera;
    delete model;
    delete sky;
    delete ground;
    for(int i = 0; i < 5; i++){
        delete metal[i];
        delete wood[i];
		delete wood2[i];
        delete asphalt[i];
        delete checkers[i];
		delete grass[i];
		delete birdd[i];
		delete wolf[i];
    }
    delete skyShader;
    delete shader;
}