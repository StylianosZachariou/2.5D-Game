#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include "primitive_builder.h"
#include "state_machine.h"


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class InputManager;
	class AudioManager;
	class Renderer3D;
}

//Scene Application Class
class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	//Initialise
	void Init();
	//Clean Up
	void CleanUp();
	//Update
	bool Update(float frame_time);
	//Render
	void Render();

private:
	
	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_;
	gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;
	gef::AudioManager* audio_manager_;
	StateMachine state_machine_;

};
#endif // _SCENE_APP_H
