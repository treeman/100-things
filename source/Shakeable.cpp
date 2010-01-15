#include "includes/Shakeable.hpp"

Shakeable::Shakeable() : shake_x_offset( 0 ), shake_y_offset( 0 ), x_mod( 1 ), y_mod( 1 )
{ }

Shakeable::Shakeable( float _x_mod, float _y_mod ) : shake_x_offset( 0 ), shake_y_offset( 0 ), x_mod( _x_mod ), y_mod( _y_mod )
{ }
	
void Shakeable::SetShakeOffset( float x, float y ) {
	shake_x_offset = x * x_mod;
	shake_y_offset = y * y_mod;
}
