//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// rTexpacker v5.0 Atlas Descriptor Code exporter v5.0                          //
//                                                                              //
// more info and bugs-report:  github.com/raylibtech/rtools                     //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2019-2025 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#ifndef BLOCKS_ATLAS_H
#define BLOCKS_ATLAS_H

#define ATLAS_ATLAS_IMAGE_PATH      "atlas.png"
#define ATLAS_ATLAS_SPRITE_COUNT    2

// Atlas sprite properties
typedef struct rtpAtlasSprite {
    const char *nameId;
    const char *tag;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
    int colliderType;
    int colliderPosX, colliderPosY, colliderSizeX, colliderSizeY;
} rtpAtlasSprite;

// Atlas sprites array
static rtpAtlasSprite rtpDescAtlas[2] = {
    { "dyrt", "", 0, 0, 0, 0, 32, 32, 0, false, 0, 0, 32, 32, 0, 0, 0, 0, 0 },
    { "ston", "", 0, 0, 32, 0, 32, 32, 0, false, 0, 0, 32, 32, 0, 0, 0, 0, 0 },
};

#endif // BLOCKS_ATLAS_H
