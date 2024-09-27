/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

 Copyright (C) 1996-1997 Id Software, Inc.
 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments)
 on EFR32MG24 and MGM240 port.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 */
// sbar.c -- status bar code
#include "quakedef.h"
#if !WIN32
#include "memory_defs.h"
#endif

int sb_updates;		// if >= vid.numpages, no update needed

#define STAT_MINUS		10	// num frame for '-' stats digit
#if SB_RAM_POINTERS
qpic_t		*sb_nums[2][11];


qpic_t      *sb_weapons[7][8];   // 0 is active, 1 is owned, 2-5 are flashes
qpic_t      *sb_ammo[4];
qpic_t		*sb_sigil[4];
qpic_t		*sb_armor[3];
qpic_t		*sb_items[32];

qpic_t	*sb_faces[7][2];		// 0 is gibbed, 1 is dead, 2-6 are alive
							// 0 is static, 1 is temporary animation
qpic_t	*sb_face_invis;
qpic_t	*sb_face_quad;
qpic_t	*sb_face_invuln;
qpic_t	*sb_face_invis_invuln;

qpic_t      *rsb_invbar[2];
qpic_t      *rsb_weapons[5];
qpic_t      *rsb_items[2];

//MED 01/04/97 added two more weapons + 3 alternates for grenade launcher
qpic_t      *hsb_weapons[7][5];   // 0 is active, 1 is owned, 2-5 are flashes

qpic_t      *rsb_ammo[3];
qpic_t      *rsb_teambord;		// PGM 01/19/97 - team color border
#else
#define sb_nums (*psb_nums)
#define sb_weapons (*psb_weapons)
#define sb_ammo (*psb_ammo)
#define sb_sigil (*psb_sigil)
#define sb_items (*psb_items)
#define sb_armor (*psb_armor)
#define sb_faces (*psb_faces)

#define rsb_invbar (*prsb_invbar)
#define rsb_weapons (*prsb_weapons)
#define rsb_items (*prsb_items)
#define rsb_ammo (*prsb_ammo)

#define hsb_weapons (*phsb_weapons)
#define hsb_items (*phsb_items)

qpic_t *(*psb_nums)[2][11];
qpic_t *(*psb_weapons)[7][8];   // 0 is active, 1 is owned, 2-5 are flashes
qpic_t *(*psb_ammo)[4];
qpic_t *(*psb_sigil)[4];
qpic_t *(*psb_armor)[3];
qpic_t *(*psb_items)[32];
qpic_t *(*psb_faces)[7][2];		// 0 is gibbed, 1 is dead, 2-6 are alive
// 0 is static, 1 is temporary animation
qpic_t *(*prsb_invbar)[2];
qpic_t *(*prsb_weapons)[5];
qpic_t *(*prsb_items)[2];
qpic_t *(*prsb_ammo)[3];
//MED 01/04/97 added two more weapons + 3 alternates for grenade launcher
qpic_t *(*phsb_weapons)[7][5];   // 0 is active, 1 is owned, 2-5 are flashes
//MED 01/04/97 added array to simplify weapon parsing
//MED 01/04/97 added hipnotic items array
qpic_t *(*phsb_items)[2];

#endif
qboolean sb_showscores;
int sb_lines;			// scan lines to draw

qpic_t *sb_colon, *sb_slash;
qpic_t *sb_ibar;
qpic_t *sb_sbar;
qpic_t *sb_scorebar;
qpic_t *sb_face_invis;
qpic_t *sb_face_quad;
qpic_t *sb_face_invuln;
qpic_t *sb_face_invis_invuln;
qpic_t *rsb_teambord;		// PGM 01/19/97 - team color border

//MED 01/04/97 added array to simplify weapon parsing
const byte hipweapons[4] =
{ HIT_LASER_CANNON_BIT, HIT_MJOLNIR_BIT, 4, HIT_PROXIMITY_GUN_BIT
};
//MED 01/04/97 added hipnotic items array

#if HAS_MULTIPLAYER
void Sbar_MiniDeathmatchOverlay (void);
#endif
void Sbar_DeathmatchOverlay(void);
void M_DrawPic(int x, int y, qpic_t *pic);

/*
 ===============
 Sbar_ShowScores

 Tab key down
 ===============
 */
void Sbar_ShowScores(void)
{
    if (sb_showscores)
        return;
    sb_showscores = true;
    sb_updates = 0;
}

/*
 ===============
 Sbar_DontShowScores

 Tab key up
 ===============
 */
void Sbar_DontShowScores(void)
{
    sb_showscores = false;
    sb_updates = 0;
}

/*
 ===============
 Sbar_Changed
 ===============
 */
void Sbar_Changed(void)
{
    sb_updates = 0;	// update next frame
}

/*
 ===============
 Sbar_Init
 ===============
 */
