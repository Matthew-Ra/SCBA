
//{{BLOCK(L1R2)

//======================================================================
//
//	L1R2, 1024x1024@8, 
//	+ palette 256 entries, not compressed
//	+ 132 tiles (t|f|p reduced) not compressed
//	+ affine map, not compressed, 128x128 
//	Total size: 512 + 8448 + 16384 = 25344
//
//	Time-stamp: 2025-04-07, 03:51:48
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_L1R2_H
#define GRIT_L1R2_H

#define L1R2TilesLen 8448
extern const unsigned short L1R2Tiles[4224];

#define L1R2MapLen 16384
extern const unsigned short L1R2Map[8192];

#define L1R2PalLen 512
extern const unsigned short L1R2Pal[256];

#endif // GRIT_L1R2_H

//}}BLOCK(L1R2)
