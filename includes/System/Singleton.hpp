#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

template<class T>
class Singleton {
public:
	static T &Get()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() { }
	virtual ~Singleton() { }
private:
	Singleton( const Singleton &s );
	Singleton &operator = ( const Singleton &s );
};

#endif
