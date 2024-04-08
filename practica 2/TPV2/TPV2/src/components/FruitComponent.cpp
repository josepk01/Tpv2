#include "FruitComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../game/Game.h"
#include "../ecs/Manager.h"

FruitComponent::FruitComponent() : rand_(sdlutils().rand()), milagrosa_(false){

}
FruitComponent::~FruitComponent() {

}

void FruitComponent::initComponent() {
}
void FruitComponent::update() {
    if (timer_.currTime() > fruitTime * 1000) {
        Game::instance().getMngr()->getComponent<ImageWithFrames>(ent_);
        // cada cierto tiempo vemos si se da la probabilidad de que la fruta se vuelva milagrosa
        timer_.reset();
        if (!milagrosa_) {
            // Actualizamos a fruta milagrosa si se da la probabilidad
            auto g = rand_.nextInt(0, 5);

            if (g == 0) {
                Game::instance().getMngr()->getComponent<ImageWithFrames>(ent_)->changeAnimation(1, 1);
                milagrosa_ = true;
            }
        }
        else {
            Game::instance().getMngr()->getComponent<ImageWithFrames>(ent_)->changeAnimation(0, 0);
            milagrosa_ = false;
        }
    }
}

bool FruitComponent::getMilagrosa() {
	return milagrosa_;
}




