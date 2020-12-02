# Quake II Chaos Bot Mod
This is a mod of an existing mod which adds support for bots.

It does compile under linux and is tested with Q2Pro Server.

## Todo List
This need to get done in no particular order .. they just need to be done
---------------------------------------------------------------------------
* Clean up Bugs, Optimize code
* New configuration file format
* Night Vision goggles
* Compression grenades
* Freeze adaptation to air gun
* Arrows stick to people
* reduce health on grenades
* reduce strength of explosive tips on crossbows
* proxy grenades stick to people
* proximity grenades that attach to the walls
* triggers for proximity grenades so that they can be remotely triggered
* flame thrower for air gun if possible
* light saber upgrade for sword possibly
* upgrade grapple hook to be able to grab items and bring them to you and possible be able to swing other players around.  Also, be able to cut grapple cable with sword/chainsaw/lightsaber
* port code to quake2 3.20 source code
* upgrade Havok Bots
* increase cell consumption on scanner and anti-grav belt
* make anti-grav belt act as some sort of minor protection against vortex
* Z-Bot detection
* Add spotlight to the turrets

## Fixed Bugs
These are bugs that have been fixed in Chaotic Dreams
-----------------------------------------------------------------------------

* Player can switch to beeing a camera, suicide, which causes them become
  invisible and then they start running around killing people
  -Fixed Wed May 19 21:10:23 CDT 1999

* Maplists file parser doesn't correctly detect file type and thusly linux
  systems can crash if trying to parse an MSDOS formatted maplists file
  -Fixed Wed May 19 21:10:30 CDT 1999

* If you kill someone who is faking death you don't get a frag for it
  -Fixed Fri May 21 20:15:55 CDT 1999

* Shotgun does not correctly cycle when out of ammo, it switches between the
  super shotgun and the regular shotgun and then back again
  -Fixed Fri May 21 19:59:15 CDT 1999

* Turrents start out w/ to much ammo
  -Fixed Sat May 22 08:23:08 CDT 1999

* When you die with the Flashlight on, the Flashlight will never turn off for
  you, even if you disconnect and reconnect, you have to restart the server.
  -Fixed Thu May 27 23:28:54 CDT 1999

* In CTF Mode, when a player was at the Join Menu, they could FakeDeath and
  drop all association of beeing on any team, and run around as a rogue
  capturing both flags and killing anyone.
  -Fixed Sat May 29 11:20:11 CDT 1999

* If a player picks up the temporary 100 health bonuses enough that the health
  makes it to 250, it never decreases again and makes their max health == 250
  -Fixed Sat May 29 16:51:07 CDT 1999

* FOV get's stuck and 90 degrees if you fakedeath and then un-fakedeath ..
  death or respawn fixes this. 
  -Fixed Fri Jun 18 12:13:03 CDT 1999

* After a FAKEDEATH the run/walk animation on a model no longer functions
  correctly
  -Fixed Fri Jun 18 12:13:20 CDT 1999

