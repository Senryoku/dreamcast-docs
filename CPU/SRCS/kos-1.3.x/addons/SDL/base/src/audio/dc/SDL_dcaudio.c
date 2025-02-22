/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    BERO <bero@geocities.co.jp>
    based on SDL_diskaudio.c by Sam Lantinga <slouken@libsdl.org>

    Modified by Lawrence Sebald <bluecrab2887@netscape.net>
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_dcaudio.c,v 1.1 2002/12/09 05:30:22 bardtx Exp $";
#endif

/* Output dreamcast aica */
#include <kos.h>
#include <dc/g2bus.h>

#include "SDL_audio.h"
#include "SDL_error.h"
#include "SDL_audiomem.h"
#include "SDL_audio_c.h"
#include "SDL_timer.h"
#include "SDL_audiodev_c.h"
#include "SDL_dcaudio.h"

#include "aica.h"
#include <dc/spu.h>

/* Audio driver functions */
static int DCAUD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void DCAUD_WaitAudio(_THIS);
static void DCAUD_PlayAudio(_THIS);
static Uint8 *DCAUD_GetAudioBuf(_THIS);
static void DCAUD_CloseAudio(_THIS);

/* Audio driver bootstrap functions */
static int DCAUD_Available(void)
{
	return 1;
}

static void DCAUD_DeleteDevice(SDL_AudioDevice *device)
{
	free(device->hidden);
	free(device);
}

static SDL_AudioDevice *DCAUD_CreateDevice(int devindex)
{
	SDL_AudioDevice *this;

	/* Initialize all variables that we clean on shutdown */
	this = (SDL_AudioDevice *)malloc(sizeof(SDL_AudioDevice));
	if ( this ) {
		memset(this, 0, (sizeof *this));
		this->hidden = (struct SDL_PrivateAudioData *)
				malloc((sizeof *this->hidden));
	}
	if ( (this == NULL) || (this->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( this ) {
			free(this);
		}
		return(0);
	}
	memset(this->hidden, 0, (sizeof *this->hidden));

	/* Set the function pointers */
	this->OpenAudio = DCAUD_OpenAudio;
	this->WaitAudio = DCAUD_WaitAudio;
	this->PlayAudio = DCAUD_PlayAudio;
	this->GetAudioBuf = DCAUD_GetAudioBuf;
	this->CloseAudio = DCAUD_CloseAudio;

	this->free = DCAUD_DeleteDevice;

	spu_init();

	return this;
}

AudioBootStrap DCAUD_bootstrap = {
	"dcaudio", "Dreamcast AICA audio",
	DCAUD_Available, DCAUD_CreateDevice
};

/* This function waits until it is possible to write a full sound buffer */
static void DCAUD_WaitAudio(_THIS)
{
	if (this->hidden->playing) {
		/* wait */
		while(aica_get_pos(0)/this->spec.samples == this->hidden->nextbuf) {
			thd_pass();
		}
	}
}

#define	SPU_RAM_BASE	0xa0800000

static void spu_memload_stereo8(int leftpos,int rightpos,void *src0,size_t size)
{
	uint8 *src = src0;
	uint32 *left  = (uint32*)(leftpos +SPU_RAM_BASE);
	uint32 *right = (uint32*)(rightpos+SPU_RAM_BASE);
	size = (size+7)/8;
	while(size--) {
		unsigned lval,rval;
		lval = *src++;
		rval = *src++;
		lval|= (*src++)<<8;
		rval|= (*src++)<<8;
		lval|= (*src++)<<16;
		rval|= (*src++)<<16;
		lval|= (*src++)<<24;
		rval|= (*src++)<<24;
		g2_write_32(*left++,lval);
		g2_write_32(*right++,rval);
		g2_fifo_wait();
	}
}

static void spu_memload_stereo16(int leftpos,int rightpos,void *src0,size_t size)
{
	uint16 *src = src0;
	uint32 *left  = (uint32*)(leftpos +SPU_RAM_BASE);
	uint32 *right = (uint32*)(rightpos+SPU_RAM_BASE);
	size = (size+7)/8;
	while(size--) {
		unsigned lval,rval;
		lval = *src++;
		rval = *src++;
		lval|= (*src++)<<16;
		rval|= (*src++)<<16;
		g2_write_32(*left++,lval);
		g2_write_32(*right++,rval);
		g2_fifo_wait();
	}
}

static void DCAUD_PlayAudio(_THIS)
{
	SDL_AudioSpec *spec = &this->spec;
	unsigned int offset;

	if (this->hidden->playing) {
		/* wait */
		while(aica_get_pos(0)/spec->samples == this->hidden->nextbuf) {
			thd_pass();
		}
	}

	offset = this->hidden->nextbuf*spec->size;
	this->hidden->nextbuf^=1;
	/* Write the audio data, checking for EAGAIN on broken audio drivers */
	if (spec->channels==1) {
		spu_memload(this->hidden->leftpos+offset,this->hidden->mixbuf,this->hidden->mixlen);
	} else {
		offset/=2;
		if ((this->spec.format&255)==8) {
			spu_memload_stereo8(this->hidden->leftpos+offset,this->hidden->rightpos+offset,this->hidden->mixbuf,this->hidden->mixlen);
		} else {
			spu_memload_stereo16(this->hidden->leftpos+offset,this->hidden->rightpos+offset,this->hidden->mixbuf,this->hidden->mixlen);
		}
	}

	if (!this->hidden->playing) {
		int mode;
		this->hidden->playing = 1;
		mode = (spec->format==AUDIO_S8)?SM_8BIT:SM_16BIT;
		if (spec->channels==1) {
			aica_play(0,mode,this->hidden->leftpos,0,spec->samples*2,spec->freq,255,128,1);
		} else {
			aica_play(0,mode,this->hidden->leftpos ,0,spec->samples*2,spec->freq,255,0,1);
			aica_play(1,mode,this->hidden->rightpos,0,spec->samples*2,spec->freq,255,255,1);
		}
	}
}

static Uint8 *DCAUD_GetAudioBuf(_THIS)
{
	return(this->hidden->mixbuf);
}

static void DCAUD_CloseAudio(_THIS)
{
	aica_stop(0);
	if (this->spec.channels==2) aica_stop(1);
	if ( this->hidden->mixbuf != NULL ) {
		SDL_FreeAudioMem(this->hidden->mixbuf);
		this->hidden->mixbuf = NULL;
	}
}

static int DCAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
	switch(spec->format&0xff) {
	case  8: spec->format = AUDIO_S8; break;
	case 16: spec->format = AUDIO_S16LSB; break;
	default:
		SDL_SetError("Unsupported audio format");
		return(-1);
	}

	/* Update the fragment size as size in bytes */
	SDL_CalculateAudioSpec(spec);

	/* Allocate mixing buffer */
	this->hidden->mixlen = spec->size;
	this->hidden->mixbuf = (Uint8 *) SDL_AllocAudioMem(this->hidden->mixlen);
	if ( this->hidden->mixbuf == NULL ) {
		return(-1);
	}
	memset(this->hidden->mixbuf, spec->silence, spec->size);
	this->hidden->leftpos = 0x11000;
	this->hidden->rightpos = 0x11000+spec->size;
	this->hidden->playing = 0;
	this->hidden->nextbuf = 0;

	/* We're ready to rock and roll. :-) */
	return(0);
}
