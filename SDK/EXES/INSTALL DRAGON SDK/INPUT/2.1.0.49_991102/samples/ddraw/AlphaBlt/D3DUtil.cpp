/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    D3DUtil.cpp

Abstract:

   This file contains Direct3D functionality for the AlphaBlt sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#define D3D_OVERLOADS
#include "AlphaBlt.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVIEWPORT2 g_pviewport;              // Main Direct3D viewport
LPDIRECT3DMATERIAL2 g_pmatWhite;              // Global white material
LPDIRECT3DMATERIAL2 g_pmatBlack;              // Global black material
D3DMATERIALHANDLE   g_hmatWhite;              // Global white material handle
D3DMATERIALHANDLE   g_hmatBlack;              // Global black material handle
LPDIRECT3DDEVICE2   g_p3ddevice;              // Main Direct3D Device
LPDIRECT3DLIGHT     g_rglight[MAX_LIGHTS];    // Global D3D lights.
LPDIRECT3D2         g_pd3d;                   // Direct3D object
D3DMATRIX           g_matIdent   (1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f);
int                 g_cLights = 0;

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

// Variables for setting up the world, view, and projection matrices.  Arbitrarily
// generic values.
static D3DVECTOR g_vectUp  (0.0f, 1.0f, 0.0f);
static D3DVECTOR g_vectFrom(4.0f, 4.0f, 4.0f);
static D3DVECTOR g_vectAt  (0.0f, 0.0f, 0.0f);
static float     g_rNear   = 0.0f;
static float     g_rFar    = 100000.0f;
static float     g_rAspect = 480.0f / 640.0f;
static float     g_rFov    = PI/4.0f;

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL SetInitialState();
static BOOL InitViewport();

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirect3D

