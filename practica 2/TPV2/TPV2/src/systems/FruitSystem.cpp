#include "FruitSystem.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/FruitComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include <math.h> 
#include <cstdlib> 
#include <ctime>   
FruitSystem::FruitSystem() : gridWidth_(10), gridHeight_(10), fruitCount_(0) {
    // Inicialización y cálculos necesarios aquí
}

FruitSystem::~FruitSystem() {
    // Limpieza si es necesario
}

void FruitSystem::initSystem() {
    placeFruits();
}
void FruitSystem::deletefruits() {
    for (auto& fruit : mngr_->getEntities(ecs::grp::FRUITS)) {
        mngr_->setAlive(fruit, false);
    }
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

    srand(time(nullptr)); // Inicializa la semilla del generador de números aleatorios.

    int totalPositions = gridWidth_ * gridHeight_;
    int fruitTarget = static_cast<int>(totalPositions * 0.2); // 20% de las posiciones.

    // Valores para el tamaño de las frutas basados en la pantalla y grid.
    int maxWidth = 800 / gridWidth_;
    int maxHeight = 600 / gridHeight_;
    int fruitSize = std::min(maxWidth, maxHeight);

    int spriteWidth = 128;
    int spriteHeight = 128;

    // Contador para el número actual de frutas colocadas.
    int fruitsPlaced = 0;

    while (fruitsPlaced < fruitTarget) {
        for (int i = 0; i < gridWidth_ && fruitsPlaced < fruitTarget; ++i) {
            for (int j = 0; j < gridHeight_ && fruitsPlaced < fruitTarget; ++j) {
                // Genera un número aleatorio entre 0 y 1.
                float probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                if (probability < 0.2) { // 20% de probabilidad de colocar una fruta aquí.
                    auto entity = mngr_->addEntity(ecs::grp::FRUITS);

                    // Cálculos de posición para la fruta.
                    float x = i * maxWidth + (maxWidth - fruitSize) / 2;
                    float y = j * maxHeight + (maxHeight - fruitSize) / 2;

                    auto tr = mngr_->addComponent<Transform>(entity, Vector2D(x, y), Vector2D(), fruitSize, fruitSize, 0.0f);

                    // Decide entre la cereza y la pera.
                    bool isCherry = rand() % 2 == 0;
                    int frameX = 4 * spriteWidth;
                    int frameY = 1 * spriteHeight;

                    Texture* fruitsTexture = &sdlutils().images().at("pacman_sprites");
                    mngr_->addComponent<ImageWithFrames>(entity,
                        fruitsTexture,
                        8, 8, frameX, frameY, spriteWidth, spriteHeight, 0, 0, 1, 1);

                    mngr_->addComponent<FruitComponent>(entity);

                    fruitsPlaced++;
                    fruitCount_++;
                }
            }
        }
    }
}
bool FruitSystem::isMiraculous(int x, int y) {
    // Implementa tu lógica para determinar si una fruta es milagrosa
    return false; // Ejemplo
}

void FruitSystem::eat() {
    fruitCount_--;
}