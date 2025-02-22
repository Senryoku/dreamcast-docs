/**************************************************************************
 *
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *
 *  Copyright (C) 1992 - 1997 Microsoft Corporation.  All Rights Reserved.
 *
 **************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include "dibmap.h"

extern NEAR PASCAL MemCopy(LPVOID,LPVOID,DWORD);
extern NEAR PASCAL MemFill(LPVOID,DWORD,BYTE);

void Histogram24(BYTE *pb, int dx, int dy, WORD WidthBytes, LPHISTOGRAM lpHistogram);
void Histogram16(BYTE *pb, int dx, int dy, WORD WidthBytes, LPHISTOGRAM lpHistogram);
void Histogram8(BYTE *pb, int dx, int dy, WORD WidthBytes, LPHISTOGRAM lpHistogram, LPWORD lpColors);
void Histogram4(BYTE *pb, int dx, int dy, WORD WidthBytes, LPHISTOGRAM lpHistogram, LPWORD lpColors);
void Histogram1(BYTE *pb, int dx, int dy, WORD WidthBytes, LPHISTOGRAM lpHistogram, LPWORD lpColors);

void Reduce24(BYTE *pbIn, int dx, int dy, WORD cbIn, BYTE *pbOut, WORD cbOut, LPBYTE lp16to8);
void Reduce16(BYTE *pbIn, int dx, int dy, WORD cbIn, BYTE *pbOut, WORD cbOut, LPBYTE lp16to8);
void Reduce8(BYTE *pbIn, int dx, int dy, WORD cbIn, BYTE *pbOut, WORD cbOut, LPBYTE lp8to8);
void Reduce4(BYTE *pbIn, int dx, int dy, WORD cbIn, BYTE *pbOut, WORD cbOut, LPBYTE lp8to8);
void Reduce1(BYTE *pbIn, int dx, int dy, WORD cbIn, BYTE *pbOut, WORD cbOut, LPBYTE lp8to8);

LPHISTOGRAM lpHistogram;

//
// InitHistogram
//
// create a zero'ed histogram table, or initialize a existing table
// to all zeros.
//
LPHISTOGRAM InitHistogram(
	LPHISTOGRAM lpHistogram)
{
	if (lpHistogram == NULL)
		lpHistogram = (LPVOID)GlobalAllocPtr(GHND, 32768L * sizeof(DWORD));

	return lpHistogram;
}

//
// FreeHistogram
//
// free a histogram table
//
void FreeHistogram(
	LPHISTOGRAM lpHistogram)
{
	GlobalFreePtr(lpHistogram);
}

//
// DibHistogram
//
// take all colors in a dib and increment its entry in the Histogram table
//
// supports the following DIB formats: 1,4,8,16,24
//
BOOL DibHistogram(
	LPBITMAPINFOHEADER lpbi,
	LPBYTE lpBits,
	int x,
	int y,
	int dx,
	int dy,
	LPHISTOGRAM lpHistogram)
{
	int		i;
	WORD		WidthBytes;
	RGBQUAD FAR *	prgbq;
	WORD		argb16[256];

	if (lpbi == NULL || lpHistogram == NULL)
		return FALSE;

	if (lpbi->biClrUsed == 0 && lpbi->biBitCount <= 8)
		lpbi->biClrUsed = (1 << (int)lpbi->biBitCount);

	if (lpBits == NULL)
		lpBits = (LPBYTE)lpbi + (int)lpbi->biSize
			+ (int)lpbi->biClrUsed*sizeof(RGBQUAD);

	WidthBytes = (WORD)(((LONG)lpbi->biBitCount * lpbi->biWidth + 7) / 8 + 3) & ~3;

	((BYTE *)lpBits) += (DWORD)y*WidthBytes + ((x*(int)lpbi->biBitCount)/8);

	if (dx < 0 || dx > (int)lpbi->biWidth)
		dx = (int)lpbi->biWidth;

	if (dy < 0 || dy > (int)lpbi->biHeight)
		dy = (int)lpbi->biHeight;

	if ((int)lpbi->biBitCount <= 8)
	{
		prgbq = (LPVOID)((LPBYTE)lpbi + lpbi->biSize);

		for (i=0; i<(int)lpbi->biClrUsed; i++)
		{
			argb16[i] = (WORD) RGB16(prgbq[i].rgbRed,prgbq[i].rgbGreen,prgbq[i].rgbBlue);
		}

		for (i=(int)lpbi->biClrUsed; i<256; i++)
		{
			argb16[i] = 0x0000;	// just in case!
		}
	}

	switch ((int)lpbi->biBitCount)
	{
		case 24:
			Histogram24(lpBits, dx, dy, WidthBytes, lpHistogram);
			break;

		case 16:
			Histogram16(lpBits, dx, dy, WidthBytes, lpHistogram);
			break;

		case 8:
			Histogram8(lpBits, dx, dy, WidthBytes, lpHistogram, argb16);
			break;

		case 4:
			Histogram4(lpBits, dx, dy, WidthBytes, lpHistogram, argb16);
			break;

		case 1:
			Histogram1(lpBits, dx, dy, WidthBytes, lpHistogram, argb16);
			break;
	}
}

//
// will convert the given DIB to a 8bit DIB with the specifed palette
//
LPBITMAPINFOHEADER DibReduce(
	LPBITMAPINFOHEADER lpbiIn,
	LPBYTE pbIn,
	HPALETTE hpal,
	LPBYTE lp16to8)
{
	LPBITMAPINFOHEADER	lpdib;
	WORD			nPalColors;  // NOTE win32 GetObject ONLY returns
                                             // 2 bytes for HPALs
	int			nDibColors;
	WORD			cbOut;
	WORD			cbIn;
	BYTE			xlat[256];
	BYTE *		pbOut;
	RGBQUAD FAR *		prgb;
	DWORD			dwSize;
	int			i;
	int			dx;
	int			dy;
	PALETTEENTRY		pe;

	dx	= (int)lpbiIn->biWidth;
	dy	= (int)lpbiIn->biHeight;
	cbIn	= (WORD)((((UINT)lpbiIn->biBitCount*dx+7)/8+3)&~3);
	cbOut	= (WORD)((dx+3)&~3);

	GetObject(hpal, sizeof(WORD), (LPVOID)&nPalColors);
	nDibColors = (int)lpbiIn->biClrUsed;

	if (nDibColors == 0 && lpbiIn->biBitCount <= 8)
		nDibColors = (1 << (int)lpbiIn->biBitCount);

	if (pbIn == NULL)
		pbIn = (LPBYTE)lpbiIn + (int)lpbiIn->biSize + nDibColors*sizeof(RGBQUAD);

	dwSize = (DWORD)cbOut * dy;

	lpdib = GlobalAllocPtr(GMEM_MOVEABLE,sizeof(BITMAPINFOHEADER)
		+ nPalColors*sizeof(RGBQUAD) + dwSize);

	if (!lpdib)
		return NULL;

	lpdib->biSize		= sizeof(BITMAPINFOHEADER);
	lpdib->biWidth		= lpbiIn->biWidth;
	lpdib->biHeight		= lpbiIn->biHeight;
	lpdib->biPlanes		= 1;
	lpdib->biBitCount	= 8;
	lpdib->biCompression	= BI_RGB;
	lpdib->biSizeImage	= dwSize;
	lpdib->biXPelsPerMeter	= 0;
	lpdib->biYPelsPerMeter	= 0;
	lpdib->biClrUsed	= (DWORD)nPalColors;
	lpdib->biClrImportant	= 0;

	pbOut	= (LPBYTE)lpdib + (int)lpdib->biSize + nPalColors*sizeof(RGBQUAD);
	prgb	= (LPVOID)((LPBYTE)lpdib + (int)lpdib->biSize);

	for (i=0; i<(int)nPalColors; i++)
	{
		GetPaletteEntries(hpal, i, 1, &pe);

		prgb[i].rgbRed		= pe.peRed;
		prgb[i].rgbGreen	= pe.peGreen;
		prgb[i].rgbBlue		= pe.peBlue;
		prgb[i].rgbReserved	= 0;
	}

	if ((int)lpbiIn->biBitCount <= 8)
	{
		prgb = (LPVOID)((LPBYTE)lpbiIn + lpbiIn->biSize);

		for (i=0; i<nDibColors; i++)
			xlat[i] = lp16to8[RGB16(prgb[i].rgbRed,prgb[i].rgbGreen,prgb[i].rgbBlue)];

		for (; i<256; i++)
			xlat[i] = 0;
	}

	switch ((int)lpbiIn->biBitCount)
	{
		case 24:
			Reduce24(pbIn, dx, dy, cbIn, pbOut, cbOut, lp16to8);
			break;

		case 16:
			Reduce16(pbIn, dx, dy, cbIn, pbOut, cbOut, lp16to8);
			break;

		case 8:
			Reduce8(pbIn, dx, dy, cbIn, pbOut, cbOut, xlat);
			break;

		case 4:
			Reduce4(pbIn, dx, dy, cbIn, pbOut, cbOut, xlat);
			break;

		case 1:
			Reduce1(pbIn, dx, dy, cbIn, pbOut, cbOut, xlat);
			break;
	}

	return lpdib;
}

///////////////////////////////////////////////////////////////////////////////
// cluster.c
///////////////////////////////////////////////////////////////////////////////

#define IN_DEPTH	5		// # bits/component kept from input
#define IN_SIZE		(1 << IN_DEPTH)	// max value of a color component

typedef enum { red, green, blue } color;

typedef struct tagCut
{
	long lvariance;		// for int version
	int cutpoint;
	unsigned long rem;	// for experimental fixed point
	color cutaxis;
	long w1, w2;
	double variance;
} Cut;

typedef struct tagColorBox	// from cluster.c
{
	struct tagColorBox *next;		/* pointer to next box */
	int rmin, rmax, gmin, gmax, bmin, bmax;	/* bounding box */
	long variance, wt;			/* weighted variance */
	long sum[3];				/* sum of values */
} ColorBox;

