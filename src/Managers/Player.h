#ifndef MANAGERS_PLAYER_H_
#define MANAGERS_PLAYER_H_

#include <rapidjson/fwd.h>

class Player
{
  private:
	int frameCounter = 0;

	// resource used to summon
	int fujika = 0;
	int fujikaGain = 2;
	int fujikaLimit = 20;

	// resource used to buy equipement
	int fuko = 0;
	int fukoGain = 1;
	int fukoLimit = 1000;

  public:
	Player (){};
	~Player (){};

	bool Summon (int cost);
	bool Buy (int cost);

	int GetFujika ();
	int GetFujikaLimit ();
	int GetFuko ();
	int GetFukoLimit ();

	void ReturnFuko (int value);

	void Update ();
	void Reset ();
	void HardReset ();
	void Save (rapidjson::Document *saveJson);
	void Load (rapidjson::Value *saveJson);
};

#endif // MANAGERS_PLAYER_H_