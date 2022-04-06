#include "state.h"
#include <system/platform.h>
#include <graphics/font.h>

//Load Scene Assets From Filename
gef::Scene* State::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

//Get Mesh From Scene Assets
gef::Mesh* State::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}

//Load Asset
gef::Mesh* State::LoadAsset(const char* asset_filename)
{
	for (int i = 0; i < 3; i++)
	{
		gef::Scene* scene_assets_ = LoadSceneAssets(*platform_, asset_filename);
		if (scene_assets_)
		{
			return GetMeshFromSceneAssets(scene_assets_);
		}
	}
}

//Init Font
void State::InitFont()
{
	font_ = new gef::Font(*platform_);
	font_->Load("font/bubble");
}
//Clean Up font
void State::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}
//Clean UP
void State::CleanUp()
{
	delete platform_;
	platform_ = NULL;
	delete primitive_builder_;
	primitive_builder_ = NULL;
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
	delete input_manager_;
	input_manager_ = NULL;
	delete renderer_3d_ ;
	renderer_3d_ = NULL;
	delete audio_manager_;
	audio_manager_ = NULL;
	delete state_machine_;
	state_machine_ = NULL;

	CleanUpFont();
}