#define STORE_TO_FLASH(array)  p##array = storeToInternalFlash(stack_##array, sizeof(stack_##array))
void Sbar_Init(void)
{
    sb_colon = Draw_PicFromWad("num_colon");
    sb_slash = Draw_PicFromWad("num_slash");
    sb_face_invis = Draw_PicFromWad("face_invis");
    sb_face_invuln = Draw_PicFromWad("face_invul2");
    sb_face_invis_invuln = Draw_PicFromWad("face_inv2");
    sb_face_quad = Draw_PicFromWad("face_quad");
#if CACHE_STATUS_BAR_TO_FLASH_IF_POSSIBLE
#if !WIN32
    if ((uint32_t) __flashSize  <= 0xAC000)
    {
        printf("Caching Statusbar to flash!");
        sb_sbar = Draw_PicFromWad("sbar");
        uint8_t *addr = (uint8_t*) sb_sbar;
        qpic_t qpd;
        extMemGetDataFromAddress(&qpd, sb_sbar, sizeof(qpd));
        sb_sbar = storeToInternalFlash(&qpd, sizeof (qpd));
        addr += sizeof (qpd);
        storeToInternalFlash(addr, qpd.height * qpd.width);
    }
    else
#endif
    {
        printf("NOT caching Status bar to flash!");
        sb_sbar = Draw_PicFromWad("sbar");
    }
#else
    sb_sbar = Draw_PicFromWad("sbar");
#endif
    sb_ibar = Draw_PicFromWad("ibar");
    sb_scorebar = Draw_PicFromWad("scorebar");
//

    qpic_t *stack_sb_nums[2][11];
    qpic_t *stack_sb_weapons[7][8];   // 0 is active, 1 is owned, 2-5 are flashes
    qpic_t *stack_sb_ammo[4];
    qpic_t *stack_sb_sigil[4];
    qpic_t *stack_sb_armor[3];
    qpic_t *stack_sb_items[32];
    qpic_t *stack_sb_faces[7][2];		// 0 is gibbed, 1 is dead, 2-6 are alive
    // 0 is static, 1 is temporary animation
    qpic_t *stack_rsb_invbar[2];
    qpic_t *stack_rsb_weapons[5];
    qpic_t *stack_rsb_items[2];
    qpic_t *stack_rsb_ammo[3];
    //MED 01/04/97 added two more weapons + 3 alternates for grenade launcher
    qpic_t *stack_hsb_weapons[7][5];   // 0 is active, 1 is owned, 2-5 are flashes
    //MED 01/04/97 added array to simplify weapon parsing
    //MED 01/04/97 added hipnotic items array
    qpic_t *stack_hsb_items[2];

#if !SB_RAM_POINTERS
    int i;
    char vastr[64];
    for (i = 0; i < 10; i++)
    {
        stack_sb_nums[0][i] = Draw_PicFromWad(va(vastr, "num_%i", i));
        stack_sb_nums[1][i] = Draw_PicFromWad(va(vastr, "anum_%i", i));
    }
    stack_sb_nums[0][10] = Draw_PicFromWad("num_minus");
    stack_sb_nums[1][10] = Draw_PicFromWad("anum_minus");

    STORE_TO_FLASH(sb_nums);

    stack_sb_weapons[0][0] = Draw_PicFromWad("inv_shotgun");
    stack_sb_weapons[0][1] = Draw_PicFromWad("inv_sshotgun");
    stack_sb_weapons[0][2] = Draw_PicFromWad("inv_nailgun");
    stack_sb_weapons[0][3] = Draw_PicFromWad("inv_snailgun");
    stack_sb_weapons[0][4] = Draw_PicFromWad("inv_rlaunch");
    stack_sb_weapons[0][5] = Draw_PicFromWad("inv_srlaunch");
    stack_sb_weapons[0][6] = Draw_PicFromWad("inv_lightng");

    stack_sb_weapons[1][0] = Draw_PicFromWad("inv2_shotgun");
    stack_sb_weapons[1][1] = Draw_PicFromWad("inv2_sshotgun");
    stack_sb_weapons[1][2] = Draw_PicFromWad("inv2_nailgun");
    stack_sb_weapons[1][3] = Draw_PicFromWad("inv2_snailgun");
    stack_sb_weapons[1][4] = Draw_PicFromWad("inv2_rlaunch");
    stack_sb_weapons[1][5] = Draw_PicFromWad("inv2_srlaunch");
    stack_sb_weapons[1][6] = Draw_PicFromWad("inv2_lightng");

    for (i = 0; i < 5; i++)
    {
        stack_sb_weapons[2 + i][0] = Draw_PicFromWad(va(vastr, "inva%i_shotgun", i + 1));
        stack_sb_weapons[2 + i][1] = Draw_PicFromWad(va(vastr, "inva%i_sshotgun", i + 1));
        stack_sb_weapons[2 + i][2] = Draw_PicFromWad(va(vastr, "inva%i_nailgun", i + 1));
        stack_sb_weapons[2 + i][3] = Draw_PicFromWad(va(vastr, "inva%i_snailgun", i + 1));
        stack_sb_weapons[2 + i][4] = Draw_PicFromWad(va(vastr, "inva%i_rlaunch", i + 1));
        stack_sb_weapons[2 + i][5] = Draw_PicFromWad(va(vastr, "inva%i_srlaunch", i + 1));
        stack_sb_weapons[2 + i][6] = Draw_PicFromWad(va(vastr, "inva%i_lightng", i + 1));
    }
    STORE_TO_FLASH(sb_weapons);

    stack_sb_ammo[0] = Draw_PicFromWad("sb_shells");
    stack_sb_ammo[1] = Draw_PicFromWad("sb_nails");
    stack_sb_ammo[2] = Draw_PicFromWad("sb_rocket");
    stack_sb_ammo[3] = Draw_PicFromWad("sb_cells");

    STORE_TO_FLASH(sb_ammo);

    stack_sb_armor[0] = Draw_PicFromWad("sb_armor1");
    stack_sb_armor[1] = Draw_PicFromWad("sb_armor2");
    stack_sb_armor[2] = Draw_PicFromWad("sb_armor3");

    STORE_TO_FLASH(sb_armor);

    stack_sb_items[0] = Draw_PicFromWad("sb_key1");
    stack_sb_items[1] = Draw_PicFromWad("sb_key2");
    stack_sb_items[2] = Draw_PicFromWad("sb_invis");
    stack_sb_items[3] = Draw_PicFromWad("sb_invuln");
    stack_sb_items[4] = Draw_PicFromWad("sb_suit");
    stack_sb_items[5] = Draw_PicFromWad("sb_quad");

    STORE_TO_FLASH(sb_items);

    stack_sb_sigil[0] = Draw_PicFromWad("sb_sigil1");
    stack_sb_sigil[1] = Draw_PicFromWad("sb_sigil2");
    stack_sb_sigil[2] = Draw_PicFromWad("sb_sigil3");
    stack_sb_sigil[3] = Draw_PicFromWad("sb_sigil4");

    STORE_TO_FLASH(sb_sigil);

    stack_sb_faces[4][0] = Draw_PicFromWad("face1");
    stack_sb_faces[4][1] = Draw_PicFromWad("face_p1");
    stack_sb_faces[3][0] = Draw_PicFromWad("face2");
    stack_sb_faces[3][1] = Draw_PicFromWad("face_p2");
    stack_sb_faces[2][0] = Draw_PicFromWad("face3");
    stack_sb_faces[2][1] = Draw_PicFromWad("face_p3");
    stack_sb_faces[1][0] = Draw_PicFromWad("face4");
    stack_sb_faces[1][1] = Draw_PicFromWad("face_p4");
    stack_sb_faces[0][0] = Draw_PicFromWad("face5");
    stack_sb_faces[0][1] = Draw_PicFromWad("face_p5");

    STORE_TO_FLASH(sb_faces);

//MED 01/04/97 added new hipnotic weapons
    if (hipnotic)
    {
        stack_hsb_weapons[0][0] = Draw_PicFromWad("inv_laser");
        stack_hsb_weapons[0][1] = Draw_PicFromWad("inv_mjolnir");
        stack_hsb_weapons[0][2] = Draw_PicFromWad("inv_gren_prox");
        stack_hsb_weapons[0][3] = Draw_PicFromWad("inv_prox_gren");
        stack_hsb_weapons[0][4] = Draw_PicFromWad("inv_prox");

        stack_hsb_weapons[1][0] = Draw_PicFromWad("inv2_laser");
        stack_hsb_weapons[1][1] = Draw_PicFromWad("inv2_mjolnir");
        stack_hsb_weapons[1][2] = Draw_PicFromWad("inv2_gren_prox");
        stack_hsb_weapons[1][3] = Draw_PicFromWad("inv2_prox_gren");
        stack_hsb_weapons[1][4] = Draw_PicFromWad("inv2_prox");

        for (i = 0; i < 5; i++)
        {
            stack_hsb_weapons[2 + i][0] = Draw_PicFromWad(va(vastr, "inva%i_laser", i + 1));
            stack_hsb_weapons[2 + i][1] = Draw_PicFromWad(va(vastr, "inva%i_mjolnir", i + 1));
            stack_hsb_weapons[2 + i][2] = Draw_PicFromWad(va(vastr, "inva%i_gren_prox", i + 1));
            stack_hsb_weapons[2 + i][3] = Draw_PicFromWad(va(vastr, "inva%i_prox_gren", i + 1));
            stack_hsb_weapons[2 + i][4] = Draw_PicFromWad(va(vastr, "inva%i_prox", i + 1));
        }
        STORE_TO_FLASH(hsb_weapons);

        stack_hsb_items[0] = Draw_PicFromWad("sb_wsuit");
        stack_hsb_items[1] = Draw_PicFromWad("sb_eshld");
        STORE_TO_FLASH(hsb_items);

    }
    if (rogue)
    {
        stack_rsb_invbar[0] = Draw_PicFromWad("r_invbar1");
        stack_rsb_invbar[1] = Draw_PicFromWad("r_invbar2");

        STORE_TO_FLASH(rsb_invbar);

        stack_rsb_weapons[0] = Draw_PicFromWad("r_lava");
        stack_rsb_weapons[1] = Draw_PicFromWad("r_superlava");
        stack_rsb_weapons[2] = Draw_PicFromWad("r_gren");
        stack_rsb_weapons[3] = Draw_PicFromWad("r_multirock");
        stack_rsb_weapons[4] = Draw_PicFromWad("r_plasma");

        STORE_TO_FLASH(rsb_weapons);

        stack_rsb_items[0] = Draw_PicFromWad("r_shield1");
        stack_rsb_items[1] = Draw_PicFromWad("r_agrav1");

        STORE_TO_FLASH(rsb_items);

// PGM 01/19/97 - team color border
        rsb_teambord = Draw_PicFromWad("r_teambord");

// PGM 01/19/97 - team color border

        stack_rsb_ammo[0] = Draw_PicFromWad("r_ammolava");
        stack_rsb_ammo[1] = Draw_PicFromWad("r_ammomulti");
        stack_rsb_ammo[2] = Draw_PicFromWad("r_ammoplasma");
        STORE_TO_FLASH(rsb_ammo);

    }

#else
	int		i;
    char vastr[64];
	for (i=0 ; i<10 ; i++)
	{
		sb_nums[0][i] = Draw_PicFromWad (va(vastr, "num_%i",i));
		sb_nums[1][i] = Draw_PicFromWad (va(vastr, "anum_%i",i));
	}

	sb_nums[0][10] = Draw_PicFromWad ("num_minus");
	sb_nums[1][10] = Draw_PicFromWad ("anum_minus");

	sb_colon = Draw_PicFromWad ("num_colon");
	sb_slash = Draw_PicFromWad ("num_slash");

	sb_weapons[0][0] = Draw_PicFromWad ("inv_shotgun");
	sb_weapons[0][1] = Draw_PicFromWad ("inv_sshotgun");
	sb_weapons[0][2] = Draw_PicFromWad ("inv_nailgun");
	sb_weapons[0][3] = Draw_PicFromWad ("inv_snailgun");
	sb_weapons[0][4] = Draw_PicFromWad ("inv_rlaunch");
	sb_weapons[0][5] = Draw_PicFromWad ("inv_srlaunch");
	sb_weapons[0][6] = Draw_PicFromWad ("inv_lightng");

	sb_weapons[1][0] = Draw_PicFromWad ("inv2_shotgun");
	sb_weapons[1][1] = Draw_PicFromWad ("inv2_sshotgun");
	sb_weapons[1][2] = Draw_PicFromWad ("inv2_nailgun");
	sb_weapons[1][3] = Draw_PicFromWad ("inv2_snailgun");
	sb_weapons[1][4] = Draw_PicFromWad ("inv2_rlaunch");
	sb_weapons[1][5] = Draw_PicFromWad ("inv2_srlaunch");
	sb_weapons[1][6] = Draw_PicFromWad ("inv2_lightng");

	for (i=0 ; i<5 ; i++)
	{
		sb_weapons[2+i][0] = Draw_PicFromWad (va(vastr, "inva%i_shotgun",i+1));
		sb_weapons[2+i][1] = Draw_PicFromWad (va(vastr, "inva%i_sshotgun",i+1));
		sb_weapons[2+i][2] = Draw_PicFromWad (va(vastr, "inva%i_nailgun",i+1));
		sb_weapons[2+i][3] = Draw_PicFromWad (va(vastr, "inva%i_snailgun",i+1));
		sb_weapons[2+i][4] = Draw_PicFromWad (va(vastr, "inva%i_rlaunch",i+1));
		sb_weapons[2+i][5] = Draw_PicFromWad (va(vastr, "inva%i_srlaunch",i+1));
		sb_weapons[2+i][6] = Draw_PicFromWad (va(vastr, "inva%i_lightng",i+1));
	}

	sb_ammo[0] = Draw_PicFromWad ("sb_shells");
	sb_ammo[1] = Draw_PicFromWad ("sb_nails");
	sb_ammo[2] = Draw_PicFromWad ("sb_rocket");
	sb_ammo[3] = Draw_PicFromWad ("sb_cells");

	sb_armor[0] = Draw_PicFromWad ("sb_armor1");
	sb_armor[1] = Draw_PicFromWad ("sb_armor2");
	sb_armor[2] = Draw_PicFromWad ("sb_armor3");

	sb_items[0] = Draw_PicFromWad ("sb_key1");
	sb_items[1] = Draw_PicFromWad ("sb_key2");
	sb_items[2] = Draw_PicFromWad ("sb_invis");
	sb_items[3] = Draw_PicFromWad ("sb_invuln");
	sb_items[4] = Draw_PicFromWad ("sb_suit");
	sb_items[5] = Draw_PicFromWad ("sb_quad");

	sb_sigil[0] = Draw_PicFromWad ("sb_sigil1");
	sb_sigil[1] = Draw_PicFromWad ("sb_sigil2");
	sb_sigil[2] = Draw_PicFromWad ("sb_sigil3");
	sb_sigil[3] = Draw_PicFromWad ("sb_sigil4");

	sb_faces[4][0] = Draw_PicFromWad ("face1");
	sb_faces[4][1] = Draw_PicFromWad ("face_p1");
	sb_faces[3][0] = Draw_PicFromWad ("face2");
	sb_faces[3][1] = Draw_PicFromWad ("face_p2");
	sb_faces[2][0] = Draw_PicFromWad ("face3");
	sb_faces[2][1] = Draw_PicFromWad ("face_p3");
	sb_faces[1][0] = Draw_PicFromWad ("face4");
	sb_faces[1][1] = Draw_PicFromWad ("face_p4");
	sb_faces[0][0] = Draw_PicFromWad ("face5");
	sb_faces[0][1] = Draw_PicFromWad ("face_p5");

	sb_face_invis = Draw_PicFromWad ("face_invis");
	sb_face_invuln = Draw_PicFromWad ("face_invul2");
	sb_face_invis_invuln = Draw_PicFromWad ("face_inv2");
	sb_face_quad = Draw_PicFromWad ("face_quad");

	sb_sbar = Draw_PicFromWad ("sbar");
	sb_ibar = Draw_PicFromWad ("ibar");
	sb_scorebar = Draw_PicFromWad ("scorebar");

//MED 01/04/97 added new hipnotic weapons
	if (hipnotic)
	{
	  hsb_weapons[0][0] = Draw_PicFromWad ("inv_laser");
	  hsb_weapons[0][1] = Draw_PicFromWad ("inv_mjolnir");
	  hsb_weapons[0][2] = Draw_PicFromWad ("inv_gren_prox");
	  hsb_weapons[0][3] = Draw_PicFromWad ("inv_prox_gren");
	  hsb_weapons[0][4] = Draw_PicFromWad ("inv_prox");

	  hsb_weapons[1][0] = Draw_PicFromWad ("inv2_laser");
	  hsb_weapons[1][1] = Draw_PicFromWad ("inv2_mjolnir");
	  hsb_weapons[1][2] = Draw_PicFromWad ("inv2_gren_prox");
	  hsb_weapons[1][3] = Draw_PicFromWad ("inv2_prox_gren");
	  hsb_weapons[1][4] = Draw_PicFromWad ("inv2_prox");

	  for (i=0 ; i<5 ; i++)
	  {
		 hsb_weapons[2+i][0] = Draw_PicFromWad (va(vastr, "inva%i_laser",i+1));
		 hsb_weapons[2+i][1] = Draw_PicFromWad (va(vastr, "inva%i_mjolnir",i+1));
		 hsb_weapons[2+i][2] = Draw_PicFromWad (va(vastr, "inva%i_gren_prox",i+1));
		 hsb_weapons[2+i][3] = Draw_PicFromWad (va(vastr, "inva%i_prox_gren",i+1));
		 hsb_weapons[2+i][4] = Draw_PicFromWad (va(vastr, "inva%i_prox",i+1));
	  }

	  hsb_items[0] = Draw_PicFromWad ("sb_wsuit");
	  hsb_items[1] = Draw_PicFromWad ("sb_eshld");
	}

	if (rogue)
	{
		rsb_invbar[0] = Draw_PicFromWad ("r_invbar1");
		rsb_invbar[1] = Draw_PicFromWad ("r_invbar2");

		rsb_weapons[0] = Draw_PicFromWad ("r_lava");
		rsb_weapons[1] = Draw_PicFromWad ("r_superlava");
		rsb_weapons[2] = Draw_PicFromWad ("r_gren");
		rsb_weapons[3] = Draw_PicFromWad ("r_multirock");
		rsb_weapons[4] = Draw_PicFromWad ("r_plasma");

		rsb_items[0] = Draw_PicFromWad ("r_shield1");
        rsb_items[1] = Draw_PicFromWad ("r_agrav1");

// PGM 01/19/97 - team color border
        rsb_teambord = Draw_PicFromWad ("r_teambord");
// PGM 01/19/97 - team color border

		rsb_ammo[0] = Draw_PicFromWad ("r_ammolava");
		rsb_ammo[1] = Draw_PicFromWad ("r_ammomulti");
		rsb_ammo[2] = Draw_PicFromWad ("r_ammoplasma");
	}
#endif
}

