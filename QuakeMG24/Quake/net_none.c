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
#include "quakedef.h"

#include "net_loop.h"

const net_driver_t net_drivers[MAX_NET_DRIVERS] =
{
{
    "Loopback",
//false,
    Loop_Init,
    Loop_Listen,
    Loop_SearchForHosts,
    Loop_Connect,
    Loop_CheckNewConnections,
    Loop_GetMessage,
    Loop_SendMessage,
    Loop_SendUnreliableMessage,
    Loop_CanSendMessage,
    Loop_CanSendUnreliableMessage,
    Loop_Close,
    Loop_Shutdown
}
};
ram_net_driver_t ram_net_drivers[MAX_NET_DRIVERS];
const int net_numdrivers = 1;
#if 0
net_landriver_t	net_landrivers[MAX_NET_DRIVERS];
int net_numlandrivers = 0;
#endif
