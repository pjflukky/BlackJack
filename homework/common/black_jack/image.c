/**
 * @file image.c
 * @author Pakorn Jantacumma
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "image.h"
 #include "black_jack_images.h"

/**
 * @brief 
 * Initializes image_t pointer based on the card suit provided  in img_type.
 *
 *  Set the width of the image based on the image_type_t passed in
 *  Set the height of the image based on the image_type_t passed in
 *  Set the fcolor to red if the image type is a HEART or DIAMOND 
 *  Set the fcolor to black if the image type is a CLUB or SPADE
 *  Set the fcolor to blue if the image type is BET_SCREEN OR START_SCREEN 
 *  Set the bcolor to white for images associated with cards. 
 *  Set the bcolor to black for images associated with splash screens. 
 * @param img_type
 * The type of image is used to identify which image is being requested 
 * @param image 
 * Pointer to the image information
 * @return true
 * A valid Image was found 
 * @return false 
 * No Image found
 */
 bool image_get_info(image_type_t img_type, image_t *image)
 {

   switch (img_type)
   {
   // HEART CASE: Set width, height, fcolor, bcolor, and bitmap
   case IMAGE_TYPE_HEART:
      image->width = IMAGE_PIXELS_WIDTH_HEART;
      image->height = IMAGE_PIXELS_HEIGHT_HEART;
      image->fcolor = 0xF800; // red color
      image->bcolor = 0xFFFF; // white
      image->bitmap = IMAGE_BITMAP_HEART;
      break;
   
   // DIAMOND CASE: Set width, height, fcolor, bcolor, and bitmap
   case IMAGE_TYPE_DIAMOND:
      image->width = IMAGE_PIXELS_WIDTH_DIAMOND;
      image->height = IMAGE_PIXELS_HEIGHT_DIAMOND;
      image->fcolor = 0xF800; // red color
      image->bcolor = 0xFFFF; // white
      image->bitmap = IMAGE_BITMAP_DIAMOND;
      break;
   
   // CLUB CASE: Set width, height, fcolor, bcolor, and bitmap
   case IMAGE_TYPE_CLUB:
      image->width = IMAGE_PIXELS_WIDTH_CLUB;
      image->height = IMAGE_PIXELS_HEIGHT_CLUB;
      image->fcolor = 0x0000; // black color
      image->bcolor = 0xFFFF; // white
      image->bitmap = IMAGE_BITMAP_CLUB;
      break;
   
   // SPADE CASE: Set width, height, fcolor, bcolor, and bitmap
   case IMAGE_TYPE_SPADE:
      image->width = IMAGE_PIXELS_WIDTH_SPADE;
      image->height = IMAGE_PIXELS_HEIGHT_SPADE;
      image->fcolor = 0x0000; // black color
      image->bcolor = 0xFFFF; // white
      image->bitmap = IMAGE_BITMAP_SPADE;
      break;
      
   // START SCREEN CASE
   case IMAGE_TYPE_START_SCREEN:
      image->width = IMAGE_PIXELS_WIDTH_START_SCREEN;
      image->height = IMAGE_PIXELS_HEIGHT_START_SCREEN;
      image->fcolor = 0x001F; // blue color
      image->bcolor = 0x0000; // black
      image->bitmap = IMAGE_BITMAP_START_SCREEN;
      break;
   
    // BET SCREEN CASE
   case IMAGE_TYPE_BET_SCREEN:
      image->width = IMAGE_PIXELS_WIDTH_BET_SCREEN;
      image->height = IMAGE_PIXELS_HEIGHT_BET_SCREEN;
      image->fcolor = 0x001F; // blue color
      image->bcolor = 0x0000; // black
      image->bitmap = IMAGE_BITMAP_START_SCREEN;
      break;

   // return false if not into any category, or font
   default:
      return false;
      break;
   }

    return true;
 }