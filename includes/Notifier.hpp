#ifndef NOTIFIER_HPP_INCLUDED
#define NOTIFIER_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "System/Hge.hpp"

struct Message {
	Message( std::string s );
	
	std::string str;
	float time_alive;
	int alpha;
	bool can_kill;
};

class Notifier {
public:
	Notifier();
	
	void Add( std::string str );
	
	void Update( float dt );
	void Render();
private:
	typedef std::vector<Message> Messages;
	Messages messages;
	boost::shared_ptr<hgeFont> fnt;
	
	const float fade_time;
	const float pause_before_fade;
};

#endif
