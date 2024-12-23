
//{{BLOCK(BGTest)

//======================================================================
//
//	BGTest, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 8 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 512 + 2048 = 3072
//
//	Time-stamp: 2024-10-07, 18:03:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned short BGTestTiles[256] __attribute__((aligned(4)))=
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,

	0x0101,0x0101,0x0101,0x0101,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0101,0x0101,0x0101,0x0101,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,
	0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,

	0x0101,0x0101,0x0101,0x0101,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0101,0x0101,0x0101,0x0101,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,

	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0201,0x0202,0x0202,0x0202,0x0201,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
	0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,0x0202,
};

const unsigned short BGTestMap[1024] __attribute__((aligned(4)))=
{
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0004,0x0005,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0006,0x0007,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0003,0x0002,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0001,0x0000,0x0006,0x0007,0x0006,0x0007,0x0006,0x0007,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0004,0x0005,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0004,0x0005,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0006,0x0007,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0006,0x0007,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,

	0x0002,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,0x0003,0x0002,
	0x0000,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
	0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,0x0001,0x0000,
};

const unsigned short BGTestPal[256] __attribute__((aligned(4)))=
{
	0x1EA3,0x2075,0x68DA,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

//}}BLOCK(BGTest)
