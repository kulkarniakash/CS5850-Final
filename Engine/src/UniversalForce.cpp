#include "UniversalForce.hpp"

UniversalForce::UniversalForce() {

}

void UniversalForce::addCallback(py::object func) {
	callbacks.push_back(func);
}

void UniversalForce::applyForces(std::vector<AnimateObject*>* objs) {
	for (auto callback : callbacks) {
		for (auto obj : *objs) {
			callback(obj);
		}
	}
}

void UniversalForce::applyForces(std::vector<PlayerObject*>* objs) {
	for (auto callback : callbacks) {
		for (auto obj : *objs) {
			callback(obj);
		}
	}
}