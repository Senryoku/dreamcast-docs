/*
   Tsunami for KallistiOS 1.2.0

   tintfader.cpp

   Copyright (C)2003 Dan Potter
*/

#include <tsu/drawable.h>
#include <tsu/anims/tintfader.h>

CVSID("$Id: tintfader.cpp,v 1.1 2003/04/24 02:57:20 bardtx Exp $");

TintFader::TintFader(const Color & fade_to, const Color & delta) {
	m_fade_to = fade_to;
	m_delta = delta;
}

TintFader::~TintFader() { }

void TintFader::nextFrame(Drawable *t) {
	Color c = t->getTint();
	c += m_delta;
	
	if (clamp(c)) {
		c = m_fade_to;
		complete(t);
	}

	t->setTint(c);
}

bool TintFader::clamp(Color & col) {
	bool allfinished = true;
	float cols[4] = {col.a, col.r, col.g, col.b};
	float tos[4] = {m_fade_to.a, m_fade_to.r, m_fade_to.g, m_fade_to.b};
	float deltas[4] = {m_delta.a, m_delta.r, m_delta.g, m_delta.b};

	for (int i=0; i<4; i++) {
		if (deltas[i] < 0.0f) {
			if (cols[i] <= tos[i])
				cols[i] = tos[i];
			else
				allfinished = false;
		} else {
			if (cols[i] >= tos[i])
				cols[i] = tos[i];
			else
				allfinished = false;
		}
	}

	col = Color(cols[0], cols[1], cols[2], cols[3]);

	return allfinished;
}
