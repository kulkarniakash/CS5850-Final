#include <ControllerComponent.hpp>
#include "GlobalAttributes.hpp"
#include <iostream>


ControllerComponent::ControllerComponent() {
	m_gameobject = NULL;
}

ControllerComponent::~ControllerComponent() {
	//delete m_gameobject;
	std::cout << "ControllerComponent destructor called" << std::endl;
	m_gameobject = NULL;
	no_key_pressed = true;
}

void ControllerComponent::handleInput() {
    
}

void ControllerComponent::addInputBinding(std::string key, py::object callback, bool isPersistent) {
	if (keymap.find(key) != keymap.end()) {
		keyToFuncMap.insert(std::make_pair(key, callback));
		keyToPersist.insert(std::make_pair(key, isPersistent));
		keypressed.insert(std::make_pair(key, false));
		prevKeyPressed.insert(std::make_pair(key, false));
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

void ControllerComponent::addPlayerObject(PlayerObject* obj) {
	m_gameobject = obj;
}

void ControllerComponent::setKeyTo(int key, bool value) {

	if (keymapinv.find(key) != keymapinv.end()) {
		auto it = keypressed.find(keymapinv.at(key));
		if (it != keypressed.end()) {
			if (it->second != value) {
				if (value) {
					executeNonPersistCallback(key);
				}
				else {
					executeNonPersistUnCallback(key);
				}
			}

			it->second = value;
		}
	}
}

void ControllerComponent::executeNonPersistCallback(int key) {
	for (auto itr : keyToFuncMap) {
		if (!keyToPersist.at(itr.first) && keymapinv.at(key) == itr.first) {
			itr.second(m_gameobject);
		}
	}
}

void ControllerComponent::executeNonPersistUnCallback(int key) {
	for (auto itr : unkeyToFuncMap) {
		if (!unkeyToPersist.at(itr.first) && keymapinv.at(key) == itr.first) {
			itr.second(m_gameobject);
		}
	}
}

void ControllerComponent::executeCallback() {
	/*if (keyToFuncMap.find(key) != keyToFuncMap.end()) {
		keyToFuncMap.at(key)(m_gameobject);
	}*/
	for (auto itr : keyToFuncMap) {
		if (keypressed.at(itr.first) && keyToPersist.at(itr.first)) {
			itr.second(m_gameobject);
		}
	}
}

int ControllerComponent::getKeysNum() {
	return keyToFuncMap.size();
}

void ControllerComponent::addInputReleaseBinding(std::string key, py::object callback, bool isPersistent) {
	if (keymap.find(key) != keymap.end()) {
		unkeyToFuncMap.insert(std::make_pair(key, callback));
		unkeyToPersist.insert(std::make_pair(key, isPersistent));
		if (keypressed.find(key) == keypressed.end()) {
			keypressed.insert(std::make_pair(key, false));
			prevKeyPressed.insert(std::make_pair(key, false));
		}
	}
	else {
		std::cout << "Error: key does not exist\n";
	}
}

int ControllerComponent::getUnKeysNum() {
	return unkeyToFuncMap.size();
}

void ControllerComponent::executeUnCallback() {
	for (auto itr : unkeyToFuncMap) {
		if (!keypressed.at(itr.first) && unkeyToPersist.at(itr.first)) {
			itr.second(m_gameobject);
		}
	}
}

bool ControllerComponent::noKeyPressed() {
	auto it = keypressed.begin();
	while (it != keypressed.end()) {
		if (it->second == true) {
			return false;
		}
		it++;
	}
	return true;
}