// Include the pybindings
#include <pybind11/pybind11.h>
#include "Engine.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "ControllerComponent.hpp"
#include "SpriteComponent.hpp"
#include "Vec2.hpp"

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
		.def(py::init<>())   // our constructor
		.def("input", &Engine::Input) // Expose member methods
		.def("render", &Engine::Render)
		.def("main_game_loop", &Engine::MainGameLoop)
		.def("start", &Engine::Start)
		.def("shutdown", &Engine::Shutdown)
		.def("initialize_graphics_subsystem", &Engine::InitializeGraphicsSubSystem);

	py::class_<GameObject>(m, "GameObject")
		.def(py::init<std::string>())   // our constructor
		.def("get_transform_component", &GameObject::getTransformComponent, py::return_value_policy::take_ownership) // Expose member methods
		.def("add_transform_component", &GameObject::addTransformComponent)
		.def("add_controller_component", &GameObject::addControllerComponent)
		.def("add_sprite_component", &GameObject::addSpriteComponent)
		.def("get_controller_component", &GameObject::getControllerComponent, py::return_value_policy::take_ownership)
		.def("get_sprite_component", &GameObject::getSpriteComponent, py::return_value_policy::take_ownership)
		.def("update", &GameObject::update)
		.def("render", &GameObject::render);

	py::class_<TransformComponent>(m, "TransformComponent")
		.def(py::init<const Vec2&, const Vec2&>())   // our constructor
		.def("set_position", &TransformComponent::setPosition) // Expose member methods
		.def("set_velocity", &TransformComponent::setVelocity)
		.def("get_XPosition", &TransformComponent::getXPosition)
		.def("get_YPosition", &TransformComponent::getYPosition)
		.def("update", &TransformComponent::update);

	py::class_<SpriteComponent>(m, "SpriteComponent")
		.def(py::init<std::string, Vec2, float, float>())   // our constructor
		.def("perform_animation", &SpriteComponent::performAnimation) // Expose member methods
		.def("render", &SpriteComponent::render)
		.def("update", &SpriteComponent::update);


	py::class_<ControllerComponent>(m, "ControllerComponent")
		.def(py::init<>());   // our constructor
		

	py::class_<Vec2>(m, "Vec2")
		.def(py::init<float, float>())
		.def_readwrite("x", &Vec2::x)
		.def_readwrite("y", &Vec2::y)
		.def("__repr__",
			[](const Vec2& vec) {
				return "{x = " + std::to_string(vec.x) + ", y = " + std::to_string(vec.y) + "}";
			});
	// We do not need to expose everything to our users!
	//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference) 
}

