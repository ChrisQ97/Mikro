typedef enum {_taLeft, _taCenter, _taRight} TTextAlign;

typedef struct Screen TScreen;

typedef struct  Button_Round {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          *Caption;
  TTextAlign    TextAlign;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          Corner_Radius;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TButton_Round;

typedef struct  Label {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Visible;
  char          Active;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TLabel;

typedef struct  Image {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  const char    *Picture_Name;
  char          Visible;
  char          Active;
  char          Picture_Type;
  char          Picture_Ratio;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TImage;

typedef struct  Circle {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Radius;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TCircle;

typedef struct  Line {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  First_Point_X;
  unsigned int  First_Point_Y;
  unsigned int  Second_Point_X;
  unsigned int  Second_Point_Y;
  char          Pen_Width;
  char          Visible;
  unsigned int  Color;
} TLine;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           Buttons_RoundCount;
  TButton_Round          * const code *Buttons_Round;
  unsigned int           LabelsCount;
  TLabel                 * const code *Labels;
  unsigned int           ImagesCount;
  TImage                 * const code *Images;
  unsigned int           CirclesCount;
  TCircle                * const code *Circles;
  unsigned int           LinesCount;
  TLine                 * const code *Lines;
};

extern   TScreen                Screen1;
extern   TLine                  Line3;
extern   TLine                  Line2;
extern   TImage               Image1;
extern   TImage               Image2;
extern   TImage               Image3;
extern   TImage               Image4;
extern   TLine                  Line1;
extern   TImage               Image5;
extern   TCircle                Circle1;
extern   TImage                 * const code Screen1_Images[5];
extern   TCircle                * const code Screen1_Circles[1];
extern   TLine                  * const code Screen1_Lines[3];


extern   TScreen                Screen2;
extern   TLabel                 Label1;
extern   TButton_Round          ButtonRound1;
extern   TLabel                 Label2;
extern   TButton_Round          * const code Screen2_Buttons_Round[1];
extern   TLabel                 * const code Screen2_Labels[2];



/////////////////////////
// Events Code Declarations
void ButtonRound1Click();
void Image1Press();
void Image2Press();
void Image3Press();
void Image4Press();
void Image5Click();
/////////////////////////

/////////////////////////////////
// Caption variables Declarations
extern char Line3_Caption[];
extern char Line2_Caption[];
extern char Image1_Caption[];
extern char Image2_Caption[];
extern char Image3_Caption[];
extern char Image4_Caption[];
extern char Line1_Caption[];
extern char Image5_Caption[];
extern char Circle1_Caption[];
extern char Label1_Caption[];
extern char ButtonRound1_Caption[];
extern char Label2_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawRoundButton(TButton_Round *Around_button);
void DrawLabel(TLabel *ALabel);
void DrawImage(TImage *AImage);
void DrawCircle(TCircle *ACircle);
void DrawLine(TLine *Aline);
void Check_TP();
void Start_TP();
