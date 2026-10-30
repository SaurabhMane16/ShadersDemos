#ifndef SCENE2_H
#define SCENE2_H

// =============================================================================
// SCENE 2: ROYAL DARBAR & CHANAKYA ENTRY
// Doors swing open, and Chanakya walks inside to the center of the court.
// =============================================================================
#define SCENE2_DURATION 14.0f

void initScene2(void);
void renderScene2(void);
void updateScene2(void);

// Cinematic Front-View Dialogue Shots (King's Perspective with Full Hall Environment)
void renderChanakyaNormalShot(void);
void renderChanakyaAngryShot(void);

#endif // SCENE2_H
