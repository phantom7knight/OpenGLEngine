#pragma once



#define Screen_Width  1000
#define Screen_Height  800 



class Game
{
public:
	Game();
	~Game();


	bool Init();
	void Update();
	void Destroy();

	inline bool getGameState()
	{
		return m_isgameRunning;
	}

	inline void setGameState(bool value)
	{
		m_isgameRunning = value;
	}

	static Game* getInstance();

private:
	bool m_isgameRunning = false;
	static Game * m_Instance;

};

