
//{{BLOCK(LvSelect)

//======================================================================
//
//	LvSelect, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 4096 + 2048 = 6656
//
//	Time-stamp: 2025-04-06, 11:23:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LVSELECT_H
#define GRIT_LVSELECT_H

#define LvSelectTilesLen 4096
extern const unsigned short LvSelectTiles[2048];

#define LvSelectMapLen 2048
extern const unsigned short LvSelectMap[1024];

#define LvSelectPalLen 512
extern const unsigned short LvSelectPal[256];

#endif // GRIT_LVSELECT_H

//}}BLOCK(LvSelect)