//=============================================================================

// drawing routines are relative to the status bar location

/*
 =============
 Sbar_DrawPic
 =============
 */
void Sbar_DrawPic(int x, int y, qpic_t *pic)
{
    if (_g->cl.gametype == GAME_DEATHMATCH)
        Draw_Pic(x /* + ((vid.width - 320)>>1)*/, y + (vid.height - SBAR_HEIGHT), pic);
    else
        Draw_Pic(x + ((vid.width - 320) >> 1), y + (vid.height - SBAR_HEIGHT), pic);
}

/*
 =============
 Sbar_DrawTransPic
 =============
 */
void Sbar_DrawTransPic(int x, int y, qpic_t *pic)
{
    if (_g->cl.gametype == GAME_DEATHMATCH)
        Draw_TransPic(x /*+ ((vid.width - 320)>>1)*/, y + (vid.height - SBAR_HEIGHT), pic);
    else
        Draw_TransPic(x + ((vid.width - 320) >> 1), y + (vid.height - SBAR_HEIGHT), pic);
}

/*
 ================
 Sbar_DrawCharacter

 Draws one solid graphics character
 ================
 */
void Sbar_DrawCharacter(int x, int y, int num)
{
    if (_g->cl.gametype == GAME_DEATHMATCH)
        Draw_Character(x /*+ ((vid.width - 320)>>1) */+ 4, y + vid.height - SBAR_HEIGHT, num);
    else
        Draw_Character(x + ((vid.width - 320) >> 1) + 4, y + vid.height - SBAR_HEIGHT, num);
}

