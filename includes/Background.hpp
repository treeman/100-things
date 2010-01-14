#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

class Background {
public:
	virtual ~Background() { }
	
	virtual void Update( float ) { }
	virtual void Render() = 0;
};

class ABackground : public Background {
public:
	ABackground();
	
	void Update( float dt );
	void Render();
};

#endif
