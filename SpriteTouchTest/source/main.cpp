#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>
#include <nds/arm9/background.h>

#include "GooberTest.h"
#include "BeastieBall.h"
#include "L1R1.h"
#include "L1R2.h"
#include "CollisionTest.h"




using namespace std;

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


//angle calculation variables;
float hyp = 0;
float adj = 0;
float opp = 0;


//angle variables global
float32 ang = 0;
float32 ang_rad = 0;
int scale = 1 << 8;


uint16 cen_x = 128;
uint16 cen_y = 100;

//background ids and position
int bg = 0;
int bgSb = 0;

int bg_x = 0;
int bg_y = 0;


// initialize variables
uint16_t kyHeld;
touchPosition touch_pos;


void positionInit(){

 cen_x = 128;
 cen_y = 100;
 
 bg_x = 0;
 bg_y = 0;

//angle calculation variables;
 hyp = 0;
 adj = 0;
 opp = 0;


//angle variables global
 ang = 0;
 ang_rad = 0;
 scale = 1 << 8;
};


class wallClass {
public:
        int x1;
        int x2;
        int y1;
        int y2;
       int wallPoints(int x, int xx, int y, int yy) {
        this->x1 = x;
        this->x2 = xx + 32;
        this->y1 = y - 32;
        this->y2 = yy;

        return (0);
        }


        //Collision check
        bool collisionVertical() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y1, this->y2)){
                                if ((inBetween(cen_y + 16, this->y1 - 8, this->y1 + 8)) or (inBetween(cen_y - 16, this->y2 - 8, this->y2 + 8))){
                                return(true);
                                }
                        } else return(false);
                }
                return(false);
        };


        bool collisionHorizontal() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y1, this->y2)){
                                if ( (inBetween(cen_x + 16, this->x2 , this->x2 + 32)) or (inBetween(cen_x + 16, this->x1, this->x1 + 8))){
                                return(true);
                                }
                        } else return(false);
                } 
                return(false);
        };
};


//established wall array as well as an array of coordinate points for the wall objects
wallClass walls1[3];

int L1R1[3][4]{
        {319, 383,  1088 , 832},
        {608, 656, 800, 1088},
        {512, 680, 864, 927}
};

int L1Ob[3][2]{
        {400, 975},
        {465, 915},
        {495, 885},       
};


int L1R2[16][4]{
        {320, 352, 832, 1024},
        {480, 512, 704, 1024},
        {96, 352, 832, 863},
        {256, 512, 704, 735},
        {96, 127, 768, 863},
        {0, 127, 768, 800},
        {96, 352, 832, 863},
        {0, 32, 608, 800},
        {96, 127, 224, 639},
        {96, 352, 832, 863},
        {256, 287, 352, 735},
        {256, 512, 352, 383},
        {96, 383, 224, 255},
        {480, 512, 224, 383},
        {352, 383, 0, 255},
        {448, 479, 0, 255}
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

};


void graphicsUpdate() {
    s32 adjacentSpeed = (adj/15);
    s32 oppositeSpeed = (opp/15);


//**Enemy Collision check**
for (int i = 0; i <= 2; i++){
        if (pointDist(L1Ob[i][0], L1Ob[i][1], cen_x, cen_y) <= 32){
                    adjacentSpeed /= 2;
                    oppositeSpeed /= 2;
        };
}
        // !! Detect Touch Input !!
        if (kyHeld & KEY_TOUCH){
                touchRead(&touch_pos);
                angleCalculation();


//BACKGROUND Movement
        bg_x -= adjacentSpeed;

        bg_y -= oppositeSpeed;
        for (int e = 0; e <= 2; e++){
                L1Ob[e][0] += adjacentSpeed;
                L1Ob[e][1] += oppositeSpeed; 
        }

        int wallSize = (sizeof(walls1)/sizeof(walls1[0])) - 1;
                for (int i = 0; i <= wallSize; i++){
                        walls1[i].x1 += adjacentSpeed;
                        walls1[i].x2 += adjacentSpeed;


                        walls1[i].y1 += oppositeSpeed;
                        walls1[i].y2 += oppositeSpeed;


                        if (walls1[i].collisionVertical()) { //CANCEL movement if collision detected
                                bg_y += oppositeSpeed;
                                for (int e = 0; e <= 2; e++){//enemy array
                                        L1Ob[e][1] -= oppositeSpeed; 
                                }

                                for (int w = 0; w <= wallSize; w++){
                                        walls1[w].y1 -= oppositeSpeed;
                                        walls1[w].y2 -= oppositeSpeed;
                                };
                        };


                        if (walls1[i].collisionHorizontal()) { //CANCEL movement if collision detected
                                bg_x += adjacentSpeed;
                                for (int e = 0; e <= 2; e++){
                                        L1Ob[e][0] -= adjacentSpeed;
                                }
                                for (int w = 0; w <= wallSize; w++){
                                        walls1[w].x1 -= adjacentSpeed;
                                        walls1[w].x2 -= adjacentSpeed;
                                };
                        };
                };
        };


        //Refresh visuals
        scanKeys();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);


};


