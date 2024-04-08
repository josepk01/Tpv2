#pragma once

#include "../ecs/Entity.h"
#include "../sdlutils/VirtualTimer.h"

class RandomNumberGenerator;
class Image;

class FruitComponent : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::FRUITCOMPONENT)

	FruitComponent();
	virtual ~FruitComponent();
	void initComponent() override;
	void update() override;
	
	bool getMilagrosa();
private:
	bool milagrosa_; // True si es fruta milagrosa
	double fruitTime = 5; // En segundos, el tiempo que dura como milagrosa y cada cuanto se actualiza
	RandomNumberGenerator& rand_;
	VirtualTimer timer_;
	int spriteWidth = 128;
	int spriteHeight = 128;
	int cerezasPosSprite = 4;
	int peraPosSprite = 7;
};

