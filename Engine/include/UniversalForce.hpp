#ifndef UNIVERSE
#define UNIVERSE
#include "AnimateObject.hpp"
#include "PlayerObject.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

class UniversalForce {
public:

	UniversalForce();

	void applyForces(std::vector<AnimateObject*>* animateobjs);
	void applyForces(std::vector<PlayerObject*>* playerobjs);

	void addCallback(py::object);

private:
	std::vector<py::object> callbacks;
};

#endif // !UNIVERSE

