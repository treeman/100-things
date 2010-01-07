#ifndef ERRORHANDLING_HPP_INCLUDED
#define ERRORHANDLING_HPP_INCLUDED

#include <exception>
#include <stdexcept>

namespace Error 
{
	class file_not_found : public std::exception {
	public:
		file_not_found( const char *err ) {
			s = err;
		}
		virtual const char *what() const throw() {
			return s;
		}
	private:
		const char *s;
	};
	
	class setting_not_found : public std::exception {
	public:
		setting_not_found( const char *err ) {
			s = err;
		}
		virtual const char *what() const throw() {
			return s;
		}
	private:
		const char *s;
	};
	
	class lua_error : public std::exception {
	public:
		lua_error( const char *err ) {
			s = err;
		}
		virtual const char *what() const throw() {
			return s;
		}
	private:
		const char *s;
	};
}

#endif
