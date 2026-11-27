#include "transform/Transformation.h"

void Transformation::addRef() {
	++refCount;
}

void Transformation::release() {
	if (--refCount <= 0) {
		delete this;
	}
}
