#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>

#include "GooberTest.h" 
#include "BeastieBall.h"
#include "BGTest.h"
#include "CollisionTest.h" 

//TO DO
// Clean Up: Wall Class functions, functions for specific tasks
// Look into external console

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

uint16 cen_x = 128;
uint16 cen_y = 100;

int bg_x = 0;
int bg_y = 0;

//angle calculation
float hyp = 0;
float adj = 0;
float opp = 0;

uint16 coll_x = 20;
uint16 coll_y = 40;

// initialize variables
uint16_t kyHeld;
touchPosition touch_pos;

//angle variables global
float32 ang = 0;
float32 ang_rad = 0;
int scale = 1 << 8;

class wallClass {
public:
        int x1;
        int x2;
        int y1;
        int y2;
        int dir;
       int wallPoints(int x, int xx, int y, int yy, int d) { 
        this->x1 = x;
        this->x2 = xx;
        this->y1 = y;
        this->y2 = yy;
        this->dir = d;

        return (0);
        }

        //Collision check
        bool collision() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y2, this->y1)){
                                printf("Collision!!");
                                return(true);
                        } else return(false);
                } else return(false);
        };
};

//established wall array as well as an array of coordinate points for the wall objects

wallClass walls1[2];

int Test0[2][5]{
        {0, 256, 30, 0, 2},
        {20, 100, 80, 30, 2}
};


void angleCalculation() {
//get hypotenuse length with point dist
        hyp = pointDist(cen_x, cen_y, touch_pos.px, touch_pos.py);
//get x distance with Xpos - touch_pos.px
        adj = touch_pos.px - cen_x;
//gets y distance for movement
        opp = touch_pos.py - cen_y;
//Calculate angle a -> INVcos(x_dis/hypLen)
//Speed vector at a starting at center
        ang = acos(adj/(hyp * 1.0)); 
        ang_rad = degreesToAngle(ang*(180/M_PI) - 90);
//Update console message
        printf("opp = [%d]\n", opp);
        printf("adj [%d]\n", adj);
};

void graphicsUpdate() {

    s32 adjacentSpeed = (adj/7);
    s32 oppositeSpeed = (opp/7);

//**Enemy Collision check**
        if (pointDist(coll_x, coll_y, cen_x, cen_y) <= 32){
                    adjacentSpeed /= 2;
                    oppositeSpeed /= 2;
                printf("Colliding");
        };


        // !! Detect Touch Input !!
        if (kyHeld & KEY_TOUCH){
                touchRead(&touch_pos);
                angleCalculation();

//BACKGROUND Movement
        bg_x -= adjacentSpeed;
        coll_x += adjacentSpeed;


        bg_y -= oppositeSpeed;
        coll_y += oppositeSpeed;


        for (int i = 0; i <= 1; i++){
                walls1[i].x1 += adjacentSpeed;
                walls1[i].x2 += adjacentSpeed;

                walls1[i].y1 += oppositeSpeed;
                walls1[i].y2 += oppositeSpeed;

                if (walls1[i].collision()) { //CANCEL movement if collision detected
                        bg_y += oppositeSpeed;
                        coll_y -= oppositeSpeed;
                        for (int b = 0; b <= 1; b++){
                                walls1[b].y1 -= oppositeSpeed;
                                walls1[b].y2 -= oppositeSpeed;
                        }

                };

        };
}



        //Refresh visuals
        bgUpdate();
        scanKeys();
        oamUpdate(&oamMain);

        };

        


//**MAIN **//

int main(int argc, char *argv[]){ 


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

               walls1[0].wallPoints(Test0[0][0], Test0[0][1], Test0[0][2], Test0[0][3], Test0[0][4]);
               walls1[1].wallPoints(Test0[1][0], Test0[1][1], Test0[1][2], Test0[1][3], Test0[1][4]);


        while(1){ //This is just an infinite loop, until something stops it
                swiWaitForVBlank();
        //Background Initalization
                bgSetScroll(bg, bg_x, bg_y);
                bgSetScroll(Col, bg_x/2, bg_y/2);
                //bgSetScroll(bgSb, bg_x, bg_y - 192);

        //Graphics manipulation
                oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
                oamSetXY(&oamMain, 1, coll_x, coll_y);
                kyHeld = keysHeld();

                graphicsUpdate();
    //flush visuals
        oamFreeGfx(&oamMain, gfxMain);
        consoleClear();

        };
};