static int InitBoxes(int nBoxes);
static void DeleteBoxes(void);
static int SplitBoxAxis(ColorBox *box, Cut cutaxis);
static void ShrinkBox(ColorBox *box);
static int ComputePalette(LPHISTOGRAM lpHistogram, LPBYTE lp16to8, LPPALETTEENTRY palette);
static COLORREF DetermineRepresentative(ColorBox *box, int palIndex);
static Cut FindSplitAxis(ColorBox *box);
static void SplitBox(ColorBox *box);
static void SortBoxes(void);

HANDLE hBoxes;
ColorBox	*UsedBoxes;
ColorBox	*FreeBoxes;
LPBYTE		glp16to8;

//#define hist(r,g,b) ((DWORD *)glpHistogram)[(WORD)(b) | ((WORD)(g)<<IN_DEPTH) | ((WORD)(r)<<(IN_DEPTH*2))]
#define hist(r,g,b) GetHistogram((BYTE)(r),(BYTE)(g),(BYTE)(b))

#pragma optimize ("", off)
//
// set FS == lpHistogram.sel, so we can get at it quickly!
//
void NEAR PASCAL UseHistogram(
	LPHISTOGRAM lpHistogramToSet)
{
        lpHistogram = lpHistogramToSet;
}

//
// get the DOWRD histogram count of a RGB
//
DWORD near _fastcall GetHistogram(
	BYTE r,
	BYTE g,
	BYTE b)
{
        return lpHistogram[((UINT)r << 10 ) + ((UINT)g << 5) + (UINT)b];
}

