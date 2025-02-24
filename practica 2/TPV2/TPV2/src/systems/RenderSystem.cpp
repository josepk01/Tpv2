// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "../components/ImageWithFrames.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawFruits();
	drawPacMan();
	drawGhosts();
	drawScore();
	drawPoints();


}

void RenderSystem::drawPoints() {
	// draw points
	for (auto e : mngr_->getEntities(ecs::grp::POINTS)) {
		mngr_->getComponent<Image>(e)->render();
	}
}
void RenderSystem::drawFruits() {
	for (auto e : mngr_->getEntities(ecs::grp::FRUITS)) {
		auto tr = mngr_->getComponent<Transform>(e);
		auto imgFrames = mngr_->getComponent<ImageWithFrames>(e);
		if (tr != nullptr && imgFrames != nullptr) {
			imgFrames->render();
		}
	}
}


void RenderSystem::drawPacMan() {
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	if (e == nullptr) return; // Si PacMan no est� inicializado, no hacemos nada.

	auto tr = mngr_->getComponent<Transform>(e);
	auto imgFrames = mngr_->getComponent<ImageWithFrames>(e); // Usar ImageWithFrames
	if (tr != nullptr && imgFrames != nullptr) {
		imgFrames->render(); // Renderizar la animaci�n actual.
	}
}

void RenderSystem::drawGhosts() {

	for(auto e : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto tr = mngr_->getComponent<Transform>(e);
		auto imgFrames = mngr_->getComponent<ImageWithFrames>(e); // Usar ImageWithFrames
		if (tr != nullptr && imgFrames != nullptr) {
			imgFrames->render(); // Renderizar la animaci�n actual.
		}
	}
}


void RenderSystem::drawScore() {
	// draw the score
	//
	auto score = mngr_->getSystem<GameCtrlSystem>()->getScore();

	Texture scoreTex(sdlutils().renderer(), "Score: " + std::to_string(score),
			sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
			(sdlutils().width() - scoreTex.width()) / 2.0f, //
			10.0f, //
			scoreTex.width(), //
			scoreTex.height());

	scoreTex.render(dest);

	// draw PacMan Title (es un ejemplo)
	sdlutils().msgs().at("pacmanTitle").render(10, 10);

}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	assert(tex != nullptr);
	tex->render(dest, tr->rot_);
}
