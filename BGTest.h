
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

#ifndef GRIT_BGTEST_H
#define GRIT_BGTEST_H

#define BGTestTilesLen 512
extern const unsigned short BGTestTiles[256];

#define BGTestMapLen 2048
extern const unsigned short BGTestMap[1024];

#define BGTestPalLen 512
extern const unsigned short BGTestPal[256];

#endif // GRIT_BGTEST_H

//}}BLOCK(BGTest)