* Fakedeath removes negative frags
  -Fixed Fri Jun 18 12:13:33 CDT 1999 (No idea when this was fixed .. but we
  have tested it on v1.12 and have found that it doesn't exist)

* Occasionally a player will fakedeath and then not be able to change weapons
  after the un-fakedeath .. possibly related to the fact that the player
  doesn't correctly drop their weapon when they fakedeath
  -Fixed Fri Jun 18 12:14:46 CDT 1999

* If a player picks up a jetpack and uses it .. and while jetpack is in use,
  they grab another .. their old jetpack stops working all together.
  -Fixed Tue Jul 13 21:54:54 CDT 1999 ( This fix also makes the jetpack also
  correctly monitor the dmflags, so now if instant powerups are set then the
  jetpack instantly turns on and you cannot turn it off. )

* Somehow the "sv addbots" command seems to have vanished from beeing ussable
  in the v1.13beta binaries for the Win32 enviroment .. likley an issue with
  the project files
  -Fixed Tue Jul 13 21:55:19 CDT 1999 (This never "trully" existed as a code
  problem, this was likley an issue created by the early config of cvs and
  it's handling of the binaries.)

* If a player starts out with a grapple they can pick up a grapple once.
  -Fixed Sun Jul 18 01:47:50 EDT 1999

* one of the mystery crashes that was killing the game "appears" to have been
  resolved.  It seems that "occasionally" a player would kill a turret, and IF
  they ran outa of ammo and let the game "autoselect" their new weapon, the
  game would somehow manage to derefrence the it_aifirst pointer, at which
  point the weapon autochanger would try to see if the player had the airfist
  and the game would crash.  There is one other occurance of a similar issue
  that appears to happen but has not yet been tracked down.
  -Fixed Sun Jul 18 16:04:25 CDT 1999

* Fakedeath was causing model animation issues .. This was fixed earlier but
  the fix got lost from the code somehow. have reinstated the fix again.
  -Fixed Sun Jul 18 16:06:28 CDT 1999

* When a player reconnects with flashlight on the flashlight stays on
  -Fixed Fri Jul 23 01:24:58 EDT 1999

* Fixed a fakedeath cheat involving ammo 
  -Fixed Fri Aug 13 17:01

* Fixed problem where player was receiving -5 frags after faking death while falling into lava, and -15 frags
  when faking death after falling into acid.  This was also fixed a bug by which when you killed a fakedeath
  player, you would continue to receive frags if you continued to shoot the player, one frag for each shot.
  - Fixed Wed Aug 25 1999

* Fixed a problem with the turrets array being too small, this caused memory overwrite problems when three 
  turrets were active.  I believe this to be the source of the infamous "turret crash".
  - Fixed Sat Sep 3 08:23 AM EDT 1999

* Fixed incorrect scoring of rocket turret frags.  Frags caused by rocket turrets now credit +1 frag to turret  owner, and do not take away a frag from turret victim.  Except in the case when a turret kills its owner 
  (because the yutz hit his own turret), when it does take away 1 frag.
  - Fixed Mon Sep 6 1999

* Fixed scoring of laser mines.  Laser mine kills now record 1 frag to owner of laser mine, and 0 to victim, 
  rather than 0 and -1, respectively, unless player is killed by his own laser mine, in which case he receives
  a -1. Also corrected the obituary messages displayed so credit is given where due.
  - Fixed Thu Sep 9, 1999

* Fixed the Vortex section of the Valid_Target routine so that Vortices again suck :)
  - Fixed Sat Oct 2, 1999

* Made small changes in Valid_Target routine to make proxies more agressive
  - Fixed Mon Oct 4, 1999

* Fixed a problem in the map rotation code causing errors in sequential rotation
  - Fixed Fri Oct 8, 1999 

* Server parameters start_ammo_shells and start_ammo_explosiveshells were reversed.
  - Fixed Wed Oct 13, 1999

* Server parameter start_supershotgun did not give an explosive shotgun, just a normal one.  Once you had a normal one and no explosive one, you could not pick up another supershotgun even if you had explosive shells.
  - Fixed Wed Oct 13, 1999

* Fixed explosive shotgun not correctly applying radius damage.  Explosive shotgun now fully functional. BOOM!
  - Fixed Thu Oct 14, 1999

* Fixed incorrect scoring of grappling hook frags 
  - Fixed Nov 15, 1999

* Fixed bug which would allow someone to kick an item (like a weapon) which would normally respawn under an elevator, which would kill the weapon for the rest of the level.  Now killing the weapon causes it to respawn immediately.  This only applies to weapons/items/armor which are moved off of a respawn point.  A dropped item is just destroyed.
  - Fixed Sat Dec 12, 1999

* Added "sv nextmap" command to move to next map in rotation without messing up rotation.
  - Fixed Sat Dec 12, 1999

----- 1.13 release

* Fixed cheat involving large amounts of ammo "miraculously" flying out nowhere :) 
  - Fixed Thu Feb 10, 2000

* Fixed incorrect logfile generation of vortex, defence turret, rocket turret, and kamikaze scoring
  - Fixed Sat Feb 19, 2000  

* Added two new config vars, ex_arrow_damage (default 80) and ex_arrow_radius (default 200).  This was added to allow server admins to choose "extra crispy" arrows.
  - Fixed Wed Mar 15, 2000
 
* Fixed several bugs related to Proxies.  
    Valid_Target was not returning correctly for players or turrets.  
    Incorrect vector generated once target was acquired.
    Proxies once turned off would not come back on
    Proxies could detect invisible players
  - Fixed Sat Mar 25, 2000

----- 1.14 release 

