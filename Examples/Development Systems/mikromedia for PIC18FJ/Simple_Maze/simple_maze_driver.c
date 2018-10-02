#include "simple_maze_objects.h"
#include "simple_maze_resources.h"
#include "built_in.h"


// TFT module connections
char TFT_DataPort at PORTJ;
sbit TFT_RST at LATD3_bit;
sbit TFT_BLED at LATC2_bit;
sbit TFT_RS at LATE0_bit;
sbit TFT_CS at LATD2_bit;
sbit TFT_RD at LATH1_bit;
sbit TFT_WR at LATH2_bit;
char TFT_DataPort_Direction at TRISJ;
sbit TFT_RST_Direction at TRISD3_bit;
sbit TFT_BLED_Direction at TRISC2_bit;
sbit TFT_RS_Direction at TRISE0_bit;
sbit TFT_CS_Direction at TRISD2_bit;
sbit TFT_RD_Direction at TRISH1_bit;
sbit TFT_WR_Direction at TRISH2_bit;
// End TFT module connections

// Touch Panel module connections
sbit DRIVEX_LEFT at LATA0_bit;
sbit DRIVEX_RIGHT at LATD7_bit;
sbit DRIVEY_UP at LATA1_bit;
sbit DRIVEY_DOWN at LATD4_bit;
sbit DRIVEX_LEFT_DIRECTION at TRISA0_bit;
sbit DRIVEX_RIGHT_DIRECTION at TRISD7_bit;
sbit DRIVEY_UP_DIRECTION at TRISA1_bit;
sbit DRIVEY_DOWN_DIRECTION at TRISD4_bit;
// End Touch Panel module connections

// Global variables
unsigned int Xcoord, Ycoord;
const ADC_THRESHOLD = 750;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;

int _object_count;
unsigned short object_pressed;
TButton_Round *local_round_button;
TButton_Round *exec_round_button;
int round_button_order;
TLabel *local_label;
TLabel *exec_label;
int label_order;
TImage *local_image;
TImage *exec_image;
int image_order;
TCircle *local_circle;
TCircle *exec_circle;
int circle_order;


