#include "FoodSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

FoodSystem::FoodSystem() {}

FoodSystem::~FoodSystem() {
    for (auto& e : fruits) {
        delete e;
    }
}

void FoodSystem::initSystem() {
    generateFruits();
}

void FoodSystem::generateFruits() {
    const int size = 20; // Tamaño de las frutas
    const int rows = 10; // Número de filas y columnas
    const int cols = 15;
    const Vector2D startPos(100, 100); // Posición inicial para empezar a colocar frutas

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto fruit = mngr_->addEntity();
            fruits.push_back(fruit);
            auto* tr = mngr_->addComponent<Transform>(fruit);
            tr->init(Vector2D(startPos.getX() + j * size * 1.5, startPos.getY() + i * size * 1.5), Vector2D(), size, size, 0.0f);
            mngr_->addComponent<Image>(fruit, &sdlutils().images().at("fruit"));
        }
    }
}

void FoodSystem::update() {
    // Aquí puedes actualizar el estado de las frutas milagrosas y manejar la lógica de colisión
}