/*
 ================
 Sbar_DrawString
 ================
 */
void Sbar_DrawString(int x, int y, char *str)
{
    if (_g->cl.gametype == GAME_DEATHMATCH)
        Draw_String(x /*+ ((vid.width - 320)>>1)*/, y + vid.height - SBAR_HEIGHT, str);
    else
        Draw_String(x + ((vid.width - 320) >> 1), y + vid.height - SBAR_HEIGHT, str);
}

/*
 =============
 Sbar_itoa
 =============
 */
int Sbar_itoa(int num, char *buf)
{
    char *str;
    int pow10;
    int dig;

    str = buf;

    if (num < 0)
    {
        *str++ = '-';
        num = -num;
    }

    for (pow10 = 10; num >= pow10; pow10 *= 10)
        ;

    do
    {
        pow10 /= 10;
        dig = num / pow10;
        *str++ = '0' + dig;
        num -= dig * pow10;
    }
    while (pow10 != 1);

    *str = 0;

    return str - buf;
}

/*
 =============
 Sbar_DrawNum
 =============
 */
void Sbar_DrawNum(int x, int y, int num, int digits, int color)
{
    char str[12];
    char *ptr;
    int l, frame;

    l = Sbar_itoa(num, str);
    ptr = str;
    if (l > digits)
        ptr += (l - digits);
    if (l < digits)
        x += (digits - l) * 24;

    while (*ptr)
    {
        if (*ptr == '-')
            frame = STAT_MINUS;
        else
            frame = *ptr - '0';

        Sbar_DrawTransPic(x, y, sb_nums[color][frame]);
        x += 24;
        ptr++;
    }
}

//=============================================================================

int fragsort[MAX_SCOREBOARD];

char scoreboardtext[MAX_SCOREBOARD][20];
int scoreboardtop[MAX_SCOREBOARD];
int scoreboardbottom[MAX_SCOREBOARD];
int scoreboardcount[MAX_SCOREBOARD];
int scoreboardlines;

/*
 ===============
 Sbar_SortFrags
 ===============
 */
void Sbar_SortFrags(void)
{
    int i;

// sort by frags
    scoreboardlines = 0;
    for (i = 0; i < _g->cl.maxclients; i++)
    {
        if (_g->cl.scores[i].name[0])
        {
            fragsort[scoreboardlines] = i;
            scoreboardlines++;
        }
    }
#if HAS_MULTIPLAYER
	int j, k;
	for (i=0 ; i<scoreboardlines ; i++)
		for (j=0 ; j<scoreboardlines-1-i ; j++)
			if (_g->cl.scores[fragsort[j]].frags < _g->cl.scores[fragsort[j+1]].frags)
			{
				k = fragsort[j];
				fragsort[j] = fragsort[j+1];
				fragsort[j+1] = k;
			}
#endif
}

int Sbar_ColorForMap(int m)
{
    return m < 128 ? m + 8 : m + 8;
}

/*
 ===============
 Sbar_UpdateScoreboard
 ===============
 */