void Init_ADC() {
  PLLEN_bit = 1;
  Delay_ms(150);
  ANCON0 = 0xF0; // All pins to digital
  ANCON1 = 0xFF;
  ADC_Init();
}
static void InitializeTouchPanel() {
  Init_ADC();
  TFT_Init(320, 240);

  TP_TFT_Init(320, 240, 0, 1);                                  // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}

void Calibrate() {
  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch selected corners for calibration", 50, 100);
  TFT_Line(315, 1, 319, 1);
  TFT_Line(310, 10, 319, 1);
  TFT_Line(319, 5, 319, 1);
  TFT_Write_Text("first here", 250, 20);

  TP_TFT_Calibrate_Min();                      // Calibration of bottom left corner
  Delay_ms(500);

  TFT_Set_Pen(CL_BLACK, 3);
  TFT_Set_Font(TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  TFT_Line(315, 1, 319, 1);
  TFT_Line(310, 10, 319, 1);
  TFT_Line(319, 5, 319, 1);
  TFT_Write_Text("first here", 250, 20);

  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Line(0, 239, 0, 235);
  TFT_Line(0, 239, 5, 239);
  TFT_Line(0, 239, 10, 229);
  TFT_Write_Text("now here ", 15, 200);

  TP_TFT_Calibrate_Max();                      // Calibration of bottom left corner
  Delay_ms(500);
}


/////////////////////////
  TScreen*  CurrentScreen;

  TScreen                Screen1;
  TLine                  Line3;
  TLine                  Line2;
  TImage               Image1;
  TImage               Image2;
  TImage               Image3;
  TImage               Image4;
  TLine                  Line1;
  TImage               Image5;
  TCircle                Circle1;
  TImage                 * const code Screen1_Images[5]=
         {
         &Image1,              
         &Image2,              
         &Image3,              
         &Image4,              
         &Image5               
         };
  TCircle                * const code Screen1_Circles[1]=
         {
         &Circle1              
         };
  TLine                  * const code Screen1_Lines[3]=
         {
         &Line3,               
         &Line2,               
         &Line1                
         };


  TScreen                Screen2;
  TLabel                 Label1;
char Label1_Caption[17] = "mikroElektronika";

  TButton_Round          ButtonRound1;
char ButtonRound1_Caption[17] = "Continue to Demo";

  TLabel                 Label2;
char Label2_Caption[17] = "Simple Maze Demo";

  TButton_Round          * const code Screen2_Buttons_Round[1]=
         {
         &ButtonRound1         
         };
  TLabel                 * const code Screen2_Labels[2]=
         {
         &Label1,              
         &Label2               
         };




static void InitializeObjects() {
  Screen1.Color                     = 0x0000;
  Screen1.Width                     = 320;
  Screen1.Height                    = 240;
  Screen1.Buttons_RoundCount        = 0;
  Screen1.LabelsCount               = 0;
  Screen1.ImagesCount               = 5;
  Screen1.Images                    = Screen1_Images;
  Screen1.CirclesCount              = 1;
  Screen1.Circles                   = Screen1_Circles;
  Screen1.LinesCount                = 3;
  Screen1.Lines                     = Screen1_Lines;
  Screen1.ObjectsCount              = 9;

  Screen2.Color                     = 0x0000;
  Screen2.Width                     = 320;
  Screen2.Height                    = 240;
  Screen2.Buttons_RoundCount        = 1;
  Screen2.Buttons_Round             = Screen2_Buttons_Round;
  Screen2.LabelsCount               = 2;
  Screen2.Labels                    = Screen2_Labels;
  Screen2.ImagesCount               = 0;
  Screen2.CirclesCount              = 0;
  Screen2.LinesCount                = 0;
  Screen2.ObjectsCount              = 3;


  Line3.OwnerScreen     = &Screen1;
  Line3.Order          = 0;
  Line3.First_Point_X  = 191;
  Line3.First_Point_Y  = 151;
  Line3.Second_Point_X = 191;
  Line3.Second_Point_Y = 238;
  Line3.Visible        = 1;
  Line3.Pen_Width      = 4;
  Line3.Color          = 0xC618;

  Line2.OwnerScreen     = &Screen1;
  Line2.Order          = 1;
  Line2.First_Point_X  = 78;
  Line2.First_Point_Y  = 150;
  Line2.Second_Point_X = 321;
  Line2.Second_Point_Y = 150;
  Line2.Visible        = 1;
  Line2.Pen_Width      = 7;
  Line2.Color          = 0xC618;

  Image1.OwnerScreen     = &Screen1;
  Image1.Order          = 2;
  Image1.Left           = 205;
  Image1.Top            = 184;
  Image1.Width          = 30;
  Image1.Height         = 30;
  Image1.Picture_Type        = 1;
  Image1.Picture_Ratio  = 1;
  Image1.Picture_Name   = eve_arrow_left_jpg;
  Image1.Visible        = 1;
  Image1.Active         = 1;
  Image1.OnUpPtr         = 0;
  Image1.OnDownPtr       = 0;
  Image1.OnClickPtr      = 0;
  Image1.OnPressPtr      = Image1Press;

  Image2.OwnerScreen     = &Screen1;
  Image2.Order          = 3;
  Image2.Left           = 237;
  Image2.Top            = 154;
  Image2.Width          = 30;
  Image2.Height         = 30;
  Image2.Picture_Type        = 1;
  Image2.Picture_Ratio  = 1;
  Image2.Picture_Name   = eve_arrow_up_jpg;
  Image2.Visible        = 1;
  Image2.Active         = 1;
  Image2.OnUpPtr         = 0;
  Image2.OnDownPtr       = 0;
  Image2.OnClickPtr      = 0;
  Image2.OnPressPtr      = Image2Press;

  Image3.OwnerScreen     = &Screen1;
  Image3.Order          = 4;
  Image3.Left           = 266;
  Image3.Top            = 180;
  Image3.Width          = 30;
  Image3.Height         = 30;
  Image3.Picture_Type        = 1;
  Image3.Picture_Ratio  = 1;
  Image3.Picture_Name   = eve_arrow_right_jpg;
  Image3.Visible        = 1;
  Image3.Active         = 1;
  Image3.OnUpPtr         = 0;
  Image3.OnDownPtr       = 0;
  Image3.OnClickPtr      = 0;
  Image3.OnPressPtr      = Image3Press;

  Image4.OwnerScreen     = &Screen1;
  Image4.Order          = 5;
  Image4.Left           = 236;
  Image4.Top            = 207;
  Image4.Width          = 30;
  Image4.Height         = 30;
  Image4.Picture_Type        = 1;
  Image4.Picture_Ratio  = 1;
  Image4.Picture_Name   = eve_arrow_down_jpg;
  Image4.Visible        = 1;
  Image4.Active         = 1;
  Image4.OnUpPtr         = 0;
  Image4.OnDownPtr       = 0;
  Image4.OnClickPtr      = 0;
  Image4.OnPressPtr      = Image4Press;

  Line1.OwnerScreen     = &Screen1;
  Line1.Order          = 6;
  Line1.First_Point_X  = 0;
  Line1.First_Point_Y  = 70;
  Line1.Second_Point_X = 243;
  Line1.Second_Point_Y = 70;
  Line1.Visible        = 1;
  Line1.Pen_Width      = 7;
  Line1.Color          = 0xC618;

  Image5.OwnerScreen     = &Screen1;
  Image5.Order          = 7;
  Image5.Left           = 200;
  Image5.Top            = 154;
  Image5.Width          = 25;
  Image5.Height         = 25;
  Image5.Picture_Type   = 0;
  Image5.Picture_Ratio  = 1;
  Image5.Picture_Name   = reload__bmp;
  Image5.Visible        = 1;
  Image5.Active         = 1;
  Image5.OnUpPtr         = 0;
  Image5.OnDownPtr       = 0;
  Image5.OnClickPtr      = Image5Click;
  Image5.OnPressPtr      = 0;

  Circle1.OwnerScreen     = &Screen1;
  Circle1.Order           = 8;
  Circle1.Left            = 11;
  Circle1.Top             = 18;
  Circle1.Radius          = 15;
  Circle1.Pen_Width       = 3;
  Circle1.Pen_Color       = 0xF800;
  Circle1.Visible         = 1;
  Circle1.Active          = 1;
  Circle1.Transparent     = 1;
  Circle1.Gradient        = 0;
  Circle1.Gradient_Orientation    = 0;
  Circle1.Gradient_Start_Color    = 0xFFFF;
  Circle1.Gradient_End_Color      = 0xC618;
  Circle1.Color           = 0xC618;
  Circle1.PressColEnabled = 0;
  Circle1.Press_Color     = 0x8410;
  Circle1.OnUpPtr         = 0;
  Circle1.OnDownPtr       = 0;
  Circle1.OnClickPtr      = 0;
  Circle1.OnPressPtr      = 0;

  Label1.OwnerScreen     = &Screen2;
  Label1.Order          = 0;
  Label1.Left           = 74;
  Label1.Top            = 41;
  Label1.Width          = 174;
  Label1.Height         = 32;
  Label1.Visible        = 1;
  Label1.Active         = 1;
  Label1.Caption        = Label1_Caption;
  Label1.FontName       = Impact20x29_Regular;
  Label1.Font_Color     = 0xF800;
  Label1.OnUpPtr         = 0;
  Label1.OnDownPtr       = 0;
  Label1.OnClickPtr      = 0;
  Label1.OnPressPtr      = 0;

  ButtonRound1.OwnerScreen     = &Screen2;
  ButtonRound1.Order           = 1;
  ButtonRound1.Left            = 94;
  ButtonRound1.Top             = 169;
  ButtonRound1.Width           = 133;
  ButtonRound1.Height          = 39;
  ButtonRound1.Pen_Width       = 1;
  ButtonRound1.Pen_Color       = 0x0000;
  ButtonRound1.Visible         = 1;
  ButtonRound1.Active          = 1;
  ButtonRound1.Transparent     = 1;
  ButtonRound1.Caption         = ButtonRound1_Caption;
  ButtonRound1.TextAlign             = _taCenter;
  ButtonRound1.TextAlign             = _taCenter;
  ButtonRound1.FontName        = Tahoma11x13_Regular;
  ButtonRound1.PressColEnabled = 1;
  ButtonRound1.Font_Color      = 0x0000;
  ButtonRound1.Gradient        = 1;
  ButtonRound1.Gradient_Orientation    = 0;
  ButtonRound1.Gradient_Start_Color    = 0xFFFF;
  ButtonRound1.Gradient_End_Color      = 0xC618;
  ButtonRound1.Color           = 0xC618;
  ButtonRound1.Press_Color     = 0x8410;
  ButtonRound1.Corner_Radius      = 3;
  ButtonRound1.OnUpPtr         = 0;
  ButtonRound1.OnDownPtr       = 0;
  ButtonRound1.OnClickPtr      = ButtonRound1Click;
  ButtonRound1.OnPressPtr      = 0;

  Label2.OwnerScreen     = &Screen2;
  Label2.Order          = 2;
  Label2.Left           = 66;
  Label2.Top            = 95;
  Label2.Width          = 189;
  Label2.Height         = 32;
  Label2.Visible        = 1;
  Label2.Active         = 1;
  Label2.Caption        = Label2_Caption;
  Label2.FontName       = Impact20x29_Regular;
  Label2.Font_Color     = 0x07FF;
  Label2.OnUpPtr         = 0;
  Label2.OnDownPtr       = 0;
  Label2.OnClickPtr      = 0;
  Label2.OnPressPtr      = 0;
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetRoundButton(index)         CurrentScreen->Buttons_Round[index]
#define GetLabel(index)               CurrentScreen->Labels[index]
#define GetImage(index)               CurrentScreen->Images[index]
#define GetCircle(index)              CurrentScreen->Circles[index]
#define GetLine(index)                CurrentScreen->Lines[index]

 void DeleteTrailingSpaces(char* str){
   char i;
   i = 0;
   while(1) {
   if(str[0] == ' ') {
      for(i = 0; i < strlen(str); i++) {
       str[i] = str[i+1];
      }
   }
   else
     break;
  }
 }

void DrawRoundButton(TButton_Round *Around_button) {
    if (Around_button->Visible == 1) {
      if (object_pressed == 1) {
        object_pressed = 0;
        TFT_Set_Brush(Around_button->Transparent, Around_button->Press_Color, Around_button->Gradient, Around_button->Gradient_Orientation,
                      Around_button->Gradient_End_Color, Around_button->Gradient_Start_Color);
      }
      else {
        TFT_Set_Brush(Around_button->Transparent, Around_button->Color, Around_button->Gradient, Around_button->Gradient_Orientation,
                      Around_button->Gradient_Start_Color, Around_button->Gradient_End_Color);
      }
      TFT_Set_Pen(Around_button->Pen_Color, Around_button->Pen_Width);
      if (Around_button->Height > Around_button->Width) {
        TFT_Rectangle_Round_Edges(Around_button->Left + 1, Around_button->Top + 1,
          Around_button->Left + Around_button->Width - 2,
          Around_button->Top + Around_button->Height - 2, Around_button->Corner_Radius);
      }
      else
        {
          TFT_Rectangle_Round_Edges(Around_button->Left + 1, Around_button->Top + 1,
            Around_button->Left + Around_button->Width - 2,
            Around_button->Top + Around_button->Height - 2, Around_button->Corner_Radius);
        }
      TFT_Set_Font(Around_button->FontName, Around_button->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text_Return_Pos(Around_button->Caption, Around_button->Left, Around_button->Top);
    if (Around_button->TextAlign == _taLeft)
      TFT_Write_Text(Around_button->Caption, Around_button->Left + 4, (Around_button->Top + ((Around_button->Height - caption_height) / 2)));
    else if (Around_button->TextAlign == _taCenter)
      TFT_Write_Text(Around_button->Caption, (Around_button->Left + (Around_button->Width - caption_length) / 2), (Around_button->Top + ((Around_button->Height - caption_height) / 2)));
    else if (Around_button->TextAlign == _taRight)
      TFT_Write_Text(Around_button->Caption, Around_button->Left + (Around_button->Width - caption_length - 4), (Around_button->Top + (Around_button->Height - caption_height) / 2));
    }
}

void DrawLabel(TLabel *ALabel) {
  if (ALabel->Visible == 1) {
    TFT_Set_Font(ALabel->FontName, ALabel->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text(ALabel->Caption, ALabel->Left, ALabel->Top);
  }
}

void DrawImage(TImage *AImage) {
  if (AImage->Visible) {
    if (AImage->Picture_Type == 0)
      TFT_Image(AImage->Left, AImage->Top, AImage->Picture_Name, AImage->Picture_Ratio);
    if (AImage->Picture_Type == 1)
      TFT_Image_Jpeg(AImage->Left, AImage->Top, AImage->Picture_Name);
  }
}

void DrawCircle(TCircle *ACircle) {
  if (ACircle->Visible == 1) {
    if (object_pressed == 1) {
      object_pressed = 0;
      TFT_Set_Brush(ACircle->Transparent, ACircle->Press_Color, ACircle->Gradient, ACircle->Gradient_Orientation,
                    ACircle->Gradient_End_Color, ACircle->Gradient_Start_Color);
    }
    else {
      TFT_Set_Brush(ACircle->Transparent, ACircle->Color, ACircle->Gradient, ACircle->Gradient_Orientation,
                    ACircle->Gradient_Start_Color, ACircle->Gradient_End_Color);
    }
    TFT_Set_Pen(ACircle->Pen_Color, ACircle->Pen_Width);
    TFT_Circle(ACircle->Left + ACircle->Radius,
               ACircle->Top + ACircle->Radius,
               ACircle->Radius);
  }
}

void DrawLine(TLine *Aline) {
  if (Aline->Visible == 1) {
    TFT_Set_Pen(Aline->Color, Aline->Pen_Width);
    TFT_Line(Aline->First_Point_X, Aline->First_Point_Y, Aline->Second_Point_X, Aline->Second_Point_Y);
  }
}

void DrawScreen(TScreen *aScreen) {
 int order;
  unsigned short round_button_idx;
  TButton_Round *local_round_button;
  unsigned short label_idx;
  TLabel *local_label;
  unsigned short image_idx;
  TImage *local_image;
  unsigned short circle_idx;
  TCircle *local_circle;
  unsigned short line_idx;
  TLine *local_line;
  char save_bled, save_bled_direction;

  object_pressed = 0;
  order = 0;
  round_button_idx = 0;
  label_idx = 0;
  image_idx = 0;
  circle_idx = 0;
  line_idx = 0;
  CurrentScreen = aScreen;

  if ((display_width != CurrentScreen->Width) || (display_height != CurrentScreen->Height)) {
    save_bled = TFT_BLED;
    save_bled_direction = TFT_BLED_Direction;
    TFT_BLED_Direction = 0;
    TFT_BLED           = 0;
    TFT_Init(CurrentScreen->Width, CurrentScreen->Height);
    TP_TFT_Init(CurrentScreen->Width, CurrentScreen->Height, 0, 1);                                  // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold
    TFT_Fill_Screen(CurrentScreen->Color);
    display_width = CurrentScreen->Width;
    display_height = CurrentScreen->Height;
    TFT_BLED           = save_bled;
    TFT_BLED_Direction = save_bled_direction;
  }
  else
    TFT_Fill_Screen(CurrentScreen->Color);


  while (order < CurrentScreen->ObjectsCount) {
    if (round_button_idx < CurrentScreen->Buttons_RoundCount) {
      local_round_button = GetRoundButton(round_button_idx);
      if (order == local_round_button->Order) {
        order++;
        round_button_idx++;
        DrawRoundButton(local_round_button);
      }
    }

    if (label_idx < CurrentScreen->LabelsCount) {
      local_label = GetLabel(label_idx);
      if (order == local_label->Order) {
        label_idx++;
        order++;
        DrawLabel(local_label);
      }
    }

    if (circle_idx < CurrentScreen->CirclesCount) {
      local_circle = GetCircle(circle_idx);
      if (order == local_circle->Order) {
        circle_idx++;
        order++;
        DrawCircle(local_circle);
      }
    }

    if (line_idx  < CurrentScreen->LinesCount) {
      local_line = GetLine(line_idx);
      if (order == local_line->Order) {
        line_idx++;
        order++;
        DrawLine(local_line);
      }
    }

    if (image_idx  < CurrentScreen->ImagesCount) {
      local_image = GetImage(image_idx);
      if (order == local_image->Order) {
        image_idx++;
        order++;
        DrawImage(local_image);
      }
    }

  }
}

void Get_Object(unsigned int X, unsigned int Y) {
  round_button_order  = -1;
  label_order         = -1;
  image_order         = -1;
  circle_order        = -1;
  //  Buttons with Round Edges
  for ( _object_count = 0 ; _object_count < CurrentScreen->Buttons_RoundCount ; _object_count++ ) {
    local_round_button = GetRoundButton(_object_count);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }

  //  Labels
  for ( _object_count = 0 ; _object_count < CurrentScreen->LabelsCount ; _object_count++ ) {
    local_label = GetLabel(_object_count);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  //  Images
  for ( _object_count = 0 ; _object_count < CurrentScreen->ImagesCount ; _object_count++ ) {
    local_image = GetImage(_object_count);
    if (local_image->Active == 1) {
      if (IsInsideObject(X, Y, local_image->Left, local_image->Top,
                         local_image->Width, local_image->Height) == 1) {
        image_order = local_image->Order;
        exec_image = local_image;
      }
    }
  }

  //  Circles
  for ( _object_count = 0 ; _object_count < CurrentScreen->CirclesCount ; _object_count++ ) {
    local_circle = GetCircle(_object_count);
    if (local_circle->Active == 1) {
      if (IsInsideObject(X, Y, local_circle->Left, local_circle->Top,
                        (local_circle->Radius * 2), (local_circle->Radius * 2)) == 1) {
        circle_order = local_circle->Order;
        exec_circle = local_circle;
      }
    }
  }

  _object_count = -1;
  if (round_button_order > _object_count)
    _object_count = round_button_order;
  if (label_order >  _object_count )
    _object_count = label_order;
  if (image_order >  _object_count )
    _object_count = image_order;
  if (circle_order >  _object_count )
    _object_count = circle_order;
}


static void Process_TP_Press(unsigned int X, unsigned int Y) {
  exec_round_button   = 0;
  exec_label          = 0;
  exec_image          = 0;
  exec_circle         = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
    if (_object_count == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnPressPtr != 0) {
          exec_round_button->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnPressPtr != 0) {
          exec_label->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnPressPtr != 0) {
          exec_image->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == circle_order) {
      if (exec_circle->Active == 1) {
        if (exec_circle->OnPressPtr != 0) {
          exec_circle->OnPressPtr();
          return;
        }
      }
    }

  }
}

static void Process_TP_Up(unsigned int X, unsigned int Y) {

  switch (PressedObjectType) {
    // Round Button
    case 1: {
      if (PressedObject != 0) {
        exec_round_button = (TButton_Round*)PressedObject;
        if ((exec_round_button->PressColEnabled == 1) && (exec_round_button->OwnerScreen == CurrentScreen)) {
          DrawRoundButton(exec_round_button);
        }
        break;
      }
      break;
    }
    // Circle
    case 4: {
      if (PressedObject != 0) {
        exec_circle = (TCircle*)PressedObject;
        if ((exec_circle->PressColEnabled == 1) && (exec_circle->OwnerScreen == CurrentScreen)) {
          DrawCircle(exec_circle);
        }
        break;
      }
      break;
    }
  }

  exec_label          = 0;
  exec_image          = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
  // Buttons with Round Edges
    if (_object_count == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnUpPtr != 0)
          exec_round_button->OnUpPtr();
        if (PressedObject == (void *)exec_round_button)
          if (exec_round_button->OnClickPtr != 0)
            exec_round_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Labels
    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnUpPtr != 0)
          exec_label->OnUpPtr();
        if (PressedObject == (void *)exec_label)
          if (exec_label->OnClickPtr != 0)
            exec_label->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Images
    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnUpPtr != 0)
          exec_image->OnUpPtr();
        if (PressedObject == (void *)exec_image)
          if (exec_image->OnClickPtr != 0)
            exec_image->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Circles
    if (_object_count == circle_order) {
      if (exec_circle->Active == 1) {
        if (exec_circle->OnUpPtr != 0)
          exec_circle->OnUpPtr();
        if (PressedObject == (void *)exec_circle)
          if (exec_circle->OnClickPtr != 0)
            exec_circle->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

static void Process_TP_Down(unsigned int X, unsigned int Y) {

  object_pressed      = 0;
  exec_round_button   = 0;
  exec_label          = 0;
  exec_image          = 0;
  exec_circle         = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->PressColEnabled == 1) {
          object_pressed = 1;
          DrawRoundButton(exec_round_button);
        }
        PressedObject = (void *)exec_round_button;
        PressedObjectType = 1;
        if (exec_round_button->OnDownPtr != 0) {
          exec_round_button->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == label_order) {
      if (exec_label->Active == 1) {
        PressedObject = (void *)exec_label;
        PressedObjectType = 2;
        if (exec_label->OnDownPtr != 0) {
          exec_label->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == image_order) {
      if (exec_image->Active == 1) {
        PressedObject = (void *)exec_image;
        PressedObjectType = 3;
        if (exec_image->OnDownPtr != 0) {
          exec_image->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == circle_order) {
      if (exec_circle->Active == 1) {
        if (exec_circle->PressColEnabled == 1) {
          object_pressed = 1;
          DrawCircle(exec_circle);
        }
        PressedObject = (void *)exec_circle;
        PressedObjectType = 4;
        if (exec_circle->OnDownPtr != 0) {
          exec_circle->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Init_MCU() {
  TP_TFT_Rotate_180(0);
}

void Start_TP() {
  Init_MCU();

  InitializeTouchPanel();

  Delay_ms(1000);
  TFT_Fill_Screen(0);
  Calibrate();
  TFT_Fill_Screen(0);

  InitializeObjects();
  display_width = Screen2.Width;
  display_height = Screen2.Height;
  DrawScreen(&Screen2);
}
