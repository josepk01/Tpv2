#include "FruitSystem.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include <math.h> 
FruitSystem::FruitSystem() : gridWidth_(10), gridHeight_(10), fruitCount_(0) {
    // Inicialización y cálculos necesarios aquí
}

FruitSystem::~FruitSystem() {
    // Limpieza si es necesario
}

void FruitSystem::initSystem() {
    placeFruits();
}

void FruitSystem::update() {
    // Actualiza el estado de las frutas milagrosas aquí si es necesario
}

void FruitSystem::checkGameOver() {
    if (fruitCount_ <= 0) {
        // Cambiar al estado GameOver
    }
}

void FruitSystem::placeFruits() {
    std::cout << "Colocando frutas en el grid...";

    int maxWidth = 800 / gridWidth_; // Calcula el ancho máximo para cada fruta
    int maxHeight = 600 / gridHeight_; // Calcula el alto máximo para cada fruta
    int fruitSize = std::min(maxWidth, maxHeight); // Usa el menor de los dos para mantener la proporción

    for (int i = 0; i < gridWidth_; ++i) {
        for (int j = 0; j < gridHeight_; ++j) {
            auto entity = mngr_->addEntity(ecs::grp::FRUITS);

            // Ajusta la posición para centrar las frutas en sus celdas
            float x = i * maxWidth + (maxWidth - fruitSize) / 2;
            float y = j * maxHeight + (maxHeight - fruitSize) / 2;

            auto tr = mngr_->addComponent<Transform>(entity, Vector2D(x, y), Vector2D(), fruitSize, fruitSize, 0.0f);

            // Selecciona aleatoriamente entre cereza y pera
            bool isCherry = rand() % 2 == 0;
            int frameX = isCherry ? 5 : 7; // Usando los valores dados para cherryX y pearX
            int frameY = 2; // Común para cereza y pera

            Texture* fruitsTexture = &sdlutils().images().at("pacman_sprites");
            mngr_->addComponent<ImageWithFrames>(entity,
                fruitsTexture,
                8, 8, frameX, frameY, fruitSize, fruitSize, 0, 0, 1, 1);

            fruitCount_++;
        }
    }
}


bool FruitSystem::isMiraculous(int x, int y) {
    // Implementa tu lógica para determinar si una fruta es milagrosa
    return false; // Ejemplo
}
