
#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>

#include "GooberTest.h" 
#include "BeastieBall.h"
#include "BGTest.h"
#include "CollisionTest.h" 

float pointDist(int x1, int y1, int x2, int y2){
    int ay = y2 - y1;
    int ax = x2 - x1;
    int r = sqrt32(pow(ax, 2) + pow(ay, 2));
    return (r);
}

bool inBetween(int x, int lowR, int highR){
        if (x >= lowR && x <= highR){
        return (true);
        } else return (false);
}

class wall {
        public:
   int x1;
   int x2;
   int y1;
   int y2;
   int dir;
       wall(int x, int xx, int y, int yy, int d) {
        x1 = x;
        x2 = xx;
        y1 = y;
        y2 = yy;
        dir = d;
   }
};

uint16 cen_x = 128;
uint16 cen_y = 100;

int bg_x = 0;
int bg_y = 0;

//angle calculation
s16 hyp = 0;
s16 adj = 0;
s16 opp = 0;

//Collision check
bool wallCol(wall wallN) {
        if (inBetween(cen_x - 16, wallN.x1, wallN.x2)){
        if (inBetween(cen_y + 16, wallN.y2, wallN.y1)){
                printf("Collision!!");
                return(true);
        } else return(false);
                } else return(false);
};

uint16 coll_x = 20;
uint16 coll_y = 40;

//**MAIN **//

int main(int argc, char *argv[]){
// initialize variables
uint16_t kyHeld;
touchPosition touch_pos;

//angle variables global
float32 ang = 0;
float32 ang_rad = 0;
int scale = 1 << 8;


videoSetMode(MODE_1_2D);
videoSetModeSub(MODE_1_2D);

vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_LCD);

consoleDemoInit();
lcdSwap();
//Main = Bottom Screen, Sub = Top Screen

// !!**Graphic Initialization**!!
oamInit(&oamMain, SpriteMapping_1D_32, false);
oamInit(&oamSub, SpriteMapping_1D_32, false);


//Initialize Background MAIN Data
int bg = bgInit(0,BgType_Text8bpp, BgSize_T_256x256, 0, 1);
dmaCopy(BGTestTiles, bgGetGfxPtr(bg), BGTestTilesLen);
dmaCopy(BGTestMap, bgGetMapPtr(bg), BGTestMapLen);
dmaCopy(BGTestPal, BG_PALETTE, BGTestPalLen);
/*
//Initialize Background SUB Data
int bgSb = bgInitSub(0,BgType_Text8bpp, BgSize_T_256x256, 0, 1);
dmaCopy(BGTestTiles, bgGetGfxPtr(bgSb), BGTestTilesLen);
dmaCopy(BGTestMap, bgGetMapPtr(bgSb), BGTestMapLen);
dmaCopy(BGTestPal, BG_PALETTE_SUB, BGTestPalLen);
*/

//Initialize Collision MAIN Data
int Col = bgInit(3,BgType_Rotation, BgSize_R_256x256, 1, 2);
dmaCopy(CollTestTiles, bgGetGfxPtr(Col), CollTestTilesLen);
dmaCopy(CollTestMap, bgGetMapPtr(Col), CollTestMapLen);

/*
//Initialize Collision SUB Data
int ColSb = bgInitSub(3,BgType_Rotation, BgSize_R_256x256, 1, 2);
dmaCopy(CollTestTiles, bgGetGfxPtr(ColSb), CollTestTilesLen);
dmaCopy(CollTestMap, bgGetMapPtr(ColSb), CollTestMapLen);
*/

//Set aside space for sprite and copy tile and pallete info to main engine
u16 *gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
dmaCopy(BeastieBallTiles, gfxMain, BeastieBallTilesLen);
dmaCopy(BeastieBallPal, SPRITE_PALETTE, BeastieBallPalLen);

u16 *plyrMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
dmaCopy(GooberTestTiles, plyrMain, GooberTestTilesLen);
dmaCopy(GooberTestPal, SPRITE_PALETTE, GooberTestPalLen);

//graphics
oamSet(&oamMain, 0,
        cen_x - 16, cen_y - 16, // Xoffset to center, Yoffset to center
        0, // Priority
        3, // Palette index
        SpriteSize_32x32, SpriteColorFormat_256Color, // Size, format
        plyrMain,  // Graphics offset
        0, // Affine index
        false, // Double size
        false, // Hide
        false, false, // H flip, V flip
        false); // Mosaic

//collision test
oamSet(&oamMain, 1,
        coll_x, coll_y,
        0,
        3,
        SpriteSize_32x32, SpriteColorFormat_256Color,
        gfxMain,
        1,
        false,
        false,
        true, false,
        true);

//WALL DECLERATIONS
wall wall0 (20, 100, 80, 30, 2);

while(1){ //This is just an infinite loop, until something stops it
    swiWaitForVBlank();
//Background Initalization
    bgSetScroll(bg, bg_x, bg_y);
    bgSetScroll(Col, bg_x/2, bg_y/2);
    //bgSetScroll(bgSb, bg_x, bg_y - 192);

//graphics manipulation
    oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
    oamSetXY(&oamMain, 1, coll_x, coll_y);
    kyHeld = keysHeld();

// !! Detect Touch Input !!
    if (kyHeld & KEY_TOUCH){
        touchRead(&touch_pos);

// !! angleCalculation !!

//get hypotenuse length with point dist
        s16 hyp = pointDist(cen_x, cen_y, touch_pos.px, touch_pos.py);
//get x distance with Xpos - touch_pos.px
        s16 adj = touch_pos.px - cen_x;
//gets y distance for movement
        s16 opp = touch_pos.py - cen_y;
//Calculate angle a -> INVcos(x_dis/hypLen)
//Speed vector at a starting at center
        ang = acos(adj/(hyp * 1.0)); 
        ang_rad = degreesToAngle(ang*(180/M_PI) - 90);
//Update console message
        printf("opp = [%d]\n", opp);
        printf("adj [%d]\n", adj);
//**Collision check**
        if (pointDist(coll_x, coll_y, cen_x, cen_y) <= 32){
                    adj /= 2;
                    opp /= 2;
                printf("Colliding");
        };

//BACKGROUND Movement
        bg_x -= (adj/7);
        coll_x += (adj/7);
        wall0.x1 += (adj/7);
        wall0.x2 += (adj/7);

        bg_y -= (opp/7);
        coll_y += (opp/7);
        wall0.y1 += (opp/7);
        wall0.y2 += (opp/7);

        if (wallCol(wall0)) {
                bg_y += (opp/7);
                coll_y -= (opp/7);
                wall0.y1 -= (opp/7);
                wall0.y2 -= (opp/7);
                printf("moving");
                };
        }
//Refresh visuals
        bgUpdate();
        scanKeys();
        oamUpdate(&oamMain);
        


    };

    //flush visuals
    oamFreeGfx(&oamMain, gfxMain);
    consoleClear();

};