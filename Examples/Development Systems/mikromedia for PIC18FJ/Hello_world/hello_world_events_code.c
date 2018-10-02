#include "hello_world_objects.h"
#include "hello_world_resources.h"

//--------------------- User code ---------------------//
bit image, label;

void Start_screen() {
  image = 1;
  label = 1;
  TFT_Set_Font(&Tahoma11x13_Regular, CL_AQUA, FO_HORIZONTAL);
  TFT_Write_Text("This  example  shows some basic  features of Visual TFT software.", 10, 105);
  TFT_Write_Text("By clicking on two buttons you can show/hide picture(mikroE Logo),", 10, 120);
  TFT_Write_Text("and Label ('MikroElektronika'). Changing  of  Label captions is", 10, 135);
  TFT_Write_Text("also demonstrated. Try it out, and don't  hesitete to experiment", 10, 150);
}
//----------------- End of User code ------------------//

// Event Handlers

void ButtonRound1Click() {
  // show/hide text
  label = ~label;
  switch (label) {
    case 0: {
      TFT_Set_Pen(CL_BLACK, 1);
      TFT_Set_Brush(1, CL_BLACK, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
      TFT_Rectangle(32, 63, 277, 97);
      strcpy(ButtonRound1.Caption, "Show Text");
      DrawRoundButton(&ButtonRound1);
      break;
    }
    case 1: {
      DrawLabel(&Label1);
      strcpy(ButtonRound1.Caption, "Hide Text");
      DrawRoundButton(&ButtonRound1);
      break;
    }
  }
}

void ButtonRound2Click() {
  // show/hide image
  image = ~image;
  switch (image) {
    case 0: {
      TFT_Set_Pen(CL_BLACK, 1);
      TFT_Set_Brush(1, CL_BLACK, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
      TFT_Rectangle(23, 7, 302, 53);
      strcpy(ButtonRound2.Caption, "Show Image");
      DrawRoundButton(&ButtonRound2);
      break;
    }
    case 1: {
      DrawImage(&Image1);
      strcpy(ButtonRound2.Caption, "Hide Image");
      DrawRoundButton(&ButtonRound2);
      break;
    }
  }
}
