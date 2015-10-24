// Include header file here.
#include "game.h"

// This will initialise the game window.
Game::Game(const float game_screen_width, const float game_screen_height) :
	window_(nullptr),
	current_state_(nullptr)
{

	// Setting the screen width and height.
	screen_resolution_.x = game_screen_width;
	screen_resolution_.y = game_screen_height;

	// Setting up the game window with variable screen resolution.
	window_ = new sf::RenderWindow(sf::VideoMode((unsigned int)screen_resolution_.x, (unsigned int)screen_resolution_.y), "It works!");

	// Handling the font loading.
	if (!font_.loadFromFile("Resources/Fonts/heavy_data.ttf"))
	{
		// Error.
		std::cout << "Font file not found." << std::endl;
	}

	// Setting up the state machine here.
	current_state_ = new InitState(*window_, font_, screen_resolution_);
	current_state_->OnEnter();

}

// This will clean up any pointers.
Game::~Game()
{

	// Cleaning up pointer variables.
	// If the current state exists.
	if (current_state_)
	{
		// Clean up the state machine.
		current_state_->Cleanup();

		// Delete the state pointer and set it to null.
		delete current_state_;
		current_state_ = nullptr;
	}
	
}

// This will handle the changing of game states.
void Game::HandleStates()
{

	// Creates a new state if a new one is required.
	State* new_state_ = current_state_->HandleInput();

	// If the new state is equal to something.
	if (new_state_ != nullptr)
	{
		// Exit the previous state.
		current_state_->OnExit();
		delete current_state_;

		// Enter the new state.
		current_state_ = new_state_;
		current_state_->OnEnter();
	}

}

// This will update the game every frame.
void Game::Update()
{

	// Setting up delta time.
	dt_ = clock_.restart();

	while (window_->pollEvent(event_))
	{
		// If the user wants to close the window.
		if (event_.type == sf::Event::Closed)
		{
			// Close the window.
			window_->close();
		}
	}

	// Handling any new state changes and input.
	HandleStates();

	// Update everything else here.
	// Updating the current state.
	current_state_->Update(dt_.asSeconds());

}

// This will render everything in the game window.
void Game::Render()
{

	// Clear the current game window.
	window_->clear();

	// Renders the window for the current state.
	current_state_->Render();

	// Display the new layout of the window.
	window_->display();

}