void Sbar_UpdateScoreboard(void)
{
    int i, k;
    int top, bottom;
    scoreboard_t *s;

    Sbar_SortFrags();

// draw the text
    memset(scoreboardtext, 0, sizeof(scoreboardtext));

    for (i = 0; i < scoreboardlines; i++)
    {
        k = fragsort[i];
        s = &_g->cl.scores[k];
        sprintf(&scoreboardtext[i][1], "%3i %s", s->frags, s->name);

        top = s->colors & 0xf0;
        bottom = (s->colors & 15) << 4;
        scoreboardtop[i] = Sbar_ColorForMap(top);
        scoreboardbottom[i] = Sbar_ColorForMap(bottom);
    }
}

/*
 ===============
 Sbar_SoloScoreboard
 ===============
 */
void Sbar_SoloScoreboard(void)
{
    char str[80];
    int minutes, seconds, tens, units;
    int l;

    sprintf(str, "Monsters:%3i /%3i", _g->cl.stats[STAT_MONSTERS], _g->cl.stats[STAT_TOTALMONSTERS]);
    Sbar_DrawString(8, 4, str);

    sprintf(str, "Secrets :%3i /%3i", _g->cl.stats[STAT_SECRETS], _g->cl.stats[STAT_TOTALSECRETS]);
    Sbar_DrawString(8, 12, str);

// time
    minutes = _g->cl.time / 60;
    seconds = _g->cl.time - 60 * minutes;
    tens = seconds / 10;
    units = seconds - 10 * tens;
    sprintf(str, "Time :%3i:%i%i", minutes, tens, units);
    Sbar_DrawString(184, 4, str);

// draw level name
    l = strlen(_g->cl.levelname);
    Sbar_DrawString(232 - l * 4, 12, _g->cl.levelname);
}

/*
 ===============
 Sbar_DrawScoreboard
 ===============
 */
void Sbar_DrawScoreboard(void)
{
    Sbar_SoloScoreboard();
    if (_g->cl.gametype == GAME_DEATHMATCH)
        Sbar_DeathmatchOverlay();
#if 0
	int		i, j, c;
	int		x, y;
	int		l;
	int		top, bottom;
	scoreboard_t	*s;

	if (cl.gametype != GAME_DEATHMATCH)
	{
		Sbar_SoloScoreboard ();
		return;
	}

	Sbar_UpdateScoreboard ();

	l = scoreboardlines <= 6 ? scoreboardlines : 6;

	for (i=0 ; i<l ; i++)
	{
		x = 20*(i&1);
		y = i/2 * 8;

		s = &cl.scores[fragsort[i]];
		if (!s->name[0])
			continue;

	// draw background
		top = s->colors & 0xf0;
		bottom = (s->colors & 15)<<4;
		top = Sbar_ColorForMap (top);
		bottom = Sbar_ColorForMap (bottom);

		Draw_Fill ( x*8+10 + ((vid.width - 320)>>1), y + vid.height - SBAR_HEIGHT, 28, 4, top);
		Draw_Fill ( x*8+10 + ((vid.width - 320)>>1), y+4 + vid.height - SBAR_HEIGHT, 28, 4, bottom);

	// draw text
		for (j=0 ; j<20 ; j++)
		{
			c = scoreboardtext[i][j];
			if (c == 0 || c == ' ')
				continue;
			Sbar_DrawCharacter ( (x+j)*8, y, c);
		}
	}
#endif
}

//=============================================================================

/*
 ===============
 Sbar_DrawInventory
 ===============
 */
void Sbar_DrawInventory(void)
{
    int i;
    char num[6];
    float time;
    int flashon;

    if (rogue)
    {
        if (_g->cl.stats[STAT_ACTIVEWEAPON] >= RIT_LAVA_NAILGUN)
            Sbar_DrawPic(0, -24, rsb_invbar[0]);
        else
            Sbar_DrawPic(0, -24, rsb_invbar[1]);
    }
    else
    {
        Sbar_DrawPic(0, -24, sb_ibar);
    }

// weapons
    for (i = 0; i < 7; i++)
    {
        if (_g->cl.items & (IT_SHOTGUN << i))
        {
            time = _g->cl.item_gettime[i];
            flashon = (int) ((_g->cl.time - time) * 10);
            if (flashon >= 10)
            {
                if (_g->cl.stats[STAT_ACTIVEWEAPON] == (IT_SHOTGUN << i))
                    flashon = 1;
                else
                    flashon = 0;
            }
            else
                flashon = (flashon % 5) + 2;

            Sbar_DrawPic(i * 24, -16, sb_weapons[flashon][i]);

            if (flashon > 1)
                sb_updates = 0;		// force update to remove flash
        }
    }

// MED 01/04/97
// hipnotic weapons
    if (hipnotic)
    {
        int grenadeflashing = 0;
        for (i = 0; i < 4; i++)
        {
            if (_g->cl.items & (1 << hipweapons[i]))
            {
                time = _g->cl.item_gettime[hipweapons[i]];
                flashon = (int) ((_g->cl.time - time) * 10);
                if (flashon >= 10)
                {
                    if (_g->cl.stats[STAT_ACTIVEWEAPON] == (1 << hipweapons[i]))
                        flashon = 1;
                    else
                        flashon = 0;
                }
                else
                    flashon = (flashon % 5) + 2;

                // check grenade launcher
                if (i == 2)
                {
                    if (_g->cl.items & HIT_PROXIMITY_GUN)
                    {
                        if (flashon)
                        {
                            grenadeflashing = 1;
                            Sbar_DrawPic(96, -16, hsb_weapons[flashon][2]);
                        }
                    }
                }
                else if (i == 3)
                {
                    if (_g->cl.items & (IT_SHOTGUN << 4))
                    {
                        if (flashon && !grenadeflashing)
                        {
                            Sbar_DrawPic(96, -16, hsb_weapons[flashon][3]);
                        }
                        else if (!grenadeflashing)
                        {
                            Sbar_DrawPic(96, -16, hsb_weapons[0][3]);
                        }
                    }
                    else
                        Sbar_DrawPic(96, -16, hsb_weapons[flashon][4]);
                }
                else
                    Sbar_DrawPic(176 + (i * 24), -16, hsb_weapons[flashon][i]);
                if (flashon > 1)
                    sb_updates = 0;      // force update to remove flash
            }
        }
    }

    if (rogue)
    {
        // check for powered up weapon.
        if (_g->cl.stats[STAT_ACTIVEWEAPON] >= RIT_LAVA_NAILGUN)
        {
            for (i = 0; i < 5; i++)
            {
                if (_g->cl.stats[STAT_ACTIVEWEAPON] == (RIT_LAVA_NAILGUN << i))
                {
                    Sbar_DrawPic((i + 2) * 24, -16, rsb_weapons[i]);
                }
            }
        }
    }

// ammo counts
    for (i = 0; i < 4; i++)
    {
        sprintf(num, "%3i", _g->cl.stats[STAT_SHELLS + i]);
        if (num[0] != ' ')
            Sbar_DrawCharacter((6 * i + 1) * 8 - 2, -24, 18 + num[0] - '0');
        if (num[1] != ' ')
            Sbar_DrawCharacter((6 * i + 2) * 8 - 2, -24, 18 + num[1] - '0');
        if (num[2] != ' ')
            Sbar_DrawCharacter((6 * i + 3) * 8 - 2, -24, 18 + num[2] - '0');
    }

    flashon = 0;
    // items
    for (i = 0; i < 6; i++)
        if (_g->cl.items & (1 << (17 + i)))
        {
            time = _g->cl.item_gettime[17 + i];
            if (time && time > _g->cl.time - 2 && flashon)
            {  // flash frame
                sb_updates = 0;
            }
            else
            {
                //MED 01/04/97 changed keys
                if (!hipnotic || (i > 1))
                {
                    Sbar_DrawPic(192 + i * 16, -16, sb_items[i]);
                }
            }
            if (time && time > _g->cl.time - 2)
                sb_updates = 0;
        }
    //MED 01/04/97 added hipnotic items
    // hipnotic items
    if (hipnotic)
    {
        for (i = 0; i < 2; i++)
            if (_g->cl.items & (1 << (24 + i)))
            {
                time = _g->cl.item_gettime[24 + i];
                if (time && time > _g->cl.time - 2 && flashon)
                {  // flash frame
                    sb_updates = 0;
                }
                else
                {
                    Sbar_DrawPic(288 + i * 16, -16, hsb_items[i]);
                }
                if (time && time > _g->cl.time - 2)
                    sb_updates = 0;
            }
    }

    if (rogue)
    {
        // new rogue items
        for (i = 0; i < 2; i++)
        {
            if (_g->cl.items & (1 << (29 + i)))
            {
                time = _g->cl.item_gettime[29 + i];

                if (time && time > _g->cl.time - 2 && flashon)
                {	// flash frame
                    sb_updates = 0;
                }
                else
                {
                    Sbar_DrawPic(288 + i * 16, -16, rsb_items[i]);
                }

                if (time && time > _g->cl.time - 2)
                    sb_updates = 0;
            }
        }
    }
    else
    {
        // sigils
        for (i = 0; i < 4; i++)
        {
            if (_g->cl.items & (1 << (28 + i)))
            {
                time = _g->cl.item_gettime[28 + i];
                if (time && time > _g->cl.time - 2 && flashon)
                {	// flash frame
                    sb_updates = 0;
                }
                else
                    Sbar_DrawPic(320 - 32 + i * 8, -16, sb_sigil[i]);
                if (time && time > _g->cl.time - 2)
                    sb_updates = 0;
            }
        }
    }
}

