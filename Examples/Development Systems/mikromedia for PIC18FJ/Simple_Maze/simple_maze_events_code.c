#include "simple_maze_objects.h"
#include "simple_maze_resources.h"

//--------------------- User code ---------------------//
unsigned short Valid_Position() {
unsigned int X, Y, counter;
unsigned short result;

  result = 0;
  // Line1 check
  for (Y = 66; Y < 75; Y++) {
    for (counter = Line1.First_Point_X; counter < Line1.Second_Point_X+1; counter++) {
      if ((Circle1.Left-1 <= counter) && ( (Circle1.Left + Circle1.Radius*2 +1) >= counter ) &&
           (Circle1.Top-1 <= Y)  && ((Circle1.Top + Circle1.Radius*2 + 1) >= Y)) {
        result = 0;
        // Ball position is invalid no need to continue
        return result;
      }
      else {
        result = 1;
      }
    }
  }

  // Line2 check
  for (Y = 146; Y < 155; Y++) {
    for (counter = Line2.First_Point_X; counter < Line2.Second_Point_X+1; counter++) {
      if ((Circle1.Left-1 <= counter) && ( (Circle1.Left + Circle1.Radius*2 +1) >= counter ) &&
           (Circle1.Top-1 <= Y)  && ((Circle1.Top + Circle1.Radius*2 + 1) >= Y)) {
        result = 0;
        // Ball position is invalid no need to continue
        return result;
      }
      else {
        result = 1;
      }
    }
  }

  // Line3 check
  X = 190;
  for (counter = 154; counter < 240; counter++) {
    if ( (Circle1.Left-1 <= X) && ( (Circle1.Left + Circle1.Radius*2 +1) >= X ) &&
         (Circle1.Top-1 <= counter) && ((Circle1.Top + Circle1.Radius*2 + 1) >= counter)) {
      result = 0;
      // Ball position is invalid no need to continue
      return result;
    }
    else {
      result = 1;
    }
  }

  // check if still inside Screen
  X = 320;
  Y = 240;
  // four points are checked
  // top left, top right, bottom left, bottom right of the object in question
  // Top Left
  if ((Circle1.Left-1 <= X) && ( (Circle1.Left-1) >= 0 ) &&
      (Circle1.Top-1 <= Y) && ((Circle1.Top-1) >= 0)) {
      result = 1;
    }
    else {
      result = 0;
      return result;
    }

  // Top Right
  if (((Circle1.Left + Circle1.Radius*2 +1) <= X) && ( (Circle1.Left + Circle1.Radius*2 +1) >= 0 ) &&
      (Circle1.Top-1 <= Y) && ((Circle1.Top-1) >= 0)) {
      result = 1;
    }
    else {
      result = 0;
      return result;
    }

  // Bottom Left
  if (((Circle1.Left-1) <= X) && ((Circle1.Left-1) >= 0 ) &&
      ((Circle1.Top + Circle1.Radius*2 + 1) <= Y) && ((Circle1.Top + Circle1.Radius*2 + 1) >= 0)) {
      result = 1;
    }
    else {
      result = 0;
      return result;
    }

  // Bottom Right
  if (((Circle1.Left + Circle1.Radius*2 +1) <= X) && ((Circle1.Left + Circle1.Radius*2 +1) >= 0 ) &&
      ((Circle1.Top + Circle1.Radius*2 + 1) <= Y) && ((Circle1.Top + Circle1.Radius*2 + 1) >= 0)) {
      result = 1;
    }
    else {
      result = 0;
      return result;
    }

  return result;
}
//----------------- End of User code ------------------//

// Event Handlers

void Image2Press() {
  // Up
  Circle1.Top = Circle1.Top - 5;
  if (Valid_Position() == 1) {
    Circle1.Top = Circle1.Top + 5;
    TFT_Set_Brush(1, Screen1.Color, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
    TFT_Set_Pen(Screen1.Color, 1);
    TFT_Rectangle(Circle1.Left-1, Circle1.Top-1, Circle1.Left + Circle1.Radius*2 + 1, Circle1.Top + Circle1.Radius*2 + 1);
    Circle1.Top = Circle1.Top - 5;
    DrawCircle(&Circle1);
  }
  else
    Circle1.Top = Circle1.Top + 5;
}

void Image3Press() {
  // Right
  Circle1.Left = Circle1.Left + 5;
  if (Valid_Position() == 1) {
    Circle1.Left = Circle1.Left - 5;
    TFT_Set_Brush(1, Screen1.Color, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
    TFT_Set_Pen(Screen1.Color, 1);
    TFT_Rectangle(Circle1.Left-1, Circle1.Top-1, Circle1.Left + Circle1.Radius*2 + 1, Circle1.Top + Circle1.Radius*2 + 1);
    Circle1.Left = Circle1.Left + 5;
    DrawCircle(&Circle1);
  }
  else
    Circle1.Left = Circle1.Left - 5;
}

void Image4Press() {
  // Down
  Circle1.Top = Circle1.Top + 5;
  if (Valid_Position() == 1) {
    Circle1.Top = Circle1.Top - 5;
    TFT_Set_Brush(1, Screen1.Color, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
    TFT_Set_Pen(Screen1.Color, 1);
    TFT_Rectangle(Circle1.Left-1, Circle1.Top-1, Circle1.Left + Circle1.Radius*2 + 1, Circle1.Top + Circle1.Radius*2 + 1);
    Circle1.Top = Circle1.Top + 5;
    DrawCircle(&Circle1);
  }
  else
    Circle1.Top = Circle1.Top - 5;
}

void Image1Press() {
  // Left
  Circle1.Left = Circle1.Left - 5;
  if (Valid_Position() == 1) {
    Circle1.Left = Circle1.Left + 5;
    TFT_Set_Brush(1, Screen1.Color, 0, TOP_TO_BOTTOM, CL_BLACK, CL_BLACK);
    TFT_Set_Pen(Screen1.Color, 1);
    TFT_Rectangle(Circle1.Left-1, Circle1.Top-1, Circle1.Left + Circle1.Radius*2 + 1, Circle1.Top + Circle1.Radius*2 + 1);
    Circle1.Left = Circle1.Left - 5;
    DrawCircle(&Circle1);
  }
  else
    Circle1.Left = Circle1.Left + 5;
}

void Image5Click() {
  // Reset Ball
  Circle1.Left               = 17;
  Circle1.Top                = 18;
  DrawScreen(&Screen1);
}

void ButtonRound1Click() {
  DrawScreen(&Screen1);
}
