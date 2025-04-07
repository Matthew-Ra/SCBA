#include <stdio.h>
#include <math.h>
#include <nds.h>
#include <gl2d.h>
#include <vector>
#include <nds/arm9/background.h>

#include "RunStartup.h"
#include "GoopObstacle.h"
#include "L1R1.h"
#include "L1R2.h"
#include "L1R3.h"
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

float pointDist(int x1, int y1, int x2, int y2) {
    int ay = y2 - y1;
    int ax = x2 - x1;
    int r = sqrt32(pow(ax, 2) + pow(ay, 2));
    return (r);
}


bool inBetween(int x, int lowR, int highR) {
    return x >= lowR && x <= highR;
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
const uint16 cen_x = 128;
const uint16 cen_y = 100;

// Where the player is on the map
uint16 pos_x = 0;
uint16 pos_y = 0;

//background ids and position
int bg = 0;
int bgMenu = 0;
int bgSb = 0;
int bg_x = 0;
int bg_y = 0;

// initialize variables
uint16_t kyHeld;
uint16_t kyUp;
touchPosition touch_pos;

int menuCol[3][4]{{48, 207, 32,  79},
                  {48, 207, 96,  143},
                  {48, 207, 160, 207}};
int menuColSize = (sizeof(menuCol) / sizeof(menuCol[0])) - 1;


//Collision and obstacle coordinates
int L1R1[17][4]{{383, 608, 1015,1024},
                {319, 383, 832, 1024},
                {608, 656, 800, 1024},
                {512, 680, 864, 927},
                {256, 383, 832, 864},
                {544, 638, 736, 800},
                {256, 287, 480, 830},
                {352, 415, 576, 767},//Middle Island //
                {415, 447, 704, 767},
                {415, 447, 576, 639},
                {512, 544, 544, 767}, // Right wall middle
                {544, 767, 320, 575}, // Right tall wall top 2
                {256, 447, 480, 511},
                {416, 447, 224, 512},
                {416, 608, 224, 255},
                {576, 607, 0,   255},
                {736, 767, 0,   352}};
int L1R1size = (sizeof(L1R1) / sizeof(L1R1[0])) - 1;

int L1R1Obj[10][2]{{400, 976},
                   {496, 964},
                   {304, 592},
                   {496, 660},
                   {528, 432},
                   {496, 336},
                   {688, 305},
                   {720, 271},
                   {624, 176},
                   {688, 112}};


int L1R2[16][4]{{608, 735, 1015,1024},
                {576, 607, 832, 1024},
                {736, 768, 704, 1024},
                {352, 607, 832, 863},
                {512, 767, 704, 735},
                {352, 383, 768, 863},
                {256, 383, 768, 800},
                {256, 288, 608, 800},
                {352, 383, 224, 639},
                {352, 639, 224, 255},
                {96,  352, 832, 863},
                {512, 544, 352, 735},
                {512, 767, 352, 383},
                {736, 767, 224, 383},
                {608, 640, 0,   255},
                {704, 735, 0,   255}};
int L1R2size = (sizeof(L1R2) / sizeof(L1R2[0])) - 1;

int L1R2Obj[15][2]{{624, 913},
                   {656, 880},
                   {592, 816},
                   {528, 753},
                   {464, 720},
                   {496, 689},
                   {384, 704},
                   {400, 594},
                   {400, 562},
                   {464, 498},
                   {448, 370},
                   {464, 274},
                   {528, 338},
                   {624, 274},
                   {688, 210}
                };

int L1R3[21][4]{{512, 608, 1015,1024},
                {448, 512, 768, 1024},
                {608, 703, 512, 1024},
                {32, 448, 864, 895},
                {224, 287, 575, 767},
                {32, 63, 0, 864},
                {224, 607, 576 , 639},
                {64, 864, 320, 383},
                {576, 607, 512, 576}, //the little one at the bottom
                {576, 703, 383, 447},
                {703, 864, 383, 415},
                {832, 864, 415, 575},
                {704, 991, 704, 735},
                {960, 991, 32, 735},
                {512, 991, 32, 63},
                {512, 735, 32, 127},
                {864, 895, 160, 575},
                {832, 864, 160, 320},
                {512, 575, 192, 255},
                {192, 415, 160,255},
                {192, 543, 0,63}
        };
int L1R3size = (sizeof(L1R3) / sizeof(L1R3[0])) - 1;

int L1R3Obj[27][2]{{560, 689},
                   {432, 786},
                   {400, 820},
                   {496, 660},
                   {368, 850},
                   {207, 786},
                   {112, 722},
                   {112, 496},
                   {208, 549},
                   {688, 112},
                   {144, 446},
                   {240, 562},
                   {272, 530},
                   {305, 530},
                   {400, 498},
                   {496, 466},
                   {720, 530},
                   {944, 498},
                   {912, 339},
                   {848, 82},
                   {784, 210},
                   {624, 178},
                   {304, 114},
                   {400, 147},
                   {368, 307},
                   {272, 274},
                   {208, 82}
                };

void positionInit() {

    pos_x = 0;
    pos_y = 0;

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

    wallClass(int x, int xx, int y, int yy) {
        this->x1 = x; //left boundary of box
        this->x2 = xx; //right boundary of box + offset
        this->y1 = y; // Lower boundary of box
        this->y2 = yy; // Upper boundary of box
    };


    //Collision check
    bool collisionVertical() {
        // Check in y bounds of rect
        return inBetween(pos_y, this->y1, this->y2);
    };


    bool collisionHorizontal() {
        // Check in x bounds of rect
        return inBetween(pos_x, this->x1, this->x2);
    };

    bool collisionTouch() {
        if (inBetween(touch_pos.px, this->x1, this->x2)) {
            if (inBetween(touch_pos.py, this->y1, this->y2)) {
                return (true);
            } else return (false);
        } else return (false);
    };
};

class objectClass{
        public:
        int x;
        int y;
        int id;
                objectClass(int h, int v, int identifier){
                        this->x = h;
                        this->y = v;
                        this->id = identifier;
                }
};


//established wall array as well as an array of coordinate points for the wall objects
//wallClass walls1[16]
std::vector <wallClass> walls1;
std::vector <objectClass> objData;

void angleCalculation() {
    //get hypotenuse length with point dist
    hyp = pointDist(cen_x, cen_y, touch_pos.px, touch_pos.py);
    //get x distance with Xpos - touch_pos.px
    adj = touch_pos.px - cen_x;
    //gets y distance for movement
    opp = touch_pos.py - cen_y;
    //Calculate angle a -> INVcos(x_dis/hypLen)
    //Speed vector at a starting at center
    if (hyp * 1.0 != 0) {
        ang = acos(adj / (hyp * 1.0));
    } else ang = 0;
    ang_rad = degreesToAngle(ang * (180 / M_PI) - 90);

};


void graphicsUpdate() {
    // !! Detect Touch Input !!
    if (kyHeld & KEY_TOUCH) {
        touchRead(&touch_pos);
        angleCalculation();

        s32 adjacentSpeed = (adj / 15);
        s32 oppositeSpeed = (opp / 15);


//**Enemy Collision check**
        for (auto obj: objData) {
            if (pointDist(obj.x, obj.y, pos_x, pos_y) <= 32) {
                adjacentSpeed *= 0.60;
                oppositeSpeed *= 0.60;

            };
        };


//BACKGROUND Movement
      //  bool hCollision = false;
        // bool vCollision = false;
        bg_x -= adjacentSpeed;
        pos_x -= adjacentSpeed;

        bg_y -= oppositeSpeed;
        pos_y -= oppositeSpeed;
        for (auto obj: objData) {
            obj.x += adjacentSpeed; //objects x
            obj.y += oppositeSpeed; //objects y
        }

        for (auto wall: walls1) {
            if (wall.collisionHorizontal() && wall.collisionVertical()) {
                bg_y += oppositeSpeed;
                pos_y += oppositeSpeed;
                bg_x += adjacentSpeed;
                pos_x += adjacentSpeed;
                break;
            }
            for (auto obj: objData) {
                obj.x -= adjacentSpeed;
                obj.y -= oppositeSpeed;
            };

        };
    };
};


class sceneClass {
public:
    int sceneID;   //Unique Scene Identifier
    int sceneType; //0 = Menu, 1 = Level, 2 = Cutscene
    //Level Data
    char wallArray;


    void sceneInit(int ID, int type) {
        this->sceneID = ID;
        this->sceneType = type;
    }


    void levelInit(char array) {
        this->wallArray = array;
    }
};

sceneClass currentScene;

void levelSetup(sceneClass scene) {
    positionInit();
    walls1.clear();
    objData.clear();
    currentScene = scene;

    bg = bgInit(3, BgType_Rotation, BgSize_R_1024x1024, 0, 3);
    bgMenu = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

    bgSb = bgInitSub(3, BgType_Rotation, BgSize_R_1024x1024, 0, 3);
    int L1R1ObjSize = (sizeof(L1R1Obj) / sizeof (L1R1Obj)[0]) - 1;
    int L1R2ObjSize = (sizeof(L1R2Obj)/sizeof(L1R2Obj)[0]) - 1;
    int L1R3ObjSize = (sizeof(L1R3Obj)/sizeof(L1R3Obj)[0]) - 1;
    //Which set of walls should be loaded?
    switch (scene.sceneID) {
        case 0:
        //LEVEL 1
            //Put levels collision data in wall container
            for (int w = 0; w <= L1R1size; w++) {
                walls1.push_back(wallClass(L1R1[w][0], L1R1[w][1], L1R1[w][2], L1R1[w][3]));
            }
            //Put levels object data in object container
        for (int o = 0; o <= L1R1ObjSize; o++){
                objData.push_back(objectClass(L1R1Obj[o][0], L1R1Obj[o][1], o + 1));
            }

            dmaCopy(L1R1Tiles, bgGetGfxPtr(bg), L1R1TilesLen);
            dmaCopy(L1R1Map, bgGetMapPtr(bg), L1R1MapLen);
            dmaCopy(L1R1Pal, BG_PALETTE, L1R1PalLen);

            dmaCopy(L1R1Tiles, bgGetGfxPtr(bgSb), L1R1TilesLen);
            dmaCopy(L1R1Map, bgGetMapPtr(bgSb), L1R1MapLen);
            dmaCopy(L1R1Pal, BG_PALETTE_SUB, L1R1PalLen);
        break;
        case 1:
        //LEVEL 2
            for (int e = 0; e <= L1R2size; e++) {
                walls1.push_back(wallClass(L1R2[e][0], L1R2[e][1], L1R2[e][2], L1R2[e][3]));
            }
            for (int p = 0; p <= L1R2ObjSize; p++){
                objData.push_back(objectClass(L1R2Obj[p][0], L1R2Obj[p][1], p + 1));
            }


            dmaCopy(L1R2Tiles, bgGetGfxPtr(bg), L1R2TilesLen);
            dmaCopy(L1R2Map, bgGetMapPtr(bg), L1R2MapLen);
            dmaCopy(L1R2Pal, BG_PALETTE, L1R2PalLen);

            dmaCopy(L1R2Tiles, bgGetGfxPtr(bgSb), L1R2TilesLen);
            dmaCopy(L1R2Map, bgGetMapPtr(bgSb), L1R2MapLen);
            dmaCopy(L1R2Pal, BG_PALETTE_SUB, L1R2PalLen);
        break;
        case 2:
            for (int m = 0; m <= menuColSize; m++) {

                walls1.push_back(wallClass(menuCol[m][0], menuCol[m][1], menuCol[m][2], menuCol[m][3]));
            }

            dmaCopy(LvSelectTiles, bgGetGfxPtr(bgMenu), LvSelectTilesLen);
            dmaCopy(LvSelectMap, bgGetMapPtr(bgMenu), LvSelectMapLen);
            dmaCopy(LvSelectPal, BG_PALETTE, LvSelectPalLen);
        break;
        case 3:
        // LEVEL 3
        for (int agh = 0; agh <= L1R3size; agh++) {
                walls1.push_back(wallClass(L1R3[agh][0], L1R3[agh][1], L1R3[agh][2], L1R3[agh][3]));
            }
        for (int bee = 0; bee <= L1R3ObjSize; bee++){
                objData.push_back(objectClass(L1R3Obj[bee][0], L1R3Obj[bee][1], bee + 1));
            }
        dmaCopy(L1R3Tiles, bgGetGfxPtr(bg), L1R3TilesLen);
        dmaCopy(L1R3Map, bgGetMapPtr(bg), L1R3MapLen);
        dmaCopy(L1R3Pal, BG_PALETTE, L1R3PalLen);

        dmaCopy(L1R3Tiles, bgGetGfxPtr(bgSb), L1R3TilesLen);
        dmaCopy(L1R3Map, bgGetMapPtr(bgSb), L1R3MapLen);
        dmaCopy(L1R3Pal, BG_PALETTE_SUB, L1R3PalLen);
        break;
    }
/*
    bgUpdate();
    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
*/
};

void originOffset(int xOffset, int yOffset, sceneClass scene) {
    positionInit();
    bg_x = xOffset;
    bg_y = yOffset;

    pos_x = xOffset + cen_x;
    pos_y = yOffset + cen_y;

    /*switch(scene.sceneID){
            case 0:
            for (int a = 0; a <= L1R1size; a++){
                    walls1.at(a).x1 -= xOffset;
                    walls1.at(a).x2 -= xOffset;

                    walls1.at(a).y1 -= yOffset;
                    walls1.at(a).y2 -= yOffset;
            };
            break ;
            case 1:
            for (int b = 0; b <= L1R2size; b++){
                    walls1.at(b).x1 -= xOffset;
                    walls1.at(b).x2 -= xOffset;

                    walls1.at(b).y1 -= yOffset;
                    walls1.at(b).y2 -= yOffset;
            };
            break;

            for (int ob = 0; ob <= 29; ob++){
                    objData[ob][0] -= xOffset;
                    objData[ob][1] -= yOffset;
            }

    }; */
};

//**MAIN **//
int main(int argc, char *argv[]) {
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

    sceneClass levelSurvey;
    levelSurvey.sceneInit(3,1);

    //collTouch -> Check each of the 3 individual collision sets; if walls1[0].collTouch -> go to levelTest

    levelSetup(levelSelect);

    //Set aside space for sprite and copy tile and pallete info to main engine
    u16 *objMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(GoopObstacleTiles, objMain, GoopObstacleTilesLen);
    dmaCopy(GoopObstaclePal, SPRITE_PALETTE, GoopObstaclePalLen);

    u16 *plyrMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(RunStartupTiles, plyrMain, RunStartupTilesLen);
    dmaCopy(RunStartupPal, SPRITE_PALETTE, RunStartupPalLen);

    //graphics
    oamSet(&oamMain, 0, cen_x - 16, cen_y - 16, // Xoffset to center, Yoffset to center
           0, // Priority
           3, // Palette index
           SpriteSize_32x32, SpriteColorFormat_256Color, // Size, format
           plyrMain,  // Graphics offset
           0, // Affine index
           false, // Double size
           false, // Hide
           false, false, // H flip, V flip
           false); // Mosaic

    for (auto obj: objData) {
    //collision test
        oamSet(&oamMain, obj.id - 1, obj.x, obj.y, 
                0, 
                3, 
                SpriteSize_32x32, SpriteColorFormat_256Color,
                objMain,
                0, 
                false, false, 
                false, false,
                false);
    }

    while (true) { //This is just an infinite loop, until something stops it
        swiWaitForVBlank();
        kyUp = keysUp();

        //Check for level select id
if (kyUp & KEY_TOUCH){
        if (currentScene.sceneID == 2) {
            if (walls1.at(0).collisionTouch()) {
                levelSetup(levelTest);
                bgHide(bgMenu);
                originOffset(450, 885, levelTest);
            }
            if (walls1.at(1).collisionTouch()) {
                levelSetup(levelQuiz);
                bgHide(bgMenu);
                originOffset(500, 885, levelQuiz);
            }
            if (walls1.at(2).collisionTouch()) {
                levelSetup(levelSurvey);
                bgHide(bgMenu);
                originOffset(450, 885, levelSurvey);
            }
        }
}


        //Background Initalization
        bgSetScroll(bg, bg_x, bg_y);
        bgSetScroll(bgSb, bg_x, bg_y - 192);

        screenBgOffsetX = REG_BG3X;
        screenBgOffsetY = REG_BG3Y;
        //Graphics manipulation
        //PlayerROtation
        oamRotateScale(&oamMain, 0, -ang_rad, scale, scale);
        for (auto obj: objData) {
            oamSetXY(&oamMain, obj.id, obj.x , obj.y);
        }
        kyHeld = keysHeld();

        if (kyHeld & KEY_LEFT) {
            levelSetup(levelQuiz);
        };
        graphicsUpdate();
        //check if player has exited the level
        if (pos_y <= 0 || pos_y >= 60000){
                levelSetup(levelSelect);
                bgHide(bg);
        }


        //Refresh visuals
        bgUpdate();
        scanKeys();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    };
};