Description:

    Initializes the Direct3D object

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
InitDirect3D()
{
    // First, get the D3D Object itself (g_pd3d)
    g_errLast = g_pdd->QueryInterface(IID_IDirect3D2, (LPVOID*)&g_pd3d);
    if (CheckError(TEXT("Creation of IDirect3D")))
        return FALSE;
    
    // On the desktop we would create a Z buffer here, before creating the device,
    // but Z buffers do not exist on the DreamCast.
    
    // Create the D3D Device
    g_errLast = g_pd3d->CreateDevice(IID_IDirect3DHALDevice,  g_pddsBack, &g_p3ddevice);
    if (CheckError(TEXT("Create device")))
        return FALSE;

    // Create the D3D viewport object
    g_errLast = g_pd3d->CreateViewport(&g_pviewport, NULL);
    if (CheckError(TEXT("Create viewport")))
        return FALSE;

    // Add the viewport to the D3D device
    g_errLast = g_p3ddevice->AddViewport(g_pviewport);
    if (CheckError(TEXT("Add viewport")))
        return FALSE;

    // Create the global materials
    g_pmatWhite = CreateMaterial(1.0f, 1.0f, 1.0f, 1.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    g_pmatBlack = CreateMaterial(0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    
    // Get a handle to the materials for later use
    g_errLast = g_pmatWhite->GetHandle(g_p3ddevice, &g_hmatWhite);
    if (CheckError(TEXT("Get White material handle")))
        return NULL;

    g_errLast = g_pmatBlack->GetHandle(g_p3ddevice, &g_hmatBlack);
    if (CheckError(TEXT("Get Black material handle")))
        return NULL;

    // Set the viewport's background material (This is necessary for the Viewport->Clear that occurs elsewhere).
    g_errLast = g_pviewport->SetBackground(g_hmatBlack);
    if (CheckError(TEXT("Set Background Material")))
        return FALSE;

    // Set the viewport
    if (!InitViewport())
        return FALSE;

    // Set the default global rendering state
    if (!SetInitialState())
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitViewport

Description:

    Initializes the Direct3D viewport to standard setup.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
static BOOL 
InitViewport()
{
    D3DVIEWPORT2 viewData;   // Viewport Data Structure to fill

    // Fill the D3DVIEWPORT data structure
    memset(&viewData, 0, sizeof(D3DVIEWPORT2));
    viewData.dwSize   = sizeof(D3DVIEWPORT2);
    viewData.dwX      = viewData.dwY = 0;
    viewData.dwWidth  = 640;
    viewData.dwHeight = 480;

    viewData.dvClipWidth  = 2.0F;
    viewData.dvClipHeight = 2.0F;

    viewData.dvClipX = -1.0F;
    viewData.dvClipY = 1.0F;

    viewData.dvMaxZ = 1.0F;
    viewData.dvMinZ = 0.0F;

    // Now, set the global Direct3D viewport's data
    g_errLast = g_pviewport->SetViewport2(&viewData);
    if (CheckError(TEXT("Set Viewport")))
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateMaterial

Description:

    Creates a material.

Arguments:

    float rRed   - Red value
    float rGreen - Green value
    float rBlue  - Blue value
    float rAlpha - Alpha value
    float rPower - Material power
    float rSpecR - Specular Red
    float rSpecG - Specular Green
    float rSpecB - Specular Blue
    float rEmisR - Emissive Red (Ambient)
    float rEmisB - Emissive Green (Ambient)
    float rEmisG - Emissve Blue (Ambient)

Return Value:

    Pointer to the created material.

-------------------------------------------------------------------*/
LPDIRECT3DMATERIAL2 
CreateMaterial(float rRed,   float rGreen, float rBlue, float rAlpha, float rPower, 
               float rSpecR, float rSpecG, float rSpecB, 
               float rEmisR, float rEmisG, float rEmisB)
{
    D3DMATERIAL         mat;        // Holds Material Information
    LPDIRECT3DMATERIAL2 pmat;       // Points to created material

    // Create the material
    g_errLast = g_pd3d->CreateMaterial(&pmat, NULL);
    if (CheckError(TEXT("Creation of Material")))
        return NULL;

    // Initialize the Material
    memset(&mat, 0, sizeof(D3DMATERIAL));
    mat.dwSize     = sizeof(D3DMATERIAL);
    mat.diffuse.r  = rRed;
    mat.diffuse.g  = rGreen;
    mat.diffuse.b  = rBlue;
    mat.diffuse.a  = rAlpha;
    mat.ambient.r  = rEmisR;
    mat.ambient.g  = rEmisG;
    mat.ambient.b  = rEmisB;
    mat.ambient.a  = 1.0f;
    mat.specular.r = rSpecR;
    mat.specular.g = rSpecG;
    mat.specular.b = rSpecB;
    mat.power      = rPower;
    mat.hTexture   = NULL;
    // Don't need to set mat.dwRampSize since Dreamcast is RGB-only.

    // Set the material's data
    g_errLast = pmat->SetMaterial(&mat);
    if (CheckError(TEXT("Set material data")))
        return NULL;

    return pmat;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AddLight

Description:

    Creates and adds a light to the global viewport

Arguments:

    float rRed   - Red value
    float rGreen - Green value
    float rBlue  - Blue value
    float rX     - X Direction of the light
    float rY     - Y Direction of the light
    float rZ     - Z Direction of the light

Return Value:

    Pointer to the created material.

-------------------------------------------------------------------*/
BOOL
AddLight(float rRed, float rGreen, float rBlue, float rX, float rY, float rZ)
{
    D3DLIGHT light;

    memset(&light, 0, sizeof(D3DLIGHT));
    light.dwSize        = sizeof(D3DLIGHT);

    light.dltType       = D3DLIGHT_DIRECTIONAL;
    light.dcvColor.r    = rRed;
    light.dcvColor.g    = rGreen;
    light.dcvColor.b    = rBlue;
    light.dcvColor.a    = 1.0f;
    light.dvDirection.x = rX;
    light.dvDirection.y = rY;
    light.dvDirection.z = rZ;

    // Create the global light
    g_errLast = g_pd3d->CreateLight(&g_rglight[g_cLights], NULL);
    if (CheckError(TEXT("Create Light")))
        return FALSE;
    
    // Set the global light's information
    g_errLast = g_rglight[g_cLights]->SetLight(&light);
    if (CheckError(TEXT("Set Light")))
        return FALSE;

    // Add the global light to the global viewport
    g_errLast = g_pviewport->AddLight(g_rglight[g_cLights]);
    if (CheckError(TEXT("Add Light")))
        return FALSE;

    g_cLights++;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetInitialState

Description:

    Sets the default render state and sets up the matrices.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
static BOOL 
SetInitialState()
{
    D3DMATRIX matWorld;  // World Matrix
    D3DMATRIX matView;   // View Matrix
    D3DMATRIX matProj;   // Projection Matrix

    g_errLast = g_p3ddevice->BeginScene();
    if (CheckError(TEXT("Begin Scene")))
        return FALSE;

    // Enable Writing to the Z buffer
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
    if (CheckError(TEXT("Set Z Write Enable to TRUE")))
        return FALSE;

    // Set the Z comparison function
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
    if (CheckError(TEXT("Set Z Function to D3DCMP_LESS")))
        return FALSE;

    // Enable Z Buffering
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
    if (CheckError(TEXT("Set ZEnable to TRUE")))
        return FALSE;

    // Set the shade mode to Gouraud
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
    if (CheckError(TEXT("Set shade mode to D3DSHADE_GOURAUD")))
        return FALSE;

    // Set the global ambient light level
    g_errLast = g_p3ddevice->SetLightState(D3DLIGHTSTATE_AMBIENT, RGBA_MAKE(64, 64, 64, 255));
    if (CheckError(TEXT("Set Ambient Light")))
        return FALSE;

    // Turn on Perspective Texture Mapping
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
    if (CheckError(TEXT("Set Texture Perspective to TRUE")))
        return FALSE;

    // Disable specular lights
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,    FALSE);

    // No antialiasing
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS,         FALSE);

    // No alphablending
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,  FALSE);

    // Modulate texture with material
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,   D3DTBLEND_MODULATE);

    // Bilinear interpolation
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN,        D3DFILTER_NEAREST);
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG,        D3DFILTER_NEAREST);

    // Set default material.
    g_p3ddevice->SetLightState (D3DLIGHTSTATE_MATERIAL,           g_hmatWhite);

    // Set the World, View, and Projection matrices
    matWorld = g_matIdent;
    SetViewMatrix(&matView, &g_vectFrom, &g_vectAt, &g_vectUp);
    SetProjectionMatrix(&matProj, g_rNear, g_rFar, g_rFov, g_rAspect);

    // Set D3DIM's Projection matrix
    g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);
    if (CheckError(TEXT("Set Projection Matrix")))
        return FALSE;

    // Set D3DIM's World matrix
    g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
    if (CheckError(TEXT("Set World Matrix")))
        return FALSE;
    
    // Set D3DIM's View matrix
    g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
    if (CheckError(TEXT("Set View Matrix")))
        return FALSE;

    // Set the current viewport to be to global one created elsewhere
    g_errLast = g_p3ddevice->SetCurrentViewport(g_pviewport);
    if (CheckError(TEXT("Set Current Viewport")))
        return FALSE;

    g_errLast = g_p3ddevice->EndScene();
    if (CheckError(TEXT("End Scene")))
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetProjectionMatrix

