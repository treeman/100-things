#ifndef SHAKEABLE_HPP_INCLUDED
#define SHAKEABLE_HPP_INCLUDED

class Shakeable {
public:
	Shakeable();
	Shakeable( float x_mod, float y_mod );
	
	virtual ~Shakeable() { }
	
	virtual void SetShakeOffset( float x, float y );
protected:
	float shake_x_offset, shake_y_offset;
	float x_mod, y_mod;
};

#endif
