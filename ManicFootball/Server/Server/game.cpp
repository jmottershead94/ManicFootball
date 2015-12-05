// Include header file here.
#include "game.h"

// This will initialise the game window.
Game::Game(const float game_screen_width, const float game_screen_height) :
	world_(nullptr),
	window_(nullptr)
{

	// Setting the screen width and height.
	screen_resolution_.x = game_screen_width;
	screen_resolution_.y = game_screen_height;

	// Handling the font loading.
	if (!font_.loadFromFile("Resources/Fonts/heavy_data.ttf"))
	{
		// Error.
		std::cout << "Font file not found." << std::endl;
	}

	// Defining the gravity vector.
	b2Vec2 gravity(0.0f, -9.8f);

	// Creating the Box2D physics world.
	world_ = new b2World(gravity);
	
	// Accept connections from clients.
	StartAcceptingConnections();
}

// This will clean up any pointers.
Game::~Game()
{
	
	if (world_)
	{
		delete world_;
		world_ = nullptr;
	}

}

void Game::StartAcceptingConnections()
{

	/*player_one_socket_.setBlocking(false);
	player_two_socket_.setBlocking(false);*/

	// Accept connections from two clients.
	network_.AcceptConnection(player_one_socket_, true, clock_);
	network_.AcceptConnection(player_two_socket_, false, clock_);

	// If the network is sending ready messages (i.e. the clients have successfully connected).
	if (network_.IsReady())
	{
		// Check to see if the clients are ready to play a match.
		if (network_.ConnectionsAreReady())
		{
			// Setting up the game window with variable screen resolution.
			window_ = new sf::RenderWindow(sf::VideoMode((unsigned int)screen_resolution_.x, (unsigned int)screen_resolution_.y), "Manic Football");

			// This will lock the frame rate of the game window to 60 fps.
			window_->setFramerateLimit(kFrameRate);

			// Initialise the server level.
			level_.Init(world_, font_, screen_resolution_, network_, clock_);
		}
	}

}

// This will check the current state of the match.
// When someone has won the match.
void Game::CheckIfLevelHasFinished()
{

	// If the current match has finished, or any of the clients have disconnected from the server.
	if (level_.GetLevelGenerator().HasFinished())
		//|| level_.GetNetwork().DisconnectingClients(*level_.GetNetwork().GetClientSockets()[0])
		//|| level_.GetNetwork().DisconnectingClients(*level_.GetNetwork().GetClientSockets()[1]))
	{
		// Resetting the objects.
		level_.GetLevelGenerator().Reset();

		// Clear the level.
		level_.GetLevelGenerator().Clear();

		// Disconnect both clients.
		network_.GetClientSockets()[0]->disconnect();
		network_.GetClientSockets()[1]->disconnect();

		// Terminate all of the connections here...
		window_->close();

		// Look out for anymore connections.
		StartAcceptingConnections();
	}

}

// This will update the game every frame.
void Game::Update()
{

	// Set up Box2D variables.
	float time_step = 1.0f / (float)kFrameRate;
	int32 velocity_iterations = 8;
	int32 position_iterations = 6;

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
	
	// This will keep checking the current match state.
	CheckIfLevelHasFinished();

	// Keep updating the physics world.
	// Updates the physics simulation based on iterations.
	world_->Step(time_step, velocity_iterations, position_iterations);

	// Update the level.
	level_.Update(dt_.asSeconds());

}

// This will render everything in the game window.
void Game::Render()
{

	// Clear the current game window.
	window_->clear();

	// Render everything in the level.
	level_.GetLevelGenerator().Render(*window_);

	// Display the new layout of the window.
	window_->display();

}