//=============================================================================

/*
 ===============
 Sbar_DrawFrags
 ===============
 */
void Sbar_DrawFrags(void)
{
    int i, k, l;
    int top, bottom;
    int x, y, f;
    int xofs;
    char num[12];
    scoreboard_t *s;

    Sbar_SortFrags();

// draw the text
    l = scoreboardlines <= 4 ? scoreboardlines : 4;

    x = 23;
    if (_g->cl.gametype == GAME_DEATHMATCH)
        xofs = 0;
    else
        xofs = (vid.width - 320) >> 1;
    y = vid.height - SBAR_HEIGHT - 23;

    for (i = 0; i < l; i++)
    {
        k = fragsort[i];
        s = &_g->cl.scores[k];
        if (!s->name[0])
            continue;

        // draw background
        top = s->colors & 0xf0;
        bottom = (s->colors & 15) << 4;
        top = Sbar_ColorForMap(top);
        bottom = Sbar_ColorForMap(bottom);

        Draw_Fill(xofs + x * 8 + 10, y, 28, 4, top);
        Draw_Fill(xofs + x * 8 + 10, y + 4, 28, 3, bottom);

        // draw number
        f = s->frags;
        sprintf(num, "%3i", f);

        Sbar_DrawCharacter((x + 1) * 8, -24, num[0]);
        Sbar_DrawCharacter((x + 2) * 8, -24, num[1]);
        Sbar_DrawCharacter((x + 3) * 8, -24, num[2]);

        if (k == _g->cl.viewentity - 1)
        {
            Sbar_DrawCharacter(x * 8 + 2, -24, 16);
            Sbar_DrawCharacter((x + 4) * 8 - 4, -24, 17);
        }
        x += 4;
    }
}

//=============================================================================

/*
 ===============
 Sbar_DrawFace
 ===============
 */
void Sbar_DrawFace(void)
{
    int f, anim;

// PGM 01/19/97 - team color drawing
// PGM 03/02/97 - fixed so color swatch only appears in CTF modes
    if (rogue && (_g->cl.maxclients != 1) && (teamplay > 3) && (teamplay < 7))
    {
        int top, bottom;
        int xofs;
        char num[12];
        scoreboard_t *s;

        s = &_g->cl.scores[_g->cl.viewentity - 1];
        // draw background
        top = s->colors & 0xf0;
        bottom = (s->colors & 15) << 4;
        top = Sbar_ColorForMap(top);
        bottom = Sbar_ColorForMap(bottom);

        if (_g->cl.gametype == GAME_DEATHMATCH)
            xofs = 113;
        else
            xofs = ((vid.width - 320) >> 1) + 113;

        Sbar_DrawPic(112, 0, rsb_teambord);
        Draw_Fill(xofs, vid.height - SBAR_HEIGHT + 3, 22, 9, top);
        Draw_Fill(xofs, vid.height - SBAR_HEIGHT + 12, 22, 9, bottom);

        // draw number
        f = s->frags;
        sprintf(num, "%3i", f);

        if (top == 8)
        {
            if (num[0] != ' ')
                Sbar_DrawCharacter(109, 3, 18 + num[0] - '0');
            if (num[1] != ' ')
                Sbar_DrawCharacter(116, 3, 18 + num[1] - '0');
            if (num[2] != ' ')
                Sbar_DrawCharacter(123, 3, 18 + num[2] - '0');
        }
        else
        {
            Sbar_DrawCharacter(109, 3, num[0]);
            Sbar_DrawCharacter(116, 3, num[1]);
            Sbar_DrawCharacter(123, 3, num[2]);
        }

        return;
    }
// PGM 01/19/97 - team color drawing

    if ((_g->cl.items & (IT_INVISIBILITY | IT_INVULNERABILITY)) == (IT_INVISIBILITY | IT_INVULNERABILITY))
    {
        Sbar_DrawPic(112, 0, sb_face_invis_invuln);
        return;
    }
    if (_g->cl.items & IT_QUAD)
    {
        Sbar_DrawPic(112, 0, sb_face_quad);
        return;
    }
    if (_g->cl.items & IT_INVISIBILITY)
    {
        Sbar_DrawPic(112, 0, sb_face_invis);
        return;
    }
    if (_g->cl.items & IT_INVULNERABILITY)
    {
        Sbar_DrawPic(112, 0, sb_face_invuln);
        return;
    }

    if (_g->cl.stats[STAT_HEALTH] >= 100)
        f = 4;
    else
        f = _g->cl.stats[STAT_HEALTH] / 20;

    if (_g->cl.time <= _g->cl.faceanimtime)
    {
        anim = 1;
        sb_updates = 0;		// make sure the anim gets drawn over
    }
    else
        anim = 0;
    Sbar_DrawPic(112, 0, sb_faces[f][anim]);
}