//
// increment the histogram count of a RGB16
//
//
// #define IncHistogram(w) if (lpHistogram[(WORD)(w)] < 0xFFFFFFFF)
//				lpHistogram[(WORD)(w)]++;
//
void near _fastcall IncHistogram(WORD rgb16)
{
    if (lpHistogram[rgb16] != (DWORD)-1)
        lpHistogram[rgb16]++;
}

#pragma optimize ("", on)

// !!! C8 generates a Jump into the middle of a 2 byte instruction
// !!! Stupid C8!
#pragma optimize ("", off)

//
// HistogramPalette
//
// given a histogram, will reduce it to 'nColors' number of colors.
// returns a optimal palette.  if specifed lp16to8 will contain the
// translate table from RGB16 to the palette index.
//
// you can specify lpHistogram as lp16to8
//
HPALETTE HistogramPalette(
	LPHISTOGRAM lpHistogram,
	LPBYTE lp16to8,
	int nColors)
{
	struct {
		WORD	palVersion;
		WORD	palNumEntries;
		PALETTEENTRY palPalEntry[256];
	} pal;

	WORD		w;
	DWORD		dwMax;
	COLORREF	rgb;
	ColorBox	*box;
	int		i;

	//
	// the 'C' code cant handle >64k histogram counts.
	// !!!fix this
	//
	for (dwMax=0,w=0; w<0x8000; w++)
		dwMax = max(dwMax,lpHistogram[w]);

	while (dwMax > 0xFFFFl)
	{
		for (w=0; w<0x8000; w++)
			lpHistogram[w] /= 2;

		dwMax /= 2;
	}

	if (!InitBoxes(min(nColors, 236)))
		return NULL;

	UseHistogram(lpHistogram);
	glp16to8 = lp16to8;

	/* while there are free boxes left, split the largest */

	i = 0;

	do {
		i++;
		SplitBox(UsedBoxes);
	}
	while (FreeBoxes && UsedBoxes->variance);

	SortBoxes();

	i=0;

	//
	// add some standard colors to the histogram
	//
	if (nColors > 236)
	{
		HDC hdc;

		hdc = GetDC(NULL);

		if (GetDeviceCaps(hdc, RASTERCAPS) & RC_PALETTE)
		{
			GetSystemPaletteEntries(hdc, 0,	
				10, &pal.palPalEntry[0]);
			GetSystemPaletteEntries(hdc, 246,
				10, &pal.palPalEntry[246]);

			i = 10;
		}

		ReleaseDC(NULL, hdc);
	}

	/* Generate the representitives and the associated Palette mapping */
	/* NOTE:  Might loop less than nColors times.                      */
	for (box = UsedBoxes; box; box = box->next, i++)
	{
		rgb = DetermineRepresentative(box, i);
		pal.palPalEntry[i].peRed	= GetRValue(rgb);
		pal.palPalEntry[i].peGreen	= GetGValue(rgb);
		pal.palPalEntry[i].peBlue	= GetBValue(rgb);
		pal.palPalEntry[i].peFlags	= 0;
	}

	DeleteBoxes();

	if (nColors > 236)
	{
		for (; i<246; i++)
		{
			pal.palPalEntry[i].peRed	= 0;
			pal.palPalEntry[i].peGreen	= 0;
			pal.palPalEntry[i].peBlue	= 0;
			pal.palPalEntry[i].peFlags	= 0;
		}

		i = 256;
	}

	glp16to8 = NULL;

	pal.palVersion		= 0x300;
	pal.palNumEntries	= (WORD)i;
	return CreatePalette((LPLOGPALETTE)&pal);
}

