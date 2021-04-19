#include <ControllerComponent.hpp>
#include "GlobalAttributes.hpp"
#include <iostream>


ControllerComponent::ControllerComponent() {
    
}

ControllerComponent::~ControllerComponent() {
    
}

void ControllerComponent::handleInput() {
    
}

void ControllerComponent::addInputBinding(std::string key, py::object callback) {
	if (keymap.find(key) != keymap.end()) {
		keyToFuncMap.insert(std::make_pair(key, callback));
	}
	else {
		std::cout << "Error: key does not exist\n";
	}
	
}

std::string* ControllerComponent::getKeys() {
	int size = keyToFuncMap.size();
	std::string* keys = new std::string[size];

	int count = 0;
	for (auto itr : keyToFuncMap) {
		keys[count] = itr.first;
		count++;
	}

	return keys;
}

void ControllerComponent::executeCallback(std::string key) {
	if (keyToFuncMap.find(key) != keyToFuncMap.end()) {
		keyToFuncMap.at(key)();
	}
}

int ControllerComponent::getKeysNum() {
	return keyToFuncMap.size();
}