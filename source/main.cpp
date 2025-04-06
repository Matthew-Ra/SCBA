#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>
#include <nds/arm9/background.h>

#include "RunStartup.h"
#include "GoopObstacle.h"
#include "L1R1.h"
#include "L1R2.h"
#include "CollisionTest.h"
#include "LvSelect.h"




using namespace std;
/*
class screenPoint{
public:

};

class backgroundPoint
*/

int screenBgOffsetX = 0;
int screenBgOffsetY = 0;

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

//Center screen variables
uint16 cen_x = 128;
uint16 cen_y = 100;

//background ids and position
int bg = 0;
int bgMenu = 0;
int bgSb = 0;
int bg_x = -32;
int bg_y = 32;

// initialize variables
uint16_t kyHeld;
touchPosition touch_pos;

int menuCol[3][4]{
        {48, 207, 32, 79},
        {48, 207, 96, 143},
        {48, 207, 160, 207}
};
int menuColSize = (sizeof(menuCol)/sizeof(menuCol[0]) - 1);


//Collision and obstacle coordinates
int L1R1[16][4]{
        {319, 383, 832, 1024},
        {608, 656, 800, 1024},
        {512, 680, 864, 927},
        {256, 383, 832, 864},
        {544, 638, 736, 800},
        {256, 287, 480, 830},
        {352, 415, 576, 767},//Middle Island //
        {415, 447, 704, 767}, //
        {415, 447, 576, 639}, //
        {512, 544, 544, 767}, // Right wall middle
        {544, 575, 320, 575}, // Right tall wall top 2
        {256, 447, 480, 511}, 
        {416, 447, 224, 512},
        {416, 608, 224, 255},
        {576, 607, 0 , 255},
        {736, 767, 0 , 352}
};
int L1R1size = (sizeof(L1R1)/sizeof(L1R1[0])) - 1;

int L1R1Obj[11][2]{
        {400, 976},
        {464, 964},
        {496, 964},
        {304, 592},
        {496, 688},
        {528, 432},
        {496, 336},
        {688, 305},
        {720, 271},
        {624, 176},
        {688, 112}
};


int L1R2[16][4]{
        {576, 607, 832, 1024},
        {736, 768, 704, 1024},
        {352, 607, 832, 863}, //
        {512, 767, 704, 735},
        {352, 383, 768, 863},
        {256, 383, 768, 800},//
        {256, 288, 608, 800},
        {352, 383, 224, 639},
        {96, 352, 832, 863}, //?
        {512, 544, 352, 735},
        {511, 767, 352, 383},
        {736, 767, 224, 255},
        {480, 512, 224, 383},
        {608, 640, 0, 255},
        {704, 735, 0, 255}
};
int L1R2size = (sizeof(L1R2)/sizeof(L1R2[0])) - 1;


void positionInit(){

 cen_x = 128;
 cen_y = 100;
 
 bg_x = -32;
 bg_y = 32;


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
       int wallPoints(int x , int xx, int y, int yy) {
        this->x1 = x; //left boundary of box
        this->x2 = xx + 32; //right boundary of box + offset
        this->y1 = y - 32; // Lower boundary of box
        this->y2 = yy; // Upper boundary of box

        return (0);
        };



        //Collision check
        bool collisionVertical() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y1, this->y2)){
                                if ( (inBetween(cen_y + 16, this->y1 - 8, this->y1 + 8)) or (inBetween(cen_y - 16, this->y2 - 8, this->y2 + 8))){
                                return(true);
                                } else return(true);
                        } else return(false);
                } else return(false);
        };


        bool collisionHorizontal() {
                if (inBetween(cen_x - 16, this->x1, this->x2)){
                        if (inBetween(cen_y + 16, this->y1, this->y2)){
                                //CHANGE LINE BELOW TO POINT DIST!!!
                                if ( (inBetween(cen_x + 16, this->x2 , this->x2 + 32)) or (inBetween(cen_x + 16, this->x1, this->x1 + 8))){
                                return(true);
                                } else return(true);
                        } else return(false);
                } else return(false);
        };

        bool collisionTouch(){
                if (inBetween(touch_pos.px, this->x1, this->x2)){
                        if (inBetween(touch_pos.py, this->y1, this->y2)){
                                return(true);
                        } else return(false);
                } else return(false);
        };
};


