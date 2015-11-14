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

	// Setting up the game window with variable screen resolution.
	window_ = new sf::RenderWindow(sf::VideoMode((unsigned int)screen_resolution_.x, (unsigned int)screen_resolution_.y), "Manic Football");
	
	// This will lock the frame rate of the game window to 60 fps.
	window_->setFramerateLimit(frame_rate_);

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
	world_->SetContinuousPhysics(true);

	// Binding the listener to the port 5000.
	// Listen out for any connections on port 5000.
	if (connection_listener_.listen(port_) != sf::Socket::Done)
	{
		// Error for listening on the port number 5000.
		std::cout << "Connection Listener Error" << std::endl;
	}

	std::cout << "Server is listening to port " << port_ << ", waiting for connections..." << std::endl;

	// Checking to see if the first client has connected to the server.
	// If the client has not connected to the server.
	if (connection_listener_.accept(player_one_socket_) != sf::Socket::Done)
	{
		// Error.
		// The first player has not made a connection to the server.
		std::cout << "Client could not connect..." << std::endl;
		return;
	}
	// Otherwise, the client has connected to the server.
	else
	{
		std::cout << "Client connected: " << player_one_socket_.getRemoteAddress() << std::endl;

		// Send a starter message struct to player one.
		// Telling them what team they are on. (bool red_team = true).
		// Sending them the initial server timestamp for timing offsets on the client side.


		// Initialise the server level.
		//level_.Init(world_, font_, screen_resolution_);
	}

	// Checking to see if the second player has connected to the server.
	if (connection_listener_.accept(player_two_socket_) != sf::Socket::Done)
	{
		// Error.
		// The second player has not made a connection to the server.
		std::cout << "Client could not connect..." << std::endl;
	}
	else
	{
		std::cout << "Client connected: " << player_one_socket_.getRemoteAddress() << std::endl;		

		// Send a starter message struct to player one.
		// Telling them what team they are on. (bool red_team = true).
		// Sending them the initial server timestamp for timing offsets on the client side.
		std::cout << "Players are now going to the level." << std::endl;

		// Initialise the server level.
		level_.Init(world_, font_, screen_resolution_);
	}

	//// If both player one and two have connected to the server successfully.
	//if ((connection_listener_.accept(player_one_socket_) == sf::Socket::Done))
	//{
	//	std::cout << "Player one is going to the level." << std::endl;

	//	// Initialise the server level.
	//	level_.Init(world_, font_, screen_resolution_);
	//}
	//// Otherwise, one of the players did not connect to the server.
	//else
	//{
	//	// Error message.
	//	std::cout << "Client could not connect..." << std::endl;
	//}

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

// This will check the current state of the match.
// When someone has won the match.
void Game::CheckIfLevelHasFinished()
{

	// If the current match has finished.
	if (level_.HasFinished())
	{
		// Clear the level.
		level_.Clear();

		// Terminate all of the connections here...
		

		// Close the server connection.
		//this->~Game();
	}

}

// This will update the game every frame.
void Game::Update()
{

	// Set up Box2D variables.
	float time_step = 1.0f / (float)frame_rate_;
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
	level_.Render(*window_);

	// Display the new layout of the window.
	window_->display();

}