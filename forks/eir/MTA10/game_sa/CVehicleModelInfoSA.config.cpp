/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.2
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CVehicleModelInfoSA.config.cpp
*  PURPOSE:     Vehicle model resource and configuration management
*  DEVELOPERS:  Martin Turski <quiret@gmx.de>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include <StdInc.h>

#define FUNC_InitVehicleData                0x005B8F00
#define FUNC_LoadVehicleColors              0x005B6890
#define FUNC_LoadCarMods                    0x005B65A0
#define FUNC_LoadVehicleParticles           0x004C8780

// TexDictionary used in vehicle clump loading
RwTexDictionary *g_vehicleTxd = NULL;

/*=========================================================
    _VehicleModels_Init

    Purpose:
        Initializes data used by vehicle models. g_vehicleTxd
        contains common textures used by vehicle models. It is
        being set during loading in CStreamingSA.
    Binary offsets:
        (1.0 US and 1.0 EU): 0x005B8F00
    Note:
        There are functions left to rewrite into native C++ code.
        I have left out the calls to UpdateLoadingBar, since MTA
        does not use that anymore.
=========================================================*/
static void __cdecl _VehicleModels_Init( void )
{
    __asm
    {
        mov eax,FUNC_LoadVehicleColors
        call eax
        mov eax,FUNC_LoadCarMods
        call eax
        mov eax,FUNC_LoadVehicleParticles
        call eax
    }

    // Load the generic vehicle textures
    CTxdInstanceSA *txdEntry = (*ppTxdPool)->Get( pGame->GetTextureManager()->FindTxdEntry( "vehicle" ) );

    if ( txdEntry )
    {
        CFile *file = OpenGlobalStream( "MODELS\\GENERIC\\VEHICLE.TXD", "rb" );

        txdEntry->LoadTXD( file );

        delete file;
    }
    else
        txdEntry = (*ppTxdPool)->Get( pGame->GetTextureManager()->LoadDictionaryEx( "vehicle", "MODELS\\GENERIC\\VEHICLE.TXD" ) );

    if ( txdEntry )
    {
        // Reference it
        txdEntry->Reference();

        g_vehicleTxd = txdEntry->m_txd;
    }

    *(RwTexture**)0x00B4E68C = g_vehicleTxd->FindNamedTexture( "vehiclelights128" );
    *(RwTexture**)0x00B4E690 = g_vehicleTxd->FindNamedTexture( "vehiclelightson128" );

    // Allocate the component info pool
    *ppVehicleComponentInfoPool = new CVehicleComponentInfoPool;

    __asm
    {
        mov ecx,0x005D5BC0
        call ecx
    }
}

void    VehicleModels_Init( void )
{
    // We should be initializing the data ourselves
    HookInstall( FUNC_InitVehicleData, (DWORD)_VehicleModels_Init, 5 );

    VehicleModelInfoRender_Init();

    // Debug
    HookInstall( 0x004C8E60, h_memFunc( &CVehicleModelInfoSAInterface::Setup ), 5 );

    // Temporary vehicle look-up fix (will not be needed anymore in future patch)
    HookInstall( 0x004C75A0, (DWORD)RwRemapScan::Apply, 5 );
    HookInstall( 0x004C75C0, (DWORD)RwRemapScan::Unapply, 5 );
}

void    VehicleModels_Shutdown( void )
{
    VehicleModelInfoRender_Shutdown();
}