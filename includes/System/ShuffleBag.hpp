#ifndef SHUFFLEBAG_HPP_INCLUDED
#define SHUFFLEBAG_HPP_INCLUDED

#include <vector>
#include <sstream>

#include "Hge.hpp"
#include "Misc.hpp"

template<typename T>
class ShuffleBag {
public:
	ShuffleBag() { }
	~ShuffleBag() { }
	
	ShuffleBag &Add( T val )
	{
		bag.push_back( val );
		return *this;
	}
	T Get()
	{
		if( Empty() ) {
			throw( std::out_of_range( "Shufflebag is empty" ) );
		}
		
		if( bag.empty() ) {
			bag.swap( rest );
		}
		
		typename List::iterator it = Misc::Random( bag.begin(), bag.end() );
		
		T temp = *it;
		
		rest.push_back( *it );
		bag.erase( it );
		
		std::stringstream ss;
		ss << temp;
		
		return temp;
	}
	void Clear()
	{
		bag.clear();
		rest.clear();
	}
	
	bool Empty()
	{
		return bag.empty() && rest.empty();
	}
	
	typedef std::vector<T> List;
	
	List GetBag() {
		return bag;
	}
	List GetRest() {
		return rest;
	}
private:
	List bag;
	List rest;
	
	HgeObj hge;
};

#endif