#pragma optimize ("", on)

static void SortBoxes(void)
{
	ColorBox *box;
	ColorBox *newList;
	ColorBox *insBox;
	ColorBox *nextBox;

	newList = UsedBoxes;
	nextBox = newList->next;
	newList->next = NULL;

	for (box = nextBox; box; box = nextBox) { // just an insertion sort...
			nextBox = box->next;
			if (box->wt > newList->wt) {
					box->next = newList;
					newList = box;
			} else {
					for (insBox = newList;
							insBox->next && (box->wt < insBox->next->wt);
							insBox = insBox->next) ;
					box->next = insBox->next;
					insBox->next = box;
			}
	}

	UsedBoxes = newList;
}


/*
	allocate space for nBoxes boxes, set up links.  On exit UsedBoxes
	points to one box, FreeBoxes points to remaining (nBoxes-1) boxes.
	return 0 if successful.
*/

static BOOL InitBoxes(
	int nBoxes)
{
	int i;

	hBoxes = LocalAlloc(LHND, nBoxes*sizeof(ColorBox));
	if (!hBoxes)
		return FALSE;

	UsedBoxes = (ColorBox*)LocalLock(hBoxes);
	FreeBoxes = UsedBoxes + 1;
	UsedBoxes->next = NULL;

	for (i = 0; i < nBoxes - 1; ++i)
	{
		FreeBoxes[i].next = FreeBoxes + i + 1;
	}
	FreeBoxes[nBoxes-2].next = NULL;

	/* save the bounding box */
	UsedBoxes->rmin = UsedBoxes->gmin = UsedBoxes->bmin = 0;
	UsedBoxes->rmax = UsedBoxes->gmax = UsedBoxes->bmax = IN_SIZE - 1;
	UsedBoxes->variance = 9999999;	/* arbitrary large # */

	return TRUE;
}

static void DeleteBoxes(void)
{
	LocalUnlock(hBoxes);
	LocalFree(hBoxes);
	hBoxes = NULL;
}

