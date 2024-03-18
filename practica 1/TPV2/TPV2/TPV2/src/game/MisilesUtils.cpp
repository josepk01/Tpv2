#include "MisilesUtils.h"

MissilesUtils::MissilesUtils() :
    rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height()) {
}

MissilesUtils::~MissilesUtils() {
}

void MissilesUtils::remove_all_missiles() {
    auto mngr = Game::instance()->getMngr();
    for (auto e : mngr->getEntities(ecs::grp::MISILES)) {
        mngr->setAlive(e, false);
    }
    mngr->refresh();
}

void MissilesUtils::add_missile() {
    generateMissile();
}

void MissilesUtils::generateMissile() {
    auto mngr = Game::instance()->getMngr();

    int x, y;
    int side = rand_.nextInt(0, 3); // Elegir una esquina aleatoriamente
    switch (side) {
    case 0: x = 0; y = 0; break; // Esquina superior izquierda
    case 1: x = width_; y = 0; break; // Esquina superior derecha
    case 2: x = 0; y = height_; break; // Esquina inferior izquierda
    case 3: x = width_; y = height_; break; // Esquina inferior derecha
    }

    Vector2D pos(x, y);
    auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
    auto fighterTR = mngr->getComponent<Transform>(fighter);
    Vector2D dir = (fighterTR->getPos() - pos).normalize();
    float speed = rand_.nextInt(1, 3); // Velocidad aleatoria entre 1 y 3
    Vector2D vel = dir * speed;

    auto missile = mngr->addEntity(ecs::grp::MISILES);

    mngr->addComponent<Transform>(missile, pos, vel, 20, 50, Vector2D(0, -1).angle(vel));
    mngr->addComponent<Follow>(missile, fighterTR->getPos());
    mngr->addComponent<Image>(missile, &sdlutils().images().at("missile"));
}
