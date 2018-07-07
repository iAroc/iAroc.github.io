function LoadCharacters() {
	var Characters = [
		{
			Name: {
				EN: 'Link',
				DE: 'Link',
				FR: 'Link',
				ES: 'Link',
				IT: 'Link'
			},
			Offset: 0x0
		},
		{
			Name: {
				EN: 'Zelda',
				DE: 'Zelda',
				FR: 'Zelda',
				ES: 'Zelda',
				IT: 'Zelda'
			},
			Offset: 0x30
		},
		{
			Name: {
				EN: 'Sheik',
				DE: 'Shiek',
				FR: 'Sheik',
				ES: 'Sheik',
				IT: 'Sheik'
			},
			Offset: 0x60
		},
		{
			Name: {
				EN: 'Impa',
				DE: 'Impa',
				FR: 'Impa',
				ES: 'Impa',
				IT: 'Impa'
			},
			Offset: 0x90
		},
		{
			Name: {
				EN: 'Ganondorf',
				DE: 'Ganondorf',
				FR: 'Ganondorf',
				ES: 'Ganondorf',
				IT: 'Ganondorf'
			},
			Offset: 0xC0
		},
		{
			Name: {
				EN: 'Darunia',
				DE: 'Darunia',
				FR: 'Darunia',
				ES: 'Darunia',
				IT: 'Darunia'
			},
			Offset: 0xF0
		},
		{
			Name: {
				EN: 'Ruto',
				DE: 'Ruto',
				FR: 'Ruto',
				ES: 'Ruto',
				IT: 'Ruto'
			},
			Offset: 0x120
		},
		{
			Name: {
				EN: 'Agitha',
				DE: 'Agnetha',
				FR: 'Machaon',
				ES: 'Maripola',
				IT: 'Xenia'
			},
			Offset: 0x150
		},
		{
			Name: {
				EN: 'Midna',
				DE: 'Midna',
				FR: 'Midona',
				ES: 'Midna',
				IT: 'Midna'
			},
			Offset: 0x180
		},
		{
			Name: {
				EN: 'Fi',
				DE: 'Phai',
				FR: 'Fay',
				ES: 'Fay',
				IT: 'Faih'
			},
			Offset: 0x1B0
		},
		{
			Name: {
				EN: 'Ghirahim',
				DE: 'Ghirahim',
				FR: 'Ghirahim',
				ES: 'Grahim',
				IT: 'Ghiraim'
			},
			Offset: 0x1E0
		},
		{
			Name: {
				EN: 'Zant',
				DE: 'Zanto',
				FR: 'Xanto',
				ES: 'Zant',
				IT: 'Zant'
			},
			Offset: 0x210
		},
		{
			Name: {
				EN: 'Lana',
				DE: 'Lana',
				FR: 'Lana',
				ES: 'Lana',
				IT: 'Lana'
			},
			Offset: 0x240
		},
		{
			Name: {
				EN: 'Cia',
				DE: 'Cia',
				FR: 'Cya',
				ES: 'Cya',
				IT: 'Cia'
			},
			Offset: 0x270
		},
		{
			Name: {
				EN: 'Volga',
				DE: 'Volga',
				FR: 'Volga',
				ES: 'Volga',
				IT: 'Volga'
			},
			Offset: 0x2A0
		},
		{
			Name: {
				EN: 'Wizzro',
				DE: 'Pyroma',
				FR: 'Iscerro',
				ES: 'Invocante',
				IT: 'Sciaman'
			},
			Offset: 0x2D0
		},
		{
			Name: {
				EN: 'Twili Midna',
				DE: 'Midna',
				FR: 'Midona',
				ES: 'Midna real',
				IT: 'Midna'
			},
			Offset: 0x300
		},
		{
			Name: {
				EN: 'Young Link',
				DE: 'Link',
				FR: 'Link',
				ES: 'Link niño',
				IT: 'Link'
			},
			Offset: 0x330
		},
		{
			Name: {
				EN: 'Tingle',
				DE: 'Tingle',
				FR: 'Tingle',
				ES: 'Tingle',
				IT: 'Tingle'
			},
			Offset: 0x360
		},
		{
			Name: {
				EN: 'Ganon',
				DE: 'Ganon',
				FR: 'Ganon',
				ES: 'Ganon',
				IT: 'Ganon'
			},
			Offset: 0x390
		},
		{
			Name: {
				EN: 'Cucco',
				DE: 'Cucco',
				FR: 'Cucco',
				ES: 'Cucco',
				IT: 'Cucco'
			},
			Offset: 0x3C0
		},
		{
			Name: {
				EN: 'Linkle',
				DE: 'Linkle',
				FR: 'Linkle',
				ES: 'Linkle',
				IT: 'Linkle'
			},
			Offset: 0x3F0
		},
		{
			Name: {
				EN: 'Skull Kid',
				DE: 'Horror Kid',
				FR: 'Skull Kid',
				ES: 'Skull Kid',
				IT: 'Skull Kid'
			},
			Offset: 0x420
		},
		{
			Name: {
				EN: 'Toon Link',
				DE: 'Link',
				FR: 'Link',
				ES: 'Toon Link',
				IT: 'Link'
			},
			Offset: 0x450
		},
		{
			Name: {
				EN: 'Tetra',
				DE: 'Tetra',
				FR: 'Tetra',
				ES: 'Tetra',
				IT: 'Dazel'
			},
			Offset: 0x480
		},
		{
			Name: {
				EN: 'King Daphnes',
				DE: 'König Daphnos',
				FR: 'Roi d\'Hyrule',
				ES: 'Rey de Hyrule',
				IT: 'Re Dafnes'
			},
			Offset: 0x4B0
		},
		{
			Name: {
				EN: 'Medli',
				DE: 'Medolie',
				FR: 'Médolie',
				ES: 'Medli',
				IT: 'Famirè'
			},
			Offset: 0x4E0
		},
		{
			Name: {
				EN: 'Marin',
				DE: 'Marin',
				FR: 'Marine',
				ES: 'Marin',
				IT: 'Marin'
			},
			Offset: 0x510
		},
		{
			Name: {
				EN: 'Toon Zelda',
				DE: 'Zelda',
				FR: 'Zelda',
				ES: 'Toon Zelda',
				IT: 'Zelda'
			},
			Offset: 0x540
		},
		{
			Name: {
				EN: 'Ravio',
				DE: 'Ravio',
				FR: 'Lavio',
				ES: 'Ravio',
				IT: 'Lavio'
			},
			Offset: 0x570
		},
		{
			Name: {
				EN: 'Yuga',
				DE: 'Yuga',
				FR: 'Yuga',
				ES: 'Yuga',
				IT: 'Yuga'
			},
			Offset: 0x5A0
		},
	]
	
	return Characters;
}