static void SplitBox(
	ColorBox *box)
{
	/*
	split box into two roughly equal halves and update the data structures
	appropriately.
	*/
	Cut cutaxis;
	ColorBox *temp, *temp2, *prev;

	cutaxis = FindSplitAxis(box);

	/* split the box along that axis.  If rc != 0 then the box contains
	one color, and should not be split
	*/
	if (SplitBoxAxis(box, cutaxis))
		return;

	/* shrink each of the boxes to fit the points they enclose */
	ShrinkBox(box);
	ShrinkBox(FreeBoxes);

	/* move old box down in list, if necessary */
	if (box->next && box->variance < box->next->variance)
	{
		UsedBoxes = box->next;
		temp = box;
		do {
			prev = temp;
			temp = temp->next;
		} while (temp && temp->variance > box->variance);
		box->next = temp;
		prev->next = box;
	}

	/* insert the new box in sorted order (descending), removing it
	from the free list.
	*/
	if (FreeBoxes->variance >= UsedBoxes->variance)
	{
		temp = FreeBoxes;
		FreeBoxes = FreeBoxes->next;
		temp->next = UsedBoxes;
		UsedBoxes = temp;
	}
	else
	{
		temp = UsedBoxes;
		do {
			prev = temp;
			temp = temp->next;
		} while (temp && temp->variance > FreeBoxes->variance);
		temp2 = FreeBoxes->next;
		FreeBoxes->next = temp;
		prev->next = FreeBoxes;
		FreeBoxes = temp2;
	}
}

static Cut FindSplitAxis(
	ColorBox *box)
{
	unsigned long	proj_r[IN_SIZE],proj_g[IN_SIZE],proj_b[IN_SIZE];
	unsigned long	f;
	double		currentMax,mean;
	unsigned long	w,w1,m,m1;
	int		r,g,b;
	int		bestCut;
	color		bestAxis;
	Cut		cutRet;
	double		temp1,temp2;
	
	for (r = 0; r < IN_SIZE; r++) {
		proj_r[r] = proj_g[r] = proj_b[r] = 0;
	}
	
	w = 0;
	
	// Project contents of box down onto axes
	for (r = box->rmin; r <= box->rmax; r++) {
		for (g = box->gmin; g <= box->gmax; ++g) {
			for (b = box->bmin; b <= box->bmax; ++b) {
				f = hist(r,g,b);
				proj_r[r] += f;
				proj_g[g] += f;
				proj_b[b] += f;
			}
		}
		w += proj_r[r];
	}

	currentMax = 0.0f;

#define Check_Axis(l,color)					\
	m = 0;							\
	for (l = box->l##min; l <= box->l##max; (l)++) {	\
		m += l * proj_##l[l];				\
	}							\
	mean = ((double) m) / ((double) w);			\
								\
	w1 = 0;							\
	m1 = 0;							\
	for (l = box->l##min; l <= box->l##max; l++) {		\
		w1 += proj_##l[l];				\
		if (w1 == 0)					\
			continue;				\
		if (w1 == w)					\
			break;					\
		m1 += l * proj_##l[l];				\
		temp1 = mean - (((double) m1) / ((double) w1));	\
		temp2 = (((double) w1) / ((double) (w-w1))) * temp1 * temp1; \
		if (temp2 > currentMax) {			\
			bestCut = l;				\
			bestAxis = color;			\
			currentMax = temp2;			\
		}						\
	}
	
	Check_Axis(r,red);
	Check_Axis(g,green);
	Check_Axis(b,blue);
	
	cutRet.cutaxis = bestAxis;
	cutRet.cutpoint = bestCut;
	
	return cutRet;
}

static int SplitBoxAxis(
	ColorBox *box,
	Cut cutaxis)
{
	/*
	Split box along splitaxis into two boxes, one of which is placed
	back in box, the other going in the first free box (FreeBoxes)
	If the box only contains one color, return non-zero, else return 0.
	*/
	ColorBox *next;

	if ( box->variance == 0)
		return 1;

	/* copy all non-link information to new box */
	next = FreeBoxes->next;
	*FreeBoxes = *box;
	FreeBoxes->next = next;

	switch (cutaxis.cutaxis)
	{
		case red:
			box->rmax = cutaxis.cutpoint;
			FreeBoxes->rmin = cutaxis.cutpoint+1;
			break;
		case green:
			box->gmax = cutaxis.cutpoint;
			FreeBoxes->gmin = cutaxis.cutpoint+1;
			break;
		case blue:
			box->bmax = cutaxis.cutpoint;
			FreeBoxes->bmin = cutaxis.cutpoint+1;
			break;
	}

	return 0;
}

