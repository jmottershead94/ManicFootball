#ifndef _NETWORK_HANDLER_H_
#define _NETWORK_HANDLER_H_

#include "utilities.h"
#include "connection.h"

class NetworkHandler : public Utilities
{

	public:
		// Methods.
		NetworkHandler();
		~NetworkHandler();
		bool ReceivedMessage();

	private:
		// Attributes.
		Connection connection_;

};

#endif