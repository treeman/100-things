#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

#include "Hge.hpp"
#include "Dator.hpp"

class WindowManager {
public:
	WindowManager();
	~WindowManager();
	
	void Setup();
	
	std::string SetWindowed( const bool &predicate );
	std::string SetScreenWidth( const int &val );
	std::string SetScreenHeight( const int &val );
	std::string SetScreenBPP( const int &val );
	std::string SetScreenTitle( const std::string &val );
private:
	int scr_width, scr_height, scr_bpp;
    bool scr_is_windowed;
	std::string title_name;

	HgeObj hge;
	
	bool is_setup;
	
	boost::shared_ptr<Dator<int> > screenWidth;
	boost::shared_ptr<Dator<int> > screenHeight;
	boost::shared_ptr<Dator<int> > screenBPP;
	boost::shared_ptr<Dator<bool> > screenIsWindowed;
	boost::shared_ptr<Dator<std::string> > titleName;
};

#endif
