#ifndef LEVELLOADER_HPP_INCLUDED
#define LEVELLOADER_HPP_INCLUDED

#include "Level.hpp"

class LevelLoader {
public:
	LevelLoader( World *const world );
	
	void LoadLevels( std::string path );
	
	boost::shared_ptr<Level> GetNextLevel();
	boost::shared_ptr<Level> GetLevel( int num );
	void ResetCounter() {
		curr = 0;
	}
	size_t GetNumLevels() const {
		return levels.size();
	}
	
	bool NoLevels();
	
	void SetStatsMod( float mod );
private:
	typedef std::vector<boost::shared_ptr<Level> > Levels;
	Levels levels;
	size_t curr;
	
	World *const world;
};

#endif
