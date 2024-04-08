#pragma once
#include "../ecs/System.h"
#include "../sdlutils/VirtualTimer.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"

class FruitSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::FRUITS)
        FruitSystem();
    virtual ~FruitSystem();

    void initSystem();
    void update() override;
    void checkGameOver();

private:
    void placeFruits();
    bool isMiraculous(int x, int y); // Decide si una fruta en posición x, y es milagrosa
    int gridWidth_; // Ancho del grid de frutas
    int gridHeight_; // Alto del grid de frutas
    int fruitCount_; // Contador de frutas restantes

    int maxWidth = 800 / gridWidth_; // Ancho máximo disponible para cada fruta
    int maxHeight = 600 / gridHeight_; // Alto máximo disponible para cada fruta
    int fruitSize = std::min(maxWidth, maxHeight);

};