//established wall array as well as an array of coordinate points for the wall objects
wallClass walls1[16];
int objData[30][2];

void angleCalculation() {
//get hypotenuse length with point dist
        hyp = pointDist(cen_x, cen_y, touch_pos.px, touch_pos.py);
//get x distance with Xpos - touch_pos.px
        adj = touch_pos.px - cen_x;
//gets y distance for movement
        opp = touch_pos.py - cen_y;
//Calculate angle a -> INVcos(x_dis/hypLen)
//Speed vector at a starting at center
if (hyp * 1.0 != 0){
        ang = acos(adj/(hyp * 1.0));
} else ang = 0;
        ang_rad = degreesToAngle(ang*(180/M_PI) - 90);

};


void graphicsUpdate() {
    s32 adjacentSpeed = (adj/15);
    s32 oppositeSpeed = (opp/15);


//**Enemy Collision check**
for (int i = 0; i <= 29; i++){
        if (pointDist(objData[i][0] + 32, objData[i][1] - 32, cen_x, cen_y) <= 16){
                if (abs(adjacentSpeed) >= 1){
                    adjacentSpeed /= 2;
                };
                if (abs(oppositeSpeed) >= 1){
                        oppositeSpeed /= 2;
                }
        };
};
        // !! Detect Touch Input !!
        if (kyHeld & KEY_TOUCH){
                touchRead(&touch_pos);
                angleCalculation();


//BACKGROUND Movement
        bg_x -= adjacentSpeed;

        bg_y -= oppositeSpeed;
        for (int e = 0; e <= 29; e++){
               objData[e][0] += adjacentSpeed; //objects x
               objData[e][1] += oppositeSpeed; //objects y
        }

        int wallSize = (sizeof(walls1)/sizeof(walls1[0])) - 1;
                for (int i = 0; i <= wallSize; i++){
                        
                        walls1[i].x1 += adjacentSpeed;
                        walls1[i].x2 += adjacentSpeed;


                        walls1[i].y1 += oppositeSpeed;
                        walls1[i].y2 += oppositeSpeed;
                        

                        if (walls1[i].collisionVertical()) { //CANCEL movement if collision detected
                                bg_y += oppositeSpeed;
                                for (int e = 0; e <= 29; e++){//enemy array y position
                                        objData[e][1] -= oppositeSpeed; 
                                };

                                for (int w = 0; w <= wallSize; w++){
                                        walls1[w].y1 -= oppositeSpeed;
                                        walls1[w].y2 -= oppositeSpeed;
                                        
                                };
                        };


                        if (walls1[i].collisionHorizontal()) { //CANCEL movement if collision detected
                                bg_x += adjacentSpeed;
                                for (int e = 0; e <= 29; e++){
                                        objData[e][0] -= adjacentSpeed;
                                };

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
sceneClass currentScene;

void levelSetup(sceneClass scene) {
        positionInit();
        currentScene = scene;

        bg = bgInit(3,BgType_Rotation, BgSize_R_1024x1024, 0, 3);
        bgMenu = bgInit(0,BgType_Text8bpp, BgSize_T_256x256, 0, 1);
        
        bgSb = bgInitSub(3,BgType_Rotation, BgSize_R_1024x1024, 0, 3);
        int L1R1ObjSize = (sizeof(L1R1Obj)/sizeof(L1R1Obj)[0]) - 1;
        //int L1R2ObjSize = (sizeof(L1R2Obj)/sizeof(L1R2Obj)[0]) - 1;
//Which set of walls should be loaded?
        switch(scene.sceneID){
        case 0:
        //Put levels collision data in wall container
                for (int w = 0; w <= L1R1size; w++){
                        walls1[w].wallPoints(L1R1[w][0], L1R1[w][1], L1R1[w][2], L1R1[w][3]);
                }  
        //Put levels object data in object container
                for (int o = 0; o <= L1R1ObjSize; o++){
                        objData[o][0] = L1R1Obj[o][0];
                        objData[o][1] = L1R1Obj[o][1];
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
        case 2:
                for (int m = 0; m <= menuColSize; m++){
                        walls1[m].wallPoints(menuCol[m][0], menuCol[m][1], menuCol[m][2], menuCol[m][3]);
                }

                dmaCopy(LvSelectTiles, bgGetGfxPtr(bgMenu), LvSelectTilesLen);
                dmaCopy(LvSelectMap, bgGetMapPtr(bgMenu), LvSelectMapLen);  
                dmaCopy(LvSelectPal, BG_PALETTE, LvSelectPalLen);  
        break;
        }

        bgUpdate();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
};

void originOffset(int xOffset, int yOffset, sceneClass scene){
        positionInit();
        bg_x += xOffset;
        bg_y += yOffset;
        switch(scene.sceneID){
                case 0:
                for (int a = 0; a <= L1R1size; a++){
                        walls1[a].x1 -= xOffset;
                        walls1[a].x2 -= xOffset;

                        walls1[a].y1 -= yOffset;
                        walls1[a].y2 -= yOffset;
                };
                break ;
                case 1:
                for (int b = 0; b <= L1R2size; b++){
                        walls1[b].x1 -= xOffset;
                        walls1[b].x2 -= xOffset;

                        walls1[b].y1 -= yOffset;
                        walls1[b].y2 -= yOffset;
                };
                break;
                
                for (int ob = 0; ob <= 29; ob++){
                        objData[ob][0] -= xOffset;
                        objData[ob][1] -= yOffset;
                }
                
        }; 
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
oamInit(&oamMain, SpriteMapping_1D_32, false);
oamInit(&oamSub, SpriteMapping_1D_32, false);
       
        //Establish Scenes, then run level set up at first scene
        sceneClass levelTest;
        levelTest.sceneInit(0, 1);

        sceneClass levelQuiz;
        levelQuiz.sceneInit(1, 1);

        sceneClass levelSelect;
        levelSelect.sceneInit(2, 0);

        //collTouch -> Check each of the 3 individual collision sets; if walls1[0].collTouch -> go to levelTest

levelSetup(levelSelect);

//Set aside space for sprite and copy tile and pallete info to main engine
u16 *objMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
dmaCopy(GoopObstacleTiles, objMain, GoopObstacleTilesLen);
dmaCopy(GoopObstaclePal, SPRITE_PALETTE, GoopObstaclePalLen);


u16 *plyrMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
dmaCopy(RunStartupTiles, plyrMain, RunStartupTilesLen);
dmaCopy(RunStartupPal, SPRITE_PALETTE, RunStartupPalLen);

int objDataSize = (sizeof(objData)/sizeof(objData)[0]) - 1;

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

for (int i = 1; i <= objDataSize; i++){
//collision test
oamSet(&oamMain, i,
        objData[i-1][0] , objData[i-1][1],
        0,
        3,
        SpriteSize_32x32, SpriteColorFormat_256Color,
        objMain,
        1,
        false,
        false,
        false, false,
        false);
}

//originOffset(485, 885, levelTest);

        while(true){ //This is just an infinite loop, until something stops it

                //Check for level select id
                if (currentScene.sceneID == 2){
                        if (walls1[0].collisionTouch()){
                                bgClearControlBits(bgMenu, REG_BG0CNT);
                                levelSetup(levelTest);

                        }
                        if (walls1[1].collisionTouch()){
                                bgClearControlBits(bgMenu, REG_BG0CNT);
                                levelSetup(levelQuiz);

                        } 
                }


                swiWaitForVBlank();
                screenBgOffsetX = REG_BG3HOFS;
                screenBgOffsetY = REG_BG3VOFS;
                //Background Initalization
                bgSetScroll(bg, bg_x, bg_y);
                bgSetScroll(bgSb, bg_x, bg_y - 192);
        //Graphics manipulation
                oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
                for (int i = 1; i <= objDataSize; i++){
                oamSetXY(&oamMain, i, objData[i-1][0] + screenBgOffsetX, objData[i-1][1] - screenBgOffsetY);
                }
                kyHeld = keysHeld();

                if (kyHeld & KEY_LEFT){
                        levelSetup(levelQuiz);
                };
                graphicsUpdate();
        //Refresh visuals
        bgUpdate();
        scanKeys();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);

        };
};
