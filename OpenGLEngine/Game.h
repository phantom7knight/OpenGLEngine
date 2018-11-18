#pragma once



#define Screen_Width  1366
#define Screen_Height  768 



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

