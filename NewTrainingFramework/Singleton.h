#pragma once
class Singleton
{
private:
	Singleton();
	static Singleton* spInstance;
public:
	
	~Singleton();
	void Init();//initializari - pot fi si in constructor
	static Singleton* getInstance();
};

