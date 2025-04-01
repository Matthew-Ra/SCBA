#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>


#include "GooberTest.h"
#include "BeastieBall.h"
#include "Lv1Test.h"
#include "Lv1Test2.h"
#include "CollisionTest.h"
#include <nds/arm9/background.h>


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


int bg = 0;
int bgSb = 0;
int bg_x = -32;
int bg_y = -32;


uint16 coll_x = 20;
uint16 coll_y = 75;


// initialize variables
uint16_t kyHeld;
touchPosition touch_pos;


void positionInit(){


 cen_x = 128;
 cen_y = 100;

 bg_x = -32;
 bg_y = -32;


//angle calculation variables;
 hyp = 0;
 adj = 0;
 opp = 0;


 coll_x = 20;
 coll_y = 75;


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
                                if ( (inBetween(cen_y + 16, this->y1 - 8, this->y1 + 8)) or (inBetween(cen_y - 16, this->y2 - 8, this->y2 + 8))){
                                return(true);
                                }
                        } else return(false);
                } else return(false);
        };


        bool collisionHorizontal() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y1, this->y2)){
                                //CHANGE LINE BELOW TO POINT DIST!!!
                                if ( (inBetween(cen_x + 16, this->x2 , this->x2 + 32)) or (inBetween(cen_x + 16, this->x1, this->x1 + 8))){
                                return(true);
                                }
                        } else return(false);
                } else return(false);
        };
};


//established wall array as well as an array of coordinate points for the wall objects
wallClass walls1[3];


int Test1[2][4]{
        {0, 256, 0, 32},
        {32, 128, 32, 64}
};


int Test0[3][4]{
        {0, 256, 0, 32},
        {128, 256, 32, 128},
        {32, 160, 160, 224}
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


        int wallSize = (sizeof(walls1)/sizeof(walls1[0])) - 1;


                for (int i = 0; i <= wallSize; i++){
                        walls1[i].x1 += adjacentSpeed;
                        walls1[i].x2 += adjacentSpeed;


                        walls1[i].y1 += oppositeSpeed;
                        walls1[i].y2 += oppositeSpeed;


                        if (walls1[i].collisionVertical()) { //CANCEL movement if collision detected
                                bg_y += oppositeSpeed;
                                coll_y -= oppositeSpeed;
                                for (int w = 0; w <= wallSize; w++){
                                        walls1[w].y1 -= oppositeSpeed;
                                        walls1[w].y2 -= oppositeSpeed;
                                };
                        };


                        if (walls1[i].collisionHorizontal()) { //CANCEL movement if collision detected
                                bg_x += adjacentSpeed;
                                coll_x -= adjacentSpeed;
                                for (int w = 0; w <= wallSize; w++){
                                        walls1[w].x1 -= adjacentSpeed;
                                        walls1[w].x2 -= adjacentSpeed;
                                };
                        };
                };
        };


        //Refresh visuals
        bgUpdate();
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
        int bg = bgInit(0,BgType_Text8bpp, BgSize_T_256x256, 0, 1);
        int bgSb = bgInitSub(0,BgType_Text8bpp, BgSize_T_256x256, 0, 1);
        //What needs to be added?


//Which set of walls should be loaded?
        switch(scene.sceneID){
        case 0:
                for (int w = 0; w <= (sizeof(Test0)/sizeof(Test0[0])); w++){
                        walls1[w].wallPoints(Test0[w][0], Test0[w][1], Test0[w][2], Test0[w][3]);
                }              


                dmaCopy(Lv1Test2Tiles, bgGetGfxPtr(bg), Lv1Test2TilesLen);
                dmaCopy(Lv1Test2Map, bgGetMapPtr(bg), Lv1Test2MapLen);
                dmaCopy(Lv1Test2Pal, BG_PALETTE, Lv1Test2PalLen);


                dmaCopy(Lv1Test2Tiles, bgGetGfxPtr(bgSb), Lv1Test2TilesLen);
                dmaCopy(Lv1Test2Map, bgGetMapPtr(bgSb), Lv1Test2MapLen);
                dmaCopy(Lv1Test2Pal, BG_PALETTE_SUB, Lv1Test2PalLen);
        break;
        case 1:


                for (int e = 0; e <= (sizeof(Test1)/sizeof(Test1[0])); e++){
                        walls1[e].wallPoints(Test1[e][0], Test1[e][1], Test1[e][2], Test1[e][3]);
                }


                dmaCopy(Lv1TestTiles, bgGetGfxPtr(bg), Lv1TestTilesLen);
                dmaCopy(Lv1TestMap, bgGetMapPtr(bg), Lv1TestMapLen);  
                dmaCopy(Lv1TestPal, BG_PALETTE, Lv1TestPalLen);  

//add bg variable to scene and have that read in the way bg were preivously loaded
                dmaCopy(Lv1TestTiles, bgGetGfxPtr(bgSb), Lv1TestTilesLen);
                dmaCopy(Lv1TestMap, bgGetMapPtr(bgSb), Lv1TestMapLen);
                dmaCopy(Lv1TestPal, BG_PALETTE_SUB, Lv1TestPalLen);
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

consoleDemoInit();
lcdMainOnBottom();
//Main = Bottom Screen, Sub = Top Screen
// !!**Graphic Initialization**!!
oamInit(&oamMain, SpriteMapping_1D_32, false);
oamInit(&oamSub, SpriteMapping_1D_32, false);
       
        //Establish Scenes, then run level set up at first scene
        sceneClass levelTest;
        levelTest.sceneInit(0, 1);
//Array name as string, can I use that string to refer to the array? Load array info into a new array? Use old system, but load position array based off of SceneID


        sceneClass levelQuiz;
        levelQuiz.sceneInit(1, 1);


levelSetup(levelTest);


//Initialize Collision MAIN Data
int Col = bgInit(3,BgType_Rotation, BgSize_R_256x256, 1, 2);
dmaCopy(CollTestTiles, bgGetGfxPtr(Col), CollTestTilesLen);
dmaCopy(CollTestMap, bgGetMapPtr(Col), CollTestMapLen);


//Initialize Collision SUB Data
int ColSb = bgInitSub(3,BgType_Rotation, BgSize_R_256x256, 1, 3);
dmaCopy(CollTestTiles, bgGetGfxPtr(ColSb), CollTestTilesLen);
dmaCopy(CollTestMap, bgGetMapPtr(ColSb), CollTestMapLen);


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


        while(true){ //This is just an infinite loop, until something stops it
                swiWaitForVBlank();
        //Background Initalization
                bgSetScroll(bg, bg_x, bg_y);
                bgSetScroll(bgSb, bg_x, bg_y - 192);
                bgSetScroll(Col, bg_x/2, bg_y/2);
        //Graphics manipulation
                oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
                oamSetXY(&oamMain, 1, coll_x, coll_y);
                kyHeld = keysHeld();


                if (kyHeld & KEY_LEFT){
                        levelSetup(levelQuiz);
                };
                graphicsUpdate();
    //flush visuals
        bgUpdate();
        oamFreeGfx(&oamMain, gfxMain);
        consoleClear();
        };
};
