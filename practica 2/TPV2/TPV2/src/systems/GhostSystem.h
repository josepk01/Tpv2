#pragma once
#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"

class Vector2D;
class RandomNumberGenerator;

class GhostSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::GHOSTS)
	GhostSystem();
	virtual ~GhostSystem();

	void remove_all_ghost();
	void update() override;
	void eateable_state();

private:
	void generateGhost();
	RandomNumberGenerator& rand_;
	int width_;
	int height_;
	double timeToSpawn_ = 3; // En segundos
	int maxGhosts_ = 10;
	int currentGhosts_ = 0;
	VirtualTimer timer_;
	bool vulnerable_ = false; // Indica si los fantasmas son azules y se pueden comer
};


