class Model {

public:
	GameObject* board;
	GameObject* player;
	std::vector<GameObject*> collectables;

	int collectables_size;
	int collected;
	bool isPause;

public:
	Model(int width, int height);
	~Model();
	void createGameObjects();
	std::vector<GameObject*>  getCollectables();
	GameObject* getBoard();
	GameObject* getPlayer();
	void setCollected(int collected);
	int getCollected();
	int getCollectablesSize();
	bool hasPlayerCollidedwithObstacles();
	void deleteFromCollectables(GameObject* go);

	void setPause(bool pauset);
	bool getPause();
};