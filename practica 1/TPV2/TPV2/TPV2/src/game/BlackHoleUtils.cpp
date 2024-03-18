#include "BlackHoleUtils.h"
#include "../components/Rotate.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

BlackHoleUtils::BlackHoleUtils() :
	rand_(sdlutils().rand()), width_(sdlutils().width()/2), height_(
		sdlutils().height()/2) {
}
BlackHoleUtils::~BlackHoleUtils() {

}

void BlackHoleUtils::create_black_holes(int n) {
	for (int i = 0; i < n; i++) {
		int x = rand_.nextInt(100, 300); // Genera un número entre -300 y -100
		int y = rand_.nextInt(100, 300);  // Genera un número entre 100 y 300

		// Elige aleatoriamente uno de los dos rangos
		x = rand_.nextInt(0, 2) == 0 ? x*-1 : x;
		y = rand_.nextInt(0, 2) == 0 ? y * -1 : y;

		Vector2D p = Vector2D(width_ + x, height_ + y);

		Vector2D c = Vector2D(width_ / 2 + rand_.nextInt(-100, 100),
			height_ / 2 + rand_.nextInt(-100, 100));

		auto g = rand_.nextInt(1, 4);
		generateHole(p, g);
	}
}
void BlackHoleUtils::remove_all_black_holes() {
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::BLACKHOLES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}


void BlackHoleUtils::generateHole(const Vector2D& p, int g) {
	auto mngr = Game::instance()->getMngr();

	auto a = mngr->addEntity(ecs::grp::BLACKHOLES);
	Vector2D v = Vector2D(0, 0);
	mngr->addComponent<Transform>(a, p, v, 40, 40, 0.0f);
	mngr->addComponent<Rotate>(a, 1);
	mngr->addComponent<Image>(a, &sdlutils().images().at("black-hole"));
}