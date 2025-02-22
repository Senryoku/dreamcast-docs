/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDUtil.cpp

Abstract:

   This file contains DirectDraw functionality for the bumpmapping sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "bumpmapping.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTDRAW4        g_pdd;          // The DirectDraw object
LPDIRECTDRAWSURFACE4 g_pddsPrimary;  // Primary DirectDraw surface
LPDIRECTDRAWSURFACE4 g_pddsBack;     // Backbuffer DirectDraw surface

// ++++ Local functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL CreateDirectDrawDevice();

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirectDraw

Description:

    Initializes the DirectDraw object and its surfaces.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
InitDirectDraw()
{
    DDSURFACEDESC2 ddsd;         // DirectDraw Surface Descriptor

    // Find and create the proper DDraw device for our purposes.
    if (!CreateDirectDrawDevice())
    {
        g_errLast = -1;
        CheckError(TEXT("Create Direct Draw Device"));
        return FALSE;
    }

    // Get exclusive mode.  Full-screen mode requires 'DDSCL_EXCLUSIVE'.
    g_errLast = g_pdd->SetCooperativeLevel(g_hwndApp, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (CheckError(TEXT("Setting of Cooperative Level")))
        return FALSE;

    // Set Display Mode
    g_errLast = g_pdd->SetDisplayMode(640, 480, 16, 0, 0);
    if (CheckError(TEXT("Setting of Display Mode")))
        return FALSE;

    // Setup to create the primary surface with 1 back buffer
    ddsd.dwSize            = sizeof(ddsd);
    ddsd.dwFlags           = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
    ddsd.ddsCaps.dwCaps2 = 0;
    ddsd.dwBackBufferCount = 1;

    // Create the primary surface
    g_errLast = g_pdd->CreateSurface(&ddsd, &g_pddsPrimary, NULL);
    if (CheckError(TEXT("Creation of Primary DirectDraw Surface")))
        return FALSE;

    // Get a pointer to the back buffer
    ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
    g_errLast = g_pddsPrimary->GetAttachedSurface(&ddsd.ddsCaps, &g_pddsBack);
    if (CheckError(TEXT("Obtaining of Back Buffer pointer")))
        return FALSE;

    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateDirectDrawDevice

Description:

    There is only one device on Dragon - create it using the NULL
    GUID and return.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
static BOOL
CreateDirectDrawDevice()
{
    IDirectDraw *pddTemp;

    g_errLast = DirectDrawCreate(NULL, &pddTemp, NULL);
    if (CheckError(TEXT("Creation of DirectDraw Object")))
        return FALSE;

    // Get an IDirectDraw4 interface 
    g_errLast = pddTemp->QueryInterface(IID_IDirectDraw4, (LPVOID *)&g_pdd); 
    if (CheckError(TEXT("QueryInterface for IDirectDraw4 interface")))
        return FALSE;

    // We no longer need the older DirectDraw interface, so release it
    pddTemp->Release();

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FlipBuffers

Description:

    If 'USE_WINDOW' is defined, then Blt the back buffer to the front.
    If 'USE_WINDOW' is not defined, then flip the back and front buffers.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
FlipBuffers()
{

    // Flip the Back Buffer to the Front Buffer
    g_errLast = g_pddsPrimary->Flip(NULL, DDFLIP_WAIT);
    CheckError(TEXT("Flipping of Buffers"));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetSurfaceDesc

Description:

    Gets the surface information for the passed-in surface

Arguments:

    LPDDSURFACEDESC2     pddsurfdesc   - Structure filled with information

    LPDIRECTDRAWSURFACE4 pddsurf       - Surface to get the information from.
 
Return Value:

    HRESULT                           - Result of function

-------------------------------------------------------------------*/
HRESULT
GetSurfaceDesc(LPDDSURFACEDESC2 pddsurfdesc, LPDIRECTDRAWSURFACE4 pddsurf)
{
    memset(pddsurfdesc, 0, sizeof(DDSURFACEDESC2));
    pddsurfdesc->dwSize = sizeof(DDSURFACEDESC2);
    
    return pddsurf->GetSurfaceDesc(pddsurfdesc);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadBitmapToDDS

Description:

    Loads a bitmap from a file or resource, creates a new DirectDraw
    surface, and copies the bitmap to that surface.

Arguments:

    LPTSTR szBitmap     -   Name of the texture to load
 
Return Value:

    LPDIRECTDRAWSURFACE -   A pointer to the loaded texture

-------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE4
LoadBitmapToDDS(LPTSTR tszBitmap)
{
    HBITMAP              hbitmap;    // Bitmap handle
    BITMAP               bitmap;     // Bitmap information
    DDSURFACEDESC2       ddsd;       // Surface Descriptor
    LPDIRECTDRAWSURFACE4 pdds;       // Pointer to a DirectDraw surface
    HDC                  hdcBitmap;  // DC for bitmap
    HDC                  hdcSurface; // DC for DDraw surface

    // Try to Load the bitmap as a resource or a file
    hbitmap = (HBITMAP)LoadImage (g_hinst, tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    if (hbitmap== NULL)
    {
        // Failed to load the bitmap
        return NULL;
    }

    // Get the width, height and other info about the bitmap.
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // Create a DirectDrawSurface for this texture
    memset(&ddsd, 0, sizeof(ddsd));
    GetSurfaceDesc(&ddsd, g_pddsBack);  

    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    ddsd.dwWidth        = bitmap.bmWidth;
    ddsd.dwHeight       = bitmap.bmHeight;

	// we want RGBA5551 textures so we can alpha blend 

	ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0x8000;
	ddsd.ddpfPixelFormat.dwRBitMask = 0x7c00;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x03e0;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x001f;
	ddsd.ddpfPixelFormat.dwSize = sizeof(ddsd.ddpfPixelFormat);
	ddsd.ddpfPixelFormat.dwFlags = DDPF_ALPHAPIXELS | DDPF_RGB;


    g_errLast = g_pdd->CreateSurface(&ddsd, &pdds, NULL);
    if (CheckError(TEXT("Create DDTexture surface")))
        return NULL;

    // Create an offscreen DC, and load the bitmap into it.
    hdcBitmap = CreateCompatibleDC (NULL);
    SelectObject (hdcBitmap, hbitmap);

    // Get a DC onto the DDraw surface.
    g_errLast = pdds->GetDC (&hdcSurface);
    if (CheckError(TEXT("Get DDraw DC")))
        return NULL;

    // Copy the bits from the bitmap to the DDraw surface.
    BitBlt (hdcSurface, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCCOPY);
    // Clean up after ourselves.
    pdds->ReleaseDC (hdcSurface);
    DeleteDC (hdcBitmap);
    DeleteObject (hbitmap);


	// Transparent parts of the DX logo bitmap were set as pure white,
	// search for this, and clear the alpha bit...

	    // Lock the bits to the bumpmap fourcc surface
    pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    WORD *pwTex = (WORD*)ddsd.lpSurface;
	for( unsigned int y=0; y < ddsd.dwHeight; y++ )
	{
		for( unsigned int x=0; x < ddsd.dwWidth; x++ )
		{
			if( ( pwTex[x] & 0x7fff ) == 0x7fff )
				pwTex[x] = 0x0000;
			else
				pwTex[x] |= 0x8000;
		}
		pwTex += ddsd.lPitch / sizeof(WORD);
	}
    pdds->Unlock(NULL);


    return pdds;
}
