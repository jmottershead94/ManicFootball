// Jason Mottershead, 1300455.

// State class header file.
// This is the base state class, every other state class will inherit from this.
// This will set the template up for the rest of the states.

// Header guard.
#ifndef _STATE_H_
#define _STATE_H_

// Include files here.
#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "network.h"

// The base state class, will be used by all other states.
class State
{

	public:
		// Methods.
		virtual ~State() {};

		// Pure virtual functions that every state MUST have.
		// Intended to be overwritten by the more specific states.
		
		// Handling input for reading input through states.
		virtual State* HandleInput() = 0;

		// Providing each state with its' own entering sequence.
		virtual void OnEnter() = 0;

		// Providing each state with its' own exiting sequence.
		virtual void OnExit() = 0;

		// Render for rendering any specific text/objects for that state.
		virtual void Render() = 0;

		// Not pure virtual functions because when a state cleans up, it should go back here.
		// All of the pointers will be erased.
		virtual void Cleanup();
		virtual void Update(float dt);

	protected:
		// Attributes.
		b2World* world_;					// Points to the Box2D world.
		sf::Font* font_;					// Points to the font.
		sf::RenderWindow* window_;			// Points to the render window.
		sf::Text* text_;					// Some generic state text, could be a title.
		sf::Text* text_controls_;			// Some generic controls text, telling us how to navigate in the state.
		sf::Vector2f* screen_resolution_;	// Points to the screen resolution.
		Network* network_;					// Points to the network we are using.

};

#endif