/*
 ===============
 Sbar_Draw
 ===============
 */
void Sbar_Draw(void)
{
    if (scr_con_current == vid.height)
        return;		// console is full screen

//#if FULL_FRAME_BUFFER
    if (sb_updates >= vid.numpages)
        return;
//#endif
    scr_copyeverything = 1;

    sb_updates++;
// no need to call this.
//    if (sb_lines && vid.width > 320)
//        Draw_TileClear(0, vid.height - sb_lines, vid.width, sb_lines);

    if (sb_lines > 24)
    {
        Sbar_DrawInventory();
        if (_g->cl.maxclients != 1)
            Sbar_DrawFrags();
    }

    if (sb_showscores || _g->cl.stats[STAT_HEALTH] <= 0)
    {
        Sbar_DrawPic(0, 0, sb_scorebar);
        Sbar_DrawScoreboard();
        sb_updates = 0;
    }
    else if (sb_lines)
    {
#if !WIN32 && CACHE_STATUS_BAR_TO_FLASH_IF_POSSIBLE
    if (isOnExternalFlash(sb_sbar))
    {
        Sbar_DrawPic(0, 0, sb_sbar);
    }
    else
    {
        uint32_t *buffer = (uint32_t*) ((uint8_t*)aux_buffer + SCREEN_WIDTH * 24);
        uint32_t *source = (uint32_t *) (sb_sbar + 1);  // data comes right after sb_sbar.
        for (int i = 0; i < 24 * SCREEN_WIDTH / 16; i++)
        {
            *buffer++ = *source++;
            *buffer++ = *source++;
            *buffer++ = *source++;
            *buffer++ = *source++;
        }
    }
#else
    Sbar_DrawPic(0, 0, sb_sbar);

#endif

        // keys (hipnotic only)
        //MED 01/04/97 moved keys here so they would not be overwritten
        if (hipnotic)
        {
            if (_g->cl.items & IT_KEY1)
                Sbar_DrawPic(209, 3, sb_items[0]);
            if (_g->cl.items & IT_KEY2)
                Sbar_DrawPic(209, 12, sb_items[1]);
        }
        // armor
        if (_g->cl.items & IT_INVULNERABILITY)
        {
            Sbar_DrawNum(24, 0, 666, 3, 1);
            Sbar_DrawPic(0, 0, draw_disc);
        }
        else
        {
            if (rogue)
            {
                Sbar_DrawNum(24, 0, _g->cl.stats[STAT_ARMOR], 3, _g->cl.stats[STAT_ARMOR] <= 25);
                if (_g->cl.items & RIT_ARMOR3)
                    Sbar_DrawPic(0, 0, sb_armor[2]);
                else if (_g->cl.items & RIT_ARMOR2)
                    Sbar_DrawPic(0, 0, sb_armor[1]);
                else if (_g->cl.items & RIT_ARMOR1)
                    Sbar_DrawPic(0, 0, sb_armor[0]);
            }
            else
            {
                Sbar_DrawNum(24, 0, _g->cl.stats[STAT_ARMOR], 3, _g->cl.stats[STAT_ARMOR] <= 25);
                if (_g->cl.items & IT_ARMOR3)
                    Sbar_DrawPic(0, 0, sb_armor[2]);
                else if (_g->cl.items & IT_ARMOR2)
                    Sbar_DrawPic(0, 0, sb_armor[1]);
                else if (_g->cl.items & IT_ARMOR1)
                    Sbar_DrawPic(0, 0, sb_armor[0]);
            }
        }

        // face
        Sbar_DrawFace();

        // health
        Sbar_DrawNum(136, 0, _g->cl.stats[STAT_HEALTH], 3, _g->cl.stats[STAT_HEALTH] <= 25);

        // ammo icon
        if (rogue)
        {
            if (_g->cl.items & RIT_SHELLS)
                Sbar_DrawPic(224, 0, sb_ammo[0]);
            else if (_g->cl.items & RIT_NAILS)
                Sbar_DrawPic(224, 0, sb_ammo[1]);
            else if (_g->cl.items & RIT_ROCKETS)
                Sbar_DrawPic(224, 0, sb_ammo[2]);
            else if (_g->cl.items & RIT_CELLS)
                Sbar_DrawPic(224, 0, sb_ammo[3]);
            else if (_g->cl.items & RIT_LAVA_NAILS)
                Sbar_DrawPic(224, 0, rsb_ammo[0]);
            else if (_g->cl.items & RIT_PLASMA_AMMO)
                Sbar_DrawPic(224, 0, rsb_ammo[1]);
            else if (_g->cl.items & RIT_MULTI_ROCKETS)
                Sbar_DrawPic(224, 0, rsb_ammo[2]);
        }
        else
        {
            if (_g->cl.items & IT_SHELLS)
                Sbar_DrawPic(224, 0, sb_ammo[0]);
            else if (_g->cl.items & IT_NAILS)
                Sbar_DrawPic(224, 0, sb_ammo[1]);
            else if (_g->cl.items & IT_ROCKETS)
                Sbar_DrawPic(224, 0, sb_ammo[2]);
            else if (_g->cl.items & IT_CELLS)
                Sbar_DrawPic(224, 0, sb_ammo[3]);
        }

        Sbar_DrawNum(248, 0, _g->cl.stats[STAT_AMMO], 3, _g->cl.stats[STAT_AMMO] <= 10);
    }
#if HAS_MULTIPLAYER
	if (vid.width > 320) {
		if (_g->cl.gametype == GAME_DEATHMATCH)
			Sbar_MiniDeathmatchOverlay ();
	}
#endif
}

//=============================================================================

/*
 ==================
 Sbar_IntermissionNumber

 ==================
 */
void Sbar_IntermissionNumber(int x, int y, int num, int digits, int color)
{
    char str[12];
    char *ptr;
    int l, frame;

    l = Sbar_itoa(num, str);
    ptr = str;
    if (l > digits)
        ptr += (l - digits);
    if (l < digits)
        x += (digits - l) * 24;

    while (*ptr)
    {
        if (*ptr == '-')
            frame = STAT_MINUS;
        else
            frame = *ptr - '0';

        Draw_TransPic(x, y, sb_nums[color][frame]);
        x += 24;
        ptr++;
    }
}

/*
 ==================
 Sbar_DeathmatchOverlay

 ==================
 */
void Sbar_DeathmatchOverlay(void)
{
    qpic_t *pic;
    int i, k, l;
    int top, bottom;
    int x, y, f;
    char num[12];
    scoreboard_t *s;

    scr_copyeverything = 1;
    scr_fullupdate = 0;

    pic = Draw_CachePic("gfx/ranking.lmp");
    qpic_t qpd;
    extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));
    M_DrawPic((320 - qpd.width) / 2, 8, pic);

// scores
    Sbar_SortFrags();

