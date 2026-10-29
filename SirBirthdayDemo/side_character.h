#pragma once

#ifndef _SIDE_CHARACTER_H_
#define _SIDE_CHARACTER_H_

// COLOR PALETTE CONSTANTS FOR DARBARI COURT ROBES

#define DARBARI_COLOR_SAFFRON_GOLD    0  // Royal Saffron & Gold Silk (Classic)
#define DARBARI_COLOR_PEARL_WHITE     1  // Pure Silk White & Pearl
#define DARBARI_COLOR_SKY_BLUE        2  // Turquoise & Sky Blue
#define DARBARI_COLOR_ROYAL_NAVY      3  // Deep Royal Navy Blue & Crimson Turban
#define DARBARI_COLOR_EMERALD_GREEN   4  // Regal Emerald Green
#define DARBARI_COLOR_CRIMSON_RED     5  // Imperial Crimson Red & Gold
#define DARBARI_COLOR_VIOLET_PURPLE   6  // Sovereign Violet & Purple


// Renders soldier with customizable rotation and spear grip hand
// Parameters:
//   - xPosition             : World X coordinate
//   - yPosition             : World Y coordinate
//   - zPosition             : World Z coordinate
//   - scaleX, scaleY, scaleZ: Non-uniform scaling factors
//   - rotationAngleYDegrees : Facing angle rotation around vertical Y-axis in degrees
//   - bHoldSpearInRightHand : 1 = Spear held in right hand, 0 = Spear held in left hand
void rlDrawSoliderEx(float xPosition, float yPosition, float zPosition,
                     float scaleX, float scaleY, float scaleZ,
                     float rotationAngleYDegrees,
                     int bHoldSpearInRightHand);

// Renders courtier with customizable rotation and robe color scheme (standing posture)
// Parameters:
//   - xPosition             : World X coordinate
//   - yPosition             : World Y coordinate
//   - zPosition             : World Z coordinate
//   - scaleX, scaleY, scaleZ: Non-uniform scaling factors
//   - rotationAngleYDegrees : Facing angle rotation around vertical Y-axis in degrees
//   - robeColorIndex        : 0 to 6 (see DARBARI_COLOR_* constants above)
void rlDreawDarbariEx(float xPosition, float yPosition, float zPosition,
                      float scaleX, float scaleY, float scaleZ,
                      float rotationAngleYDegrees,
                      int robeColorIndex);

#endif // _SIDE_CHARACTER_H_
