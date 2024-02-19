// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

namespace ecs {

Manager::Manager() :
		ents_(), //
		hdlrs_() //
{
	// we reserve space for 100 entities, just to avoid resizing. You
	// can adjust this number.
	//
	ents_.reserve(100);

}

Manager::~Manager() {

	// delete all entities
	//
	for (auto e : ents_)
		delete e;
}

void Manager::refresh() {

	// remove all dead
	ents_.erase( //
			remove_if(ents_.begin(), ents_.end(), [](Entity *e) {
				if (e->isAlive()) {
					return false;
				} else {
					delete e;
					return true;
				}
			}), //
			ents_.end());

}

} // end of namespace