// draw the text
    l = scoreboardlines;

    x = 80 + ((vid.width - 320) >> 1);
    y = 40;
    for (i = 0; i < l; i++)
    {
        k = fragsort[i];
        s = &_g->cl.scores[k];
        if (!s->name[0])
            continue;

        // draw background
        top = s->colors & 0xf0;
        bottom = (s->colors & 15) << 4;
        top = Sbar_ColorForMap(top);
        bottom = Sbar_ColorForMap(bottom);

        Draw_Fill(x, y, 40, 4, top);
        Draw_Fill(x, y + 4, 40, 4, bottom);

        // draw number
        f = s->frags;
        sprintf(num, "%3i", f);

        Draw_Character(x + 8, y, num[0]);
        Draw_Character(x + 16, y, num[1]);
        Draw_Character(x + 24, y, num[2]);

        if (k == _g->cl.viewentity - 1)
            Draw_Character(x - 8, y, 12);

#if 0
{
	int				total;
	int				n, minutes, tens, units;

	// draw time
		total = cl.completed_time - s->entertime;
		minutes = (int)total/60;
		n = total - minutes*60;
		tens = n/10;
		units = n%10;

		sprintf (num, "%3i:%i%i", minutes, tens, units);

		Draw_String ( x+48 , y, num);
}
#endif

        // draw name
        Draw_String(x + 64, y, s->name);

        y += 10;
    }
}
#if HAS_MULTIPLAYER
/*
==================
Sbar_DeathmatchOverlay

==================
*/
void Sbar_MiniDeathmatchOverlay (void)
{
	qpic_t			*pic;
	int				i, k, l;
	int				top, bottom;
	int				x, y, f;
	char			num[12];
	scoreboard_t	*s;
	int				numlines;

	if (vid.width < 512 || !sb_lines)
		return;

	scr_copyeverything = 1;
	scr_fullupdate = 0;

// scores
	Sbar_SortFrags ();

// draw the text
	l = scoreboardlines;
	y = vid.height - sb_lines;
	numlines = sb_lines/8;
	if (numlines < 3)
		return;

	//find us
	for (i = 0; i < scoreboardlines; i++)
		if (fragsort[i] == _g->cl.viewentity - 1)
			break;

    if (i == scoreboardlines) // we're not there
            i = 0;
    else // figure out start
            i = i - numlines/2;

    if (i > scoreboardlines - numlines)
            i = scoreboardlines - numlines;
    if (i < 0)
            i = 0;

	x = 324;
	for (/* */; i < scoreboardlines && y < vid.height - 8 ; i++)
	{
		k = fragsort[i];
		s = &_g->cl.scores[k];
		if (!s->name[0])
			continue;

	// draw background
		top = s->colors & 0xf0;
		bottom = (s->colors & 15)<<4;
		top = Sbar_ColorForMap (top);
		bottom = Sbar_ColorForMap (bottom);

		Draw_Fill ( x, y+1, 40, 3, top);
		Draw_Fill ( x, y+4, 40, 4, bottom);

	// draw number
		f = s->frags;
		sprintf (num, "%3i",f);

		Draw_Character ( x+8 , y, num[0]);
		Draw_Character ( x+16 , y, num[1]);
		Draw_Character ( x+24 , y, num[2]);

		if (k == _g->cl.viewentity - 1) {
			Draw_Character ( x, y, 16);
			Draw_Character ( x + 32, y, 17);
		}

#if 0
{
	int				total;
	int				n, minutes, tens, units;

	// draw time
		total = cl.completed_time - s->entertime;
		minutes = (int)total/60;
		n = total - minutes*60;
		tens = n/10;
		units = n%10;

		sprintf (num, "%3i:%i%i", minutes, tens, units);

		Draw_String ( x+48 , y, num);
}
#endif

	// draw name
		Draw_String (x+48, y, s->name);

		y += 8;
	}
}
#endif
/*
 ==================
 Sbar_IntermissionOverlay

 ==================
 */
void Sbar_IntermissionOverlay(void)
{
    qpic_t *pic;
    int dig;
    int num;
    //
    scr_copyeverything = 1;
    scr_fullupdate = 0;

#if HAS_MULTIPLAYER
	if (_g->cl.gametype == GAME_DEATHMATCH)
	{
		Sbar_DeathmatchOverlay ();
		return;
	}
#endif
#if ORIGINAL_INTERMISSION
    // next-hack: added because we cannot really go fullscreen
    fastMemclear32((byte*)&d_zbuffer[SCREEN_WIDTH * DRAW_BUFFER_HEIGHT] - SCREEN_WIDTH * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT), SCREEN_WIDTH * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT) / 4);

	pic = Draw_CachePic ("gfx/complete.lmp");
	Draw_Pic (64, 24, pic);

	pic = Draw_CachePic ("gfx/inter.lmp");
	Draw_TransPic (0, 56, pic);

// time
	dig = _g->cl.completed_time/60;
	Sbar_IntermissionNumber (160, 64, dig, 3, 0);
	num = _g->cl.completed_time - dig*60;
	Draw_TransPic (234,64,sb_colon);
	Draw_TransPic (246,64,sb_nums[0][num/10]);
	Draw_TransPic (266,64,sb_nums[0][num%10]);

	Sbar_IntermissionNumber (160, 104, _g->cl.stats[STAT_SECRETS], 3, 0);
	Draw_TransPic (232,104,sb_slash);
	Sbar_IntermissionNumber (240, 104, _g->cl.stats[STAT_TOTALSECRETS], 3, 0);

	Sbar_IntermissionNumber (160, 144, _g->cl.stats[STAT_MONSTERS], 3, 0);
	Draw_TransPic (232,144,sb_slash);
	Sbar_IntermissionNumber (240, 144, _g->cl.stats[STAT_TOTALMONSTERS], 3, 0);
#else
    pic = Draw_CachePic("gfx/complete.lmp");

    Draw_Pic(64, 24 - 8, pic);

    pic = Draw_CachePic("gfx/inter.lmp");
    Draw_TransPic(0, 56 - 20, pic);

// time
    dig = _g->cl.completed_time / 60;
    Sbar_IntermissionNumber(160, 64 - 20, dig, 3, 0);
    num = _g->cl.completed_time - dig * 60;
    Draw_TransPic(234, 64 - 20, sb_colon);
    Draw_TransPic(246, 64 - 20, sb_nums[0][num / 10]);
    Draw_TransPic(266, 64 - 20, sb_nums[0][num % 10]);

    Sbar_IntermissionNumber(160, 104 - 20, _g->cl.stats[STAT_SECRETS], 3, 0);
    Draw_TransPic(232, 104 - 24, sb_slash);
    Sbar_IntermissionNumber(240, 104 - 20, _g->cl.stats[STAT_TOTALSECRETS], 3, 0);

    Sbar_IntermissionNumber(160, 144 - 20, _g->cl.stats[STAT_MONSTERS], 3, 0);
    Draw_TransPic(232, 144 - 32, sb_slash);
    Sbar_IntermissionNumber(240, 144 - 20, _g->cl.stats[STAT_TOTALMONSTERS], 3, 0);
    Sbar_Draw();
#endif
}

/*
 ==================
 Sbar_FinaleOverlay

 ==================
 */
void Sbar_FinaleOverlay(void)
{
    qpic_t *pic;

    scr_copyeverything = 1;

    pic = Draw_CachePic("gfx/finale.lmp");
    qpic_t qpd;
    extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));
    scr_fullupdate = 0;
    Draw_TransPic((vid.width - qpd.width) / 2, 16, pic);
    Sbar_Draw();
}
