// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <string>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture *tex, int rows, int cols, int x, int y,
		int w, int h, int srow, int scol, int nrow, int ncol) :
		tex_(tex), //
		tr_(nullptr), //
		currFrameR_(0), //
		currFrameC_(0), //
		x_(x), //
		y_(y), //
		w_(w), //
		h_(h), //
		srow_(srow), //
		scol_(scol), //
		nrow_(nrow), //
		ncol_(ncol), //
		lastFrameChange_(0)
{
	frameWidth_ = tex_->width() / cols;
	frameHeight_ = tex->height() / rows;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ImageWithFrames::update() {
	std::cout << "ImageWithFrames ";
	// Asegurarse de que la actualización del frame ocurra solo si hay más de un frame para animar
	if (ncol_ > 0 && sdlutils().virtualTimer().currTime() > lastFrameChange_ + 50) {
		lastFrameChange_ = sdlutils().virtualTimer().currTime();
		currFrameC_ = (currFrameC_ + 1) % ncol_;
	}
}

void ImageWithFrames::render() {
	// Asumiendo que currFrameR_ se establece correctamente al cambiar de animación,
	// solo necesitamos preocuparnos por currFrameC_ aquí.
	int frameX = x_ + currFrameC_ * frameWidth_;
	int frameY = y_ + currFrameR_ * frameHeight_;
	SDL_Rect src = build_sdlrect(frameX, frameY, frameWidth_, frameHeight_);
	SDL_Rect dest = build_sdlrect(tr_->pos_.getX(), tr_->pos_.getY(), tr_->width_, tr_->height_);

	tex_->render(src, dest, tr_->rot_);
}


void ImageWithFrames::changeAnimation(int row, int nFrames) {
	currFrameR_ = row; // Establece la fila actual para la animación.
	ncol_ = nFrames; // Establece el número total de frames en la animación.
	currFrameC_ = 0; // Reinicia al primer frame de la nueva animación.
	lastFrameChange_ = sdlutils().virtualTimer().currTime(); // Reinicia el temporizador de cambio de frame.
}
