
//{{BLOCK(CollTest)

//======================================================================
//
//	CollTest, 128x128@8, 
//	+ palette 256 entries, not compressed
//	+ 2 tiles (t|f|p reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 512 + 128 + 256 = 896
//
//	Time-stamp: 2024-10-25, 15:06:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COLLTEST_H
#define GRIT_COLLTEST_H

#define CollTestTilesLen 128
extern const unsigned short CollTestTiles[64];

#define CollTestMapLen 256
extern const unsigned short CollTestMap[128];

#define CollTestPalLen 512
extern const unsigned short CollTestPal[256];

#endif // GRIT_COLLTEST_H

//}}BLOCK(CollTest)
