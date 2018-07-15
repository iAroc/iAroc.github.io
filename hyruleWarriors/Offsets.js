function LoadOffsets() {
	var Offsets = {}
	Offsets.General = {}
	Offsets.General.Rupees 		= 0x000002B8
	Offsets.General.DiscoverMaterials 		= 0x00001BFE
	Offsets.General.Material 	= 0x00001AFE
	Offsets.General.Weapons 	= 0x000337F4
	Offsets.Characters = {}
	Offsets.Characters.Base 	= 0x0003308C
	Offsets.Maps = {}
	Offsets.Maps.AdventureMap = {}
	Offsets.Maps.AdventureMap.Base		= 0x00002BE8
	Offsets.Maps.AdventureMap.LevelCount = 128
	Offsets.Maps.AdventureMap.Unlocked	= 0x00002BEC //00 = locked, 01 = beaten, 02 = unlocked, 03 = beaten and unlocked, 4 Bytes [XX 00 00 00]
	Offsets.Maps.AdventureMap.Beaten	= 0x00002DEC //E0 01 = Beaten, 00 00 = Unbeaten, 8 Bytes [XX XX 00 00 00 00 00 00]
	Offsets.Maps.AdventureMap.Items		= 0x000031EC
	Offsets.Maps.AdventureMap.Searched	= 0x00003250 //00 = Not Searched, 01 = Searched, 1 Byte
	Offsets.Maps.AdventureMap.LevelHasOffser = 0x000032D0 //00 = No Item, 01 = Item, 1 Byte
	Offsets.Maps.AdventureMap.EnemiesHidden	= 0x00003350 //00 = Hidden, 01 = Visible, 1 Byte
	Offsets.Maps.AdventureMap.Medal	= 0x000034D0 // FF FF FF FF = Locked/Unbeaten, 01 00 00 00 = Bronze, 02 = Silver, 03 = Gold, 4 Bytes
	Offsets.Maps.AdventureMap.NoFog	= 0x00005550 // 01 01 01 01 01 01 01 01 = No Fog, 00 00 00 00 00 00 00 00 = Fog, 8 Bytes
	
	return Offsets;
}