// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include "../components/ImageWithFrames.h"

struct Transform;

const float SPEED = 1.0f;
enum class PacManState {
	NORMAL,
	IMMORTAL,
	DEAD // Agregar más estados según sea necesario
};
class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMAN)

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void changePacManState(PacManState newState);
	void update() override;
private:
	Transform* pmTR_;
	ImageWithFrames* pmImage_;
	PacManState pmState_;
	PacManState pmlState_;
	// Las dimensiones de cada frame de Pac-Man basadas en la hoja de sprites proporcionada.
	const int frameWidth = 1028 / 8;  // La hoja de sprites tiene 8 columnas.
	const int frameHeight = 1028 / 8; // La hoja de sprites tiene 8 filas.

};

