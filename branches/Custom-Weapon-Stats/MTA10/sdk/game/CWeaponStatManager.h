/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        sdk/game/CWaterManager.h
*  PURPOSE:     Water interface
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CWEAPONSTATMANAGER_H
#define __CWEAPONSTATMANAGER_H
#include "CWeaponStat.h"

class CWeaponStatManager
{
public:
    virtual CWeaponStat*                GetWeaponStats                  ( eWeaponType type, eWeaponSkill skill = WEAPONSKILL_STD ) = 0;
    virtual CWeaponStat*                GetOriginalWeaponStats          ( eWeaponType type, eWeaponSkill skill = WEAPONSKILL_STD ) = 0;
    virtual void                        Init                            ( void ) = 0;
    virtual bool                        LoadDefault                     ( CWeaponStat* pDest, eWeaponType weaponType ) = 0;
    virtual void                        CreateWeaponStat                ( CWeaponInfo* pInterface, eWeaponType weaponType, eWeaponSkill weaponSkill ) = 0;

};

#endif
