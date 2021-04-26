#ifndef UNIVERSE
#define UNIVERSE
#include "AnimateObject.hpp"
#include "PlayerObject.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

/*!
 * @brief class that represents a UniversalForce
 * handles applying forces and function objects to objects
 */
class UniversalForce {
public:

    //! constructs our UniversalForce
	UniversalForce();

    /*!
     * @brief applies a force to our vector of AnimateObject
     * @param animateobjs: A vector of AnimateObject we want to apply force upon
     */
	void applyForces(std::vector<AnimateObject*>* animateobjs);
    
    /*!
     * @brief applies a force to our vector of PlayerObject
     * @param playerobjs: A vector of PlayerObject we want to apply force upon
     */
	void applyForces(std::vector<PlayerObject*>* playerobjs);

    /*!
     * @brief adds a function object to our vector of function objects
     * @param object: function object that we want to add in our vector
     */
	void addCallback(py::object);

private:
	std::vector<py::object> callbacks;
};

#endif // !UNIVERSE

