#pragma once
#include "BlackHoleFacade.h"

class Vector2D;
class RandomNumberGenerator;

class BlackHoleUtils : public BlackHoleFacade
{
public:
	BlackHoleUtils();
	~BlackHoleUtils();

	void create_black_holes(int n) override;
	void remove_all_black_holes() override;
	void teleport_astroid(entity_t a) override;
private:
	void generateHole(const Vector2D& p, int g);
	RandomNumberGenerator& rand_;
	int width_;
	int height_;
};

