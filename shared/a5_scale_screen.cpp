// Scale Screen:
//    Sets up transforms in order to fit any resolution
//    onto an ALLEGRO_FULLSCREEN_WINDOW.
//
// (Special thanks to Matthew Leverton for help with this!)

#include <allegro5/allegro.h>

#include "a5_scale_screen.h"

// usage: a5_scale_screen(BUFFER_WIDTH, BUFFER_HEIGHT, display_width, display_height);
void a5_scale_screen(int bw, int bh, int dw, int dh)
{
  ALLEGRO_TRANSFORM t;

  // Calculate the horizontal and vertial aspect ratios
  const float HAR = dw/(float)bw;
  const float VAR = dh/(float)bh;

  // The aspect ratio, x-offset and y-offset (in pixels)
  float ar, ox, oy;


  if (bw == dw && bh == dh)
  {
    // 1:1, just reset everything
    al_identity_transform(&t);
    al_use_transform(&t);
    al_set_clipping_rectangle(0, 0, bw, bh);
  }
  else
  {
    // Choose the smaller aspect ratio
    if (HAR < VAR)
    {
      // horizontal bars on the top and bottom
      ar = HAR;
      ox = 0;
      oy = (dh - (ar * bh)) / 2.0;
    }
    else
    {
      // vertical bars on the left and right
      ar = VAR;
      ox = (dw - (ar * bw)) / 2.0;
      oy = 0;
    }

    // set up the transformation to scale and translate
    al_build_transform(&t, ox, oy, ar, ar, 0);
    al_use_transform(&t);

    // make sure nothing is drawn into the black bars
    al_set_clipping_rectangle(ox, oy, ar * bw, ar * bh);
  }
}