static void ShrinkBox(
	ColorBox *box)
{
	unsigned long n, sxx, sx2, var, quotient, remainder;
	int r,g,b;
	unsigned long f;
	unsigned long	proj_r[IN_SIZE],proj_g[IN_SIZE],proj_b[IN_SIZE];

	n = 0;
	
	for (r = 0; r < IN_SIZE; r++) {
		proj_r[r] = proj_g[r] = proj_b[r] = 0;
	}
	
	// Project contents of box down onto axes
	for (r = box->rmin; r <= box->rmax; r++) {
		for (g = box->gmin; g <= box->gmax; ++g) {
			for (b = box->bmin; b <= box->bmax; ++b) {
				f = hist(r,g,b);
				proj_r[r] += f;
				proj_g[g] += f;
				proj_b[b] += f;
			}
		}
		n += proj_r[r];
	}
	
	box->wt = n;
	var = 0;
	
#define AddAxisVariance(c)						\
	sxx = 0; sx2 = 0;						\
	for (c = box->c##min; c <= box->c##max; c++) {			\
		sxx += proj_##c[c] * c * c;				\
		sx2 += proj_##c[c] * c;					\
	}								\
	quotient = sx2 / n; /* This stuff avoids overflow */		\
	remainder = sx2 % n;						\
	var += sxx - quotient * sx2 - ((remainder * sx2)/n);
	
	AddAxisVariance(r);
	AddAxisVariance(g);
	AddAxisVariance(b);

	box->variance = var;
}

static COLORREF DetermineRepresentative(
	ColorBox *box,
	int palIndex)
{
	/*
	determines the rgb value to represent the pixels contained in
	box.  nbits is the # bits/component we're allowed to return.
	*/
	
	long f;
	long Rval, Gval, Bval;
	unsigned long total;
	int r, g, b;
	int i;

	/* compute the weighted sum of the elements in the box */
	Rval = Gval = Bval = total = 0;
	for (r = box->rmin; r <= box->rmax; ++r)
	{
		for (g = box->gmin; g <= box->gmax; ++g)
		{
			for (b = box->bmin; b <= box->bmax; ++b)
			{
				if (glp16to8)
				{
					i = (b) | (g << IN_DEPTH)
						| (r << (IN_DEPTH*2));
					glp16to8[i] = (BYTE)palIndex;
				}
	
				f = hist(r,g,b);
				if (f == 0L)
					continue;

				Rval += f * (long) r;
				Gval += f * (long) g;
				Bval += f * (long) b;

				total += f;
			}
		}
	}

	/* Bias the sum so that we round up at .5 */
	Rval += total / 2;
	Gval += total / 2;
	Bval += total / 2;

	return RGB(Rval*255/total/IN_SIZE, Gval*255/total/IN_SIZE, Bval*255/total/IN_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
//  write this stuff in ASM!
//
///////////////////////////////////////////////////////////////////////////////

void Histogram24(
	BYTE *pb,
	int dx,
	int dy,
	WORD WidthBytes,
	LPHISTOGRAM lpHistogram)
{
	int x,y;
	BYTE r,g,b;
	WORD w;

	UseHistogram(lpHistogram);

	WidthBytes -= (WORD) (dx*3);
	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			b = *pb++;
			g = *pb++;
			r = *pb++;
			w = (WORD) RGB16(r,g,b);
			IncHistogram(w);
		}
		pb += WidthBytes;
	}
}

void Histogram16(
	BYTE *pb,
	int dx,
	int dy,
	WORD WidthBytes,
	LPHISTOGRAM lpHistogram)
{
	int x,y;
	WORD w;

	UseHistogram(lpHistogram);

	WidthBytes -= (WORD)(dx*2);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			w = *((WORD *)pb)++;
			w &= 0x7FFF;
			IncHistogram(w);
		}
		pb += WidthBytes;
	}
}

void Histogram8(
	BYTE *pb,
	int dx,
	int dy,
	WORD WidthBytes,
	LPHISTOGRAM lpHistogram,
	LPWORD lpColors)
{
	int x,y;
	WORD w;

	UseHistogram(lpHistogram);

	WidthBytes -= (WORD)dx;

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			w = lpColors[*pb++];
			IncHistogram(w);
		}
		pb += WidthBytes;
	}
}

