// Include header file here.
#include "game.h"

// This will initialise the game window.
Game::Game(const float game_screen_width, const float game_screen_height) :
	world_(nullptr),
	window_(nullptr),
	ready_(false)
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

	NetworkConnection();
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

void Game::NetworkConnection()
{
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
		StartMessage starting_message;
		starting_message.player_team = true;		// Setting player one to be on the red team.
		starting_message.game_clock.restart();	// Restarting the game clock for player one to determine lag offset.
					
		// Placing the starting message into the data packet for sending.
		data_ >> starting_message;

		// Sending the data back to the player one socket.
		if (player_one_socket_.send(data_) != sf::Socket::Done)
		{
			// ERROR: The data could not be sent!
			std::cout << "ERROR: Data could not be sent to player one." << std::endl;
		}
	}

	// Checking to see if the second player has connected to the server.
	if (connection_listener_.accept(player_two_socket_) != sf::Socket::Done)
	{
		// Error.
		// The second player has not made a connection to the server.
		std::cout << "Client could not connect..." << std::endl;
		return;
	}
	else
	{
		std::cout << "Client connected: " << player_two_socket_.getRemoteAddress() << std::endl;

		// Send a starter message struct to player two.
		// Telling them what team they are on. (bool red_team = true).
		// Sending them the initial server timestamp for timing offsets on the client side.
		StartMessage starting_message;
		starting_message.player_team = false;		// Setting player two to be on the blue team.
		starting_message.game_clock.restart();		// Restarting the game clock for player one to determine lag offset.

		// Placing the starting message into the data packet for sending.
		data_ << starting_message;

		// If the data could not be sent to player two.
		if (player_two_socket_.send(data_) != sf::Socket::Done)
		{
			// ERROR: The data could not be sent!
			std::cout << "ERROR: Data could not be sent to player two." << std::endl;
			return;
		}
		// Otherwise, the data has been sent.
		else
		{
			// Both players have connected and are ready to start the game.
			ready_ = true;

			// Place the ready flag into a packet of data.
			data_ << ready_;

			// Checking to see if both sockets have received the ready flag, continue with the game.
			if ((player_one_socket_.send(data_) != sf::Socket::Done) || (player_two_socket_.send(data_) != sf::Socket::Done))
			{
				// ERROR: The data could not be sent!
				std::cout << "ERROR: Data could not be sent to the players." << std::endl;
				return;
			}
			else if ((player_one_socket_.send(data_) == sf::Socket::Done) || (player_two_socket_.send(data_) == sf::Socket::Done))
			{
				// Initialise the server level.
				level_.Init(world_, font_, screen_resolution_);
			}
		}
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

// Overloading packet operator functions.
// Used for sending packet data.
sf::Packet& operator<<(sf::Packet& packet, const Game::StartMessage& message)
{
	return packet << message;
}

// Used for recieving packet data.
sf::Packet& operator>>(sf::Packet& packet, const Game::StartMessage& message)
{
	return packet >> message;
}