class sceneClass {
        public:
        int sceneID;   //Unique Scene Identifier
        int sceneType; //0 = Menu, 1 = Level, 2 = Cutscene
        //Level Data
        char wallArray;


        void sceneInit(int ID, int type){
                this->sceneID = ID;
                this->sceneType = type;
        }


        void levelInit(char array){
                this->wallArray = array;
        }
};


void levelSetup(sceneClass scene) {
        positionInit();

        bg = bgInit(3,BgType_Rotation, BgSize_R_1024x1024, 0, 3);
        bgSb = bgInitSub(3,BgType_Rotation, BgSize_R_1024x1024, 0, 3);
        int L1R1size = (sizeof(L1R1)/sizeof(L1R1[0])) - 1;
        int L1R2size = (sizeof(L1R2)/sizeof(L1R2[0])) - 1;

//Which set of walls should be loaded?
        switch(scene.sceneID){
        case 0:
                for (int w = 0; w <= L1R1size; w++){
                        walls1[w].wallPoints(L1R1[w][0], L1R1[w][1], L1R1[w][2], L1R1[w][3]);
                }              


                dmaCopy(L1R1Tiles, bgGetGfxPtr(bg), L1R1TilesLen);
                dmaCopy(L1R1Map, bgGetMapPtr(bg), L1R1MapLen);
                dmaCopy(L1R1Pal, BG_PALETTE, L1R1PalLen);

                dmaCopy(L1R1Tiles, bgGetGfxPtr(bgSb), L1R1TilesLen);
                dmaCopy(L1R1Map, bgGetMapPtr(bgSb), L1R1MapLen);
                dmaCopy(L1R1Pal, BG_PALETTE_SUB, L1R1PalLen);
        break;
        case 1:


                for (int e = 0; e <= L1R2size; e++){
                        walls1[e].wallPoints(L1R2[e][0], L1R2[e][1], L1R2[e][2], L1R2[e][3]);
                }


                dmaCopy(L1R2Tiles, bgGetGfxPtr(bg), L1R2TilesLen);
                dmaCopy(L1R2Map, bgGetMapPtr(bg), L1R2MapLen);  
                dmaCopy(L1R2Pal, BG_PALETTE, L1R2PalLen);  

                dmaCopy(L1R2Tiles, bgGetGfxPtr(bgSb), L1R2TilesLen);
                dmaCopy(L1R2Map, bgGetMapPtr(bgSb), L1R2MapLen);
                dmaCopy(L1R2Pal, BG_PALETTE_SUB, L1R2PalLen);
        break;
        }

        bgUpdate();
};

//**MAIN **//
int main(int argc, char *argv[]){
swiWaitForVBlank();
videoSetMode(MODE_1_2D);
videoSetModeSub(MODE_1_2D);

vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_LCD);

lcdMainOnBottom();
//Main = Bottom Screen, Sub = Top Screen
// !!**Graphic Initialization**!!
oamInit(&oamMain, SpriteMapping_1D_256, false);
oamInit(&oamSub, SpriteMapping_1D_256, false);
       
        //Establish Scenes, then run level set up at first scene
        sceneClass levelTest;
        levelTest.sceneInit(0, 1);
//Array name as string, can I use that string to refer to the array? Load array info into a new array? Use old system, but load position array based off of SceneID

        sceneClass levelQuiz;
        levelQuiz.sceneInit(1, 1);

        sceneClass cutsceneTest;
        cutsceneTest.sceneInit(2, 2);

levelSetup(levelTest);

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

for (int i = 1; i <= 3; i++){
//collision test
oamSet(&oamMain, i,
        L1Ob[i-1][0], L1Ob[i-1][1],
        1,
        3,
        SpriteSize_32x32, SpriteColorFormat_256Color,
        gfxMain,
        1,
        false,
        false,
        false, false,
        false);
}

        while(true){ //This is just an infinite loop, until something stops it
        //Background Initalization
                bgSetScroll(bg, bg_x, bg_y);
                bgSetScroll(bgSb, bg_x, bg_y - 192);
        //Graphics manipulation
                oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
                for (int i = 1; i <= 3; i++){
                oamSetXY(&oamMain, i, L1Ob[i-1][0], L1Ob[i-1][1]);
                }
                kyHeld = keysHeld();

                if (kyHeld & KEY_LEFT){
                        levelSetup(levelQuiz);
                        printf("Changed Room!!");
                };
                graphicsUpdate();
    //flush visuals
        bgUpdate();
        //oamFreeGfx(&oamMain, gfxMain);
        consoleClear();
        swiWaitForVBlank();
        };
};
