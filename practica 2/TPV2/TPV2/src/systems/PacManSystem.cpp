// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr), 
		lives_(3) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	std::cout << "CREAR PACMAN";
	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() + s) / 2.0f;
	auto y = (sdlutils().height() + s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	// Inicializar componente de animaci�n con la primera animaci�n (normal)
	Texture* pacmanTexture = &sdlutils().images().at("pacman_sprites");
	pmImage_ = mngr_->addComponent<ImageWithFrames>(pacman,
		pacmanTexture,
		8, // N�mero total de columnas en la hoja de sprites.
		8, // N�mero total de filas en la hoja de sprites.
		0, // X inicial de la animaci�n en la textura (fila de animaci�n normal).
		0, // Y inicial de la animaci�n en la textura (columna de animaci�n normal).
		frameWidth, // Ancho de cada frame.
		frameHeight, // Alto de cada frame.
		0, // Columna inicial para la animaci�n normal.
		0, // Fila inicial para la animaci�n normal.
		1, // N�mero de columnas (frames) para la animaci�n normal.
		4  // N�mero de filas para la animaci�n normal.
	);
	pmState_ = PacManState::NORMAL; // Estado inicial de Pac-Man.
}

void PacManSystem::update() {

	std::cout << isImmortal;

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = 90.0f;
			pmTR_->vel_ = Vector2D(SPEED * 0.1, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = -90.0f;
			pmTR_->vel_ = Vector2D(-SPEED * 0.1, 0);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
			pmTR_->rot_ = 0.0f;
			pmTR_->vel_ = Vector2D(0, -SPEED * 0.1);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			pmTR_->rot_ = 180.0f;
			pmTR_->vel_ = Vector2D(0, SPEED * 0.1);
		}

	}

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	// Cambiar el estado de animaci�n en funci�n de la l�gica del juego
	switch (pmState_) {
	case PacManState::NORMAL:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::NORMAL);
		break;
	case PacManState::IMMORTAL:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::IMMORTAL);
		break;
	case PacManState::DEAD:
		if (pmlState_ != pmState_)
		changePacManState(PacManState::DEAD);
		break;
	}
	checkImmortalState();
}

bool PacManSystem::isInmortal()
{
	return pmState_ == PacManState::IMMORTAL;
}

void PacManSystem::changePacManState(PacManState newState) {
    // Asegurarse de cambiar la animaci�n solo si el estado ha cambiado.
    if (pmState_ != newState) {
        pmState_ = newState;
        switch (pmState_) {
            case PacManState::NORMAL:
                // Supongamos que la animaci�n normal est� en la primera fila (fila 0).
                pmImage_->changeAnimation(0, 4); // Cambiar a la animaci�n en la fila 0 con 4 frames.
                break;
            case PacManState::IMMORTAL:
                // La animaci�n inmortal est� en la tercera fila (fila 2).
                pmImage_->changeAnimation(2, 4); // Cambiar a la animaci�n en la fila 2 con 4 frames.
                break;
            case PacManState::DEAD:
                // La animaci�n de muerte est� en la cuarta fila (fila 3).
                pmImage_->changeAnimation(3, 4); // Cambiar a la animaci�n en la fila 3 con 4 frames.
                break;
            // A�adir m�s estados y animaciones seg�n sea necesario.
        }
    }
}


void PacManSystem::startImmortalState() {
	changePacManState(PacManState::IMMORTAL);
	immortalStartTime_ = SDL_GetTicks();
	isImmortal = true;
}

void PacManSystem::checkImmortalState() {
	if (isImmortal && (SDL_GetTicks() - immortalStartTime_ >= 5000)) { // 5 segundos
		isImmortal = false;
		changePacManState(PacManState::NORMAL);
		Message m;
		m.id = _m_IMMUNITY_END;
		mngr_->send(m);
	}
}
// M�todo para perder una vida y reiniciar o terminar el juego
void PacManSystem::loseLife() {
	if (lives_ >= 0) {
		--lives_;
		// Si todav�a quedan vidas, reinicia la posici�n de Pac-Man
		resetPacManPosition();

		if (lives_ == 0) {
			// Cambiar a estado muerto si no quedan vidas
			reset();
			changePacManState(PacManState::DEAD);
			// Aqu� puedes agregar l�gica para terminar el juego o reiniciarlo completamente
		}

	}
}

// M�todo para reiniciar la posici�n de Pac-Man y cambiarlo al estado normal
void PacManSystem::resetPacManPosition() {
	auto s = 50.0f;
	auto x = (sdlutils().width() + s) / 2.0f;
	auto y = (sdlutils().height() + s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	changePacManState(PacManState::NORMAL);
}