void Histogram4(
	BYTE *pb,
	int dx,
	int dy,
	WORD WidthBytes,
	LPHISTOGRAM lpHistogram,
	LPWORD lpColors)
{
	int x,y;
	BYTE b;
	WORD w;

	UseHistogram(lpHistogram);

	WidthBytes -= (WORD)((dx+1)/2);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<(dx+1)/2; x++)
		{
			b = *pb++;

			w = lpColors[b>>4];
			IncHistogram(w);

			w = lpColors[b&0x0F];
			IncHistogram(w);
		}
		pb += WidthBytes;
	}
}

void Histogram1(
	BYTE *pb,
	int dx,
	int dy,
	WORD WidthBytes,
	LPHISTOGRAM lpHistogram,
	LPWORD lpColors)
{
	int x,y,i;
	BYTE b;
	WORD w;

	UseHistogram(lpHistogram);

	WidthBytes -= (WORD)((dx+7)/8);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<(dx+7)/8; x++)
		{
			b = *pb++;

			for (i=0; i<8; i++)
			{
				w = lpColors[b>>7];
				IncHistogram(w);
				b<<=1;
			}
		}
		pb += WidthBytes;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//  write this stuff in ASM! too
//
///////////////////////////////////////////////////////////////////////////////

void Reduce24(
	BYTE *pbIn,
	int dx,
	int dy,
	WORD cbIn,
	BYTE *pbOut,
	WORD cbOut,
	LPBYTE lp16to8)
{
	int x,y;
	BYTE r,g,b;

	cbOut	-= (WORD)dx;
	cbIn	-= (WORD)(dx*3);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			b = *pbIn++;
			g = *pbIn++;
			r = *pbIn++;
			*pbOut++ = lp16to8[RGB16(r,g,b)];
		}
		pbIn += cbIn;
		pbOut+= cbOut;
	}
}

void Reduce16(
	BYTE *pbIn,
	int dx,
	int dy,
	WORD cbIn,
	BYTE *pbOut,
	WORD cbOut,
	LPBYTE lp16to8)
{
	int x,y;
	WORD w;

	cbOut	-= (WORD)dx;
	cbIn	-= (WORD)(dx*2);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			w = *((WORD *)pbIn)++;
			*pbOut++ = lp16to8[w&0x7FFF];
		}
		pbIn += cbIn;
		pbOut+= cbOut;
	}
}

void Reduce8(
	BYTE *pbIn,
	int dx,
	int dy,
	WORD cbIn,
	BYTE *pbOut,
	WORD cbOut,
	LPBYTE lp8to8)
{
	int x,y;

	cbIn	-= (WORD)dx;
	cbOut	-= (WORD)dx;

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			*pbOut++ = lp8to8[*pbIn++];
		}
		pbIn	+= cbIn;
		pbOut	+= cbOut;
	}
}

void Reduce4(
	BYTE *pbIn,
	int dx,
	int dy,
	WORD cbIn,
	BYTE *pbOut,
	WORD cbOut,
	LPBYTE lp8to8)
{
	int x,y;
	BYTE b;

	cbIn	-= (WORD)((dx+1)/2);
	cbOut	-= (WORD)((dx+1)&~1);

	for (y=0; y<dy; y++)
	{
		for (x=0; x<(dx+1)/2; x++)
		{
			b = *pbIn++;
			*pbOut++ = lp8to8[b>>4];
			*pbOut++ = lp8to8[b&0x0F];
		}
		pbIn	+= cbIn;
		pbOut	+= cbOut;
	}
}

void Reduce1(
	BYTE *pbIn,
	int dx,
	int dy,
	WORD cbIn,
	BYTE *pbOut,
	WORD cbOut,
	LPBYTE lp8to8)
{
	int x,y;
	BYTE b;

	cbIn	-= (WORD)((dx+7)/8);
	cbOut	-= (WORD)dx;

	for (y=0; y<dy; y++)
	{
		for (x=0; x<dx; x++)
		{
			if (x%8 == 0)
				b = *pbIn++;

			*pbOut++ = lp8to8[b>>7];
			b<<=1;
		}
		pbIn	+= cbIn;
		pbOut	+= cbOut;
	}
}
