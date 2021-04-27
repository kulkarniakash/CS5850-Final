// Include the pybindings
#include <pybind11/pybind11.h>
#include "Engine.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "ControllerComponent.hpp"
#include "SpriteComponent.hpp"
#include "CharacterSpriteComponent.hpp"
#include "Vec2.hpp"
#include "SDL_Headers.hpp"
#include "ResourceManager.hpp"
#include "AnimateObject.hpp"
#include "PlayerObject.hpp"
#include "Camera.hpp"
//#include "UIComponent.hpp"

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(Engine, m) {
	m.doc() = "our game engine as a library"; // Optional docstring

	py::class_<Engine>(m, "Engine")
		.def(py::init<>(), py::return_value_policy::take_ownership)   // our constructor
		.def("input", &Engine::Input) // Expose member methods
		.def("render", &Engine::Render)
		.def("main_game_loop", &Engine::MainGameLoop)
		.def("start", &Engine::Start)
		.def("shutdown", &Engine::Shutdown)
		.def("initialize_graphics_subsystem", &Engine::InitializeGraphicsSubSystem)
		.def("program_ended", &Engine::programEnded)
		.def("clear", &Engine::clear)
		.def("delay", &Engine::delay)
		.def("add_game_object", &Engine::addGameObject)
		.def("add_animate_object", &Engine::addAnimateObject)
		.def("add_player_object", &Engine::addPlayerObject)
		.def("add_ui_component", &Engine::addUIComponent)
		.def("update", &Engine::update)
		.def("add_UF_callback", &Engine::addUFCallback)
		.def("add_tilemanager", &Engine::addTileManager)
		.def("destroy_object", &Engine::destroyObject)
		.def("get_time", &Engine::getTime)
		.def("set_timer", &Engine::setTimer)
		.def("stop_timer", &Engine::stopTimer)
		.def("reset_timer", &Engine::resetTimer)
		.def("reset", &Engine::reset);

	py::class_<TileManager>(m, "TileManager")
		.def(py::init<int, int, Vec2>(), py::return_value_policy::reference)
		.def("load_tile_types", &TileManager::loadTileTypes)
		.def("load_level_map", &TileManager::loadLevelMap)
		.def("get_tile_count", &TileManager::getTileCount);

	py::class_<SDL_Rect>(m, "Rect")
		.def(py::init<>())
		.def_readwrite("x", &SDL_Rect::x)
		.def_readwrite("y", &SDL_Rect::y)
		.def_readwrite("w", &SDL_Rect::w)
		.def_readwrite("h", &SDL_Rect::h);

	py::class_<GameObject>(m, "GameObject")
		.def(py::init<std::string, float, float>(), py::return_value_policy::reference)// our constructor
        .def("get_sound_component", &GameObject::getSoundComponent)
        .def("add_sound_component", &GameObject::addSoundComponent)
		.def("get_transform_component", &GameObject::getTransformComponent, py::return_value_policy::reference) // Expose member methods
		.def("add_transform_component", &GameObject::addTransformComponent)
		.def("add_sprite_component", &GameObject::addSpriteComponent)
		.def("add_character_sprite_component", &GameObject::addCharacterSpriteComponent)
		.def("get_sprite_component", &GameObject::getSpriteComponent, py::return_value_policy::reference)
		.def("add_character_sprite_component", &GameObject::addCharacterSpriteComponent)
		.def("get_sprite_component", &GameObject::getSpriteComponent, py::return_value_policy::reference)
		.def("get_character_sprite_component", &GameObject::getCharacterSpriteComponent, py::return_value_policy::reference)
		.def("get_width", &GameObject::getWidth)
		.def("get_height", &GameObject::getHeight)
		.def("render", &GameObject::render);

	py::class_<AnimateObject, GameObject>(m, "AnimateObject")
		.def(py::init<std::string, float, float>(), py::return_value_policy::reference)
		.def("update_sprite", &AnimateObject::updateSprite)
		.def("update_transform", &AnimateObject::updateTransform)
		.def("update_position", &AnimateObject::updatePosition)
		.def("update_velocity", &AnimateObject::updateVelocity)
		.def("set_position", &AnimateObject::setPosition)
		.def("set_velocity", &AnimateObject::setVelocity)
		.def("add_collision_callback", &AnimateObject::addCollisionCallback);

	py::class_<PlayerObject, AnimateObject>(m, "PlayerObject")
		.def(py::init<std::string, float, float>(), py::return_value_policy::reference)
		.def("add_controller_component", &PlayerObject::addControllerComponent)
		.def("get_controller_component", &PlayerObject::getControllerComponent, py::return_value_policy::reference)
		.def("update_controller_velocity", &PlayerObject::updateControllerVelocity)
		.def("set_controller_velocity", &PlayerObject::setControllerVelocity)
		.def("get_controller_velocity", &PlayerObject::getControllerVelocity)
		.def("add_collision_callback", &PlayerObject::addCollisionCallback);

	py::class_<TransformComponent>(m, "TransformComponent")
		.def(py::init<const Vec2&, const Vec2&>())   // our constructor
		.def("set_position", &TransformComponent::setPosition) // Expose member methods
		.def("set_velocity", &TransformComponent::setVelocity)
		.def("get_position", &TransformComponent::getPosition)
		.def("get_velocity", &TransformComponent::getVelocity)
		.def("update", &TransformComponent::update);

	py::class_<SpriteComponent>(m, "SpriteComponent")
		.def(py::init<std::string, SDL_Rect>(), py::return_value_policy::reference)
		.def("render", &SpriteComponent::render)
		.def("update_postion", &SpriteComponent::updatePosition)
		.def("get_width", &SpriteComponent::getWidth)
		.def("get_height", &SpriteComponent::getHeight);

	py::class_<CharacterSpriteComponent, SpriteComponent>(m, "CharacterSpriteComponent")
		.def(py::init<std::string, SDL_Rect, SDL_Rect, int, int>(), py::return_value_policy::reference)
		.def("loop_action", &CharacterSpriteComponent::loopAction, py::return_value_policy::reference)
		.def("add_animation", &CharacterSpriteComponent::addAnimation)
		.def("perform_animation", &CharacterSpriteComponent::performAnimation)
		.def("set_loop", &CharacterSpriteComponent::setLoop)
		.def("update_frame", &CharacterSpriteComponent::updateFrame);
    
    py::class_<SoundComponent>(m, "SoundComponent")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("add_background_music", &SoundComponent::addBackgroundMusic)
        .def("add_sound_effect", &SoundComponent::addSoundEffect)
        .def("play_sound_effect", &SoundComponent::playSoundEffect)
        .def("play_background_music", &SoundComponent::playBackgroundMusic);


	py::class_<ControllerComponent>(m, "ControllerComponent")
		.def(py::init<>(), py::return_value_policy::reference)   // our constructor
		.def("add_input_binding", &ControllerComponent::addInputBinding)
		.def("add_input_release_binding", &ControllerComponent::addInputReleaseBinding)
		.def("no_key_pressed", &ControllerComponent::noKeyPressed);
		
	py::class_<Vec2>(m, "Vec2")
		.def(py::init<float, float>())
		.def_readwrite("x", &Vec2::x)
		.def_readwrite("y", &Vec2::y)
		.def("__repr__",
			[](const Vec2& vec) {
				return "{x = " + std::to_string(vec.x) + ", y = " + std::to_string(vec.y) + "}";
			});

	py::class_<Camera>(m, "Camera")
		.def("bind_to_object", &Camera::bindToObject)
		.def("get_instance", &Camera::getInstance, py::return_value_policy::reference);

	py::class_<UIComponent>(m, "UIComponent")
		.def(py::init<std::string, SDL_Rect, std::string, int>(), py::return_value_policy::reference)
		.def("render", &UIComponent::render)
		.def("update", &UIComponent::update);
	// We do not need to expose everything to our users!
	//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference) 
}