Description:

    Set a projection matrix with the given
    near and far clipping planes in viewing units
    the fov angle in RADIANS
    and aspect ratio

    Destroys the current contents of the destination matrix.

Arguments:

    LPD3DMATRIX pmatxDest   -   Matrix to receive projection matrix

    float  rNear            -  Distance to near clipping plane

    float  rFar             -  Distance to far clipping plane

    float  rFov             -  whole field of view angle in radians

    float  rAspect          -  The aspect ratio Y/X of the viewing plane

Return Value:

    None

-------------------------------------------------------------------*/
void
SetProjectionMatrix(LPD3DMATRIX pmatxDest, float rNear, float rFar, 
                       float rFov, float rAspect)
{
    float rTfov = (float)(tan(rFov/2.0f));
    float rFFN  = rFar / (rFar - rNear);

    pmatxDest->_11 = 1.0f;
    pmatxDest->_12 = 0.0f;
    pmatxDest->_13 = 0.0f;
    pmatxDest->_14 = 0.0f;

    pmatxDest->_21 = 0.0f;
    pmatxDest->_22 = 1.0f/rAspect;
    pmatxDest->_23 = 0.0f;
    pmatxDest->_24 = 0.0f;

    pmatxDest->_31 = 0.0f;
    pmatxDest->_32 = 0.0f;
    pmatxDest->_33 = rTfov * rFFN;
    pmatxDest->_34 = rTfov;

    pmatxDest->_41 = 0.0f;
    pmatxDest->_42 = 0.0f;
    pmatxDest->_43 = -rNear * rTfov * rFFN;
    pmatxDest->_44 = 0.0f;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    NormalizeVector

Description:

    Normalizes the vector v to unit length.
    If the vector is degenerate nothing is done

Arguments:

    pvect -  Vector to normalize

Return Value:

    None

-------------------------------------------------------------------*/
void
NormalizeVector(LPD3DVECTOR pvect)
{
    float vx, vy, vz, rInvMod;

    vx = pvect->x;
    vy = pvect->y;
    vz = pvect->z;

    if ((vx != 0.0f) || (vy != 0.0f) || (vz != 0.0f)) 
    {
        rInvMod = (float)(1.0f / sqrt(vx * vx + vy * vy + vz * vz));
        pvect->x = vx * rInvMod;
        pvect->y = vy * rInvMod;
        pvect->z = vz * rInvMod;
    }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    VectorCrossProduct

Description:

    Calculates cross product of vectors 1 and 2.  vectDest = vect1 x vect2

Arguments:

    pvectDest -  Pointer to vector to receive result

    pvect1    -  Pointer to vector 1

    pvect2    -  Pointer to vector 2

Return Value:

    Pointer to result - pD

-------------------------------------------------------------------*/
void
VectorCrossProduct(LPD3DVECTOR pvectDest, LPD3DVECTOR pvect1, LPD3DVECTOR pvect2)
{
    pvectDest->x = pvect1->y * pvect2->z - pvect1->z * pvect2->y;
    pvectDest->y = pvect1->z * pvect2->x - pvect1->x * pvect2->z;
    pvectDest->z = pvect1->x * pvect2->y - pvect1->y * pvect2->x;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetMatrixRotation

Description:

    Set the rotation part of a matrix such that the vector pvectDir is the new
    z-axis and pvectUp is the new y-axis.
    NOTE:  The function only modifies the upper left 3x3 of the matrix.  Row 4 and column 4 are untouched.

Arguments:

    pmatxDest - Pointer to matrix to be modified.

    pvectDir - Pointer to a vector defining the Z-axis (Direction)

    pvectUp - Pointer to a vector defining the Y- Axis (Up)

Return Value:

   None

-------------------------------------------------------------------*/
void
SetMatrixRotation(LPD3DMATRIX pmatxDest, LPD3DVECTOR pvectDir, LPD3DVECTOR pvectUp)
{
    float t;
    D3DVECTOR d, u, r;

    // Normalize the direction vector.
    d.x = pvectDir->x;
    d.y = pvectDir->y;
    d.z = pvectDir->z;
    NormalizeVector(&d);

    u.x = pvectUp->x;
    u.y = pvectUp->y;
    u.z = pvectUp->z;

    // Project u into the plane defined by d and normalize.
    t = u.x * d.x + u.y * d.y + u.z * d.z;
    u.x -= d.x * t;
    u.y -= d.y * t;
    u.z -= d.z * t;
    NormalizeVector(&u);

    // Calculate the vector pointing along the matrix x axis (in a right
    // handed coordinate system) using cross product.
    VectorCrossProduct(&r, &u, &d);

    pmatxDest->_11 = r.x;
    pmatxDest->_12 = r.y;
    pmatxDest->_13 = r.z;

    pmatxDest->_21 = u.x;
    pmatxDest->_22 = u.y;
    pmatxDest->_23 = u.z;

    pmatxDest->_31 = d.x;
    pmatxDest->_32 = d.y;
    pmatxDest->_33 = d.z;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SubtractVectors

Description:

    Subtracts point 1 from point 1 giving Vector V.

    NOTE:  Points and vectors should be different types because they are mathematically distinct
           but D3D does not have that concept so D3DVECTOR is used to represent points.

Arguments:

   LPD3DVECTOR pvectDest  -  vector to reseive result

   LPD3DVECTOR  pvectSrc1  - vector representing point 1.

   LPD3DVECTOR  pvectSrc2  - vector representing point 2.

Return Value:

   None

-------------------------------------------------------------------*/
void
SubtractVectors(LPD3DVECTOR pvectDest, LPD3DVECTOR pvectSrc1, LPD3DVECTOR pvectSrc2)
{
    pvectDest->x = pvectSrc1->x - pvectSrc2->x;
    pvectDest->y = pvectSrc1->y - pvectSrc2->y;
    pvectDest->z = pvectSrc1->z - pvectSrc2->z;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    TransposeMatrix

Description:

   Transposes a matrix.  Transpose is equivalent to Inverse for pure
   rotation matrices.

Arguments:

  LPD3DMATRIX pmatxDest  - Destination matrix

  LPD3DMATRIX pmatxSrc   - Source matrix

Return Value:

   None

-------------------------------------------------------------------*/
void
TransposeMatrix(LPD3DMATRIX pmatxDest, LPD3DMATRIX pmatxSrc)
{
    D3DMATRIX matxTemp;

    matxTemp._11 = pmatxSrc->_11;
    matxTemp._12 = pmatxSrc->_21;
    matxTemp._13 = pmatxSrc->_31;
    matxTemp._14 = pmatxSrc->_41;

    matxTemp._21 = pmatxSrc->_12;
    matxTemp._22 = pmatxSrc->_22;
    matxTemp._23 = pmatxSrc->_32;
    matxTemp._24 = pmatxSrc->_42;

    matxTemp._31 = pmatxSrc->_13;
    matxTemp._32 = pmatxSrc->_23;
    matxTemp._33 = pmatxSrc->_33;
    matxTemp._34 = pmatxSrc->_43;

    matxTemp._41 = pmatxSrc->_14;
    matxTemp._42 = pmatxSrc->_24;
    matxTemp._43 = pmatxSrc->_34;
    matxTemp._44 = pmatxSrc->_44;

    *pmatxDest = matxTemp;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetViewMatrix

Description:

    Sets the viewing matrix such that
    from is at the origin
    at   is on the positive Z axis
    up   is in the Y-Z plane

Arguments:

   LPD3DMATRIX pmatxDest   -  Pointer to matrix to receive view matrix

   LPD3DVECTOR pvectFrom   -  Location of the eye

   LPD3DVECTOR pvectAt     -  Point looked at

   LPD3DVECTOR pvectUp     -  Vector describing the up direction.  Cannot be parallel to (At - From)

Return Value:

   None

-------------------------------------------------------------------*/
void
SetViewMatrix(LPD3DMATRIX pmatxDest, LPD3DVECTOR pvectFrom, LPD3DVECTOR pvectAt, LPD3DVECTOR pvectUp)
{
    D3DVECTOR los;              // Line of sight

    SubtractVectors(&los, pvectAt, pvectFrom);

    // Generate the rotation part of the matrix
    SetMatrixRotation(pmatxDest, &los, pvectUp);

    // Make sure the matrix is completely initialized
    pmatxDest->_14 = 0.0f;
    pmatxDest->_24 = 0.0f;
    pmatxDest->_34 = 0.0f;
    pmatxDest->_41 = 0.0f;
    pmatxDest->_42 = 0.0f;
    pmatxDest->_43 = 0.0f;
    pmatxDest->_44 = 1.0f;

    TransposeMatrix(pmatxDest, pmatxDest);

    // Preconcatenate translational component
    pmatxDest->_41 = -(pvectFrom->x * pmatxDest->_11 + pvectFrom->y * pmatxDest->_21 + pvectFrom->z * pmatxDest->_31);
    pmatxDest->_42 = -(pvectFrom->x * pmatxDest->_12 + pvectFrom->y * pmatxDest->_22 + pvectFrom->z * pmatxDest->_32);
    pmatxDest->_43 = -(pvectFrom->x * pmatxDest->_13 + pvectFrom->y * pmatxDest->_23 + pvectFrom->z * pmatxDest->_33);
}
