// This header file helps to convert box2d coordinates into local framework coordinates.

// Header guard.
#ifndef _BOX2D_CONVERSIONS_H
#define _BOX2D_CONVERSIONS_H

#define DISPLAY_WIDTH				1280
#define DISPLAY_HEIGHT				720

// To convert the Box2D coordinates to framework coordinates.
#define BOX2D_FRAMEWORK_SCALE						100.0f
#define BOX2D_FRAMEWORK_OFFSET_X					0.0f
#define BOX2D_FRAMEWORK_OFFSET_Y					0.0f
#define BOX2D_FRAMEWORK_SIZE_OFFSET					0.5f
#define BOX2D_FRAMEWORK_DYNAMIC_CIRCLE_SIZE			0.3f

// To convert the Box2D coordinates into framework coordinates.
#define BOX2D_FRAMEWORK_SIZE(s) ((s)*BOX2D_FRAMEWORK_SCALE)
#define BOX2D_FRAMEWORK_POS_X(x) (((x)*BOX2D_FRAMEWORK_SCALE) + BOX2D_FRAMEWORK_OFFSET_X)
#define BOX2D_FRAMEWORK_POS_Y(y) (DISPLAY_HEIGHT - (((y)*BOX2D_FRAMEWORK_SCALE) + BOX2D_FRAMEWORK_OFFSET_Y))

// To convert the framework coordinates to Box2D coordinates.
#define FRAMEWORK_BOX2D_SIZE(s) ((s) / BOX2D_FRAMEWORK_SCALE)
#define FRAMEWORK_BOX2D_POS_X(x) (((x) - BOX2D_FRAMEWORK_OFFSET_X)/BOX2D_FRAMEWORK_SCALE)
#define FRAMEWORK_BOX2D_POS_Y(y) (((y) - DISPLAY_HEIGHT+BOX2D_FRAMEWORK_OFFSET_Y)/-BOX2D_FRAMEWORK_SCALE)


#endif