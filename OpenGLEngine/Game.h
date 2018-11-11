#pragma once



#define Screen_Width  1000
#define Screen_Height  800 



class Game
{
public:
	Game();
	~Game();


	bool Init();
	void Run();
	void Update();
	void Destroy();

	
	static Game* getInstance();

private:
	
	static Game * m_Instance;

};

