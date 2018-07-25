#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

enum Style {
  regular,
  bold
};

class PCL {

   char   ESC;
   string pcl_code;
   float  barcode_width_ratio;
   float  barcode_height;

   bool   print_barcode_text;

   int    PCL_WIDE_BAR;
   int    PCL_NARROW_BAR;

   int    PCL_RECTANGLE_SPACE;
   int    PCL_RECTANGLE_NOT_SPACE;
   int    PCL_TEXT_MARGIN;
   
  public:

    PCL() {
      ESC = (char) 27;
      pcl_code = "";
      barcode_width_ratio = 0.55;
      barcode_height = 300;

      PCL_WIDE_BAR = 30;
      PCL_NARROW_BAR = 10;
      PCL_RECTANGLE_SPACE = 1;
      PCL_RECTANGLE_NOT_SPACE = 0;
      PCL_TEXT_MARGIN = 75;

      print_barcode_text = 0;
    }

    void   debug();
    int get39BarWidth(char c);
    int get39WhiteWidth(char c);
    string code();
    string Esc(string code);
    void   Text(string code);
    void   Reset();
    void   EjectPage();
    void   XPos(int x);
    void   YPos(int y);
    void   SetPos(int x, int y);
    void   SetFont(int size, Style style);
    void   SetBCRatio(float ratio);
    void   SetBCHeight(float height);
    void   setTextMargin(float height);
    void   EnablePrintBarcodeText();
    void   DisablePrintBarcodeText();
    void   MoveH(float h);
    void   MoveV(float v);
    void   DrawRectangle(float H, float V, int is_space);
    void   Push();
    void   Pop();
    void   Image(string file_name);
    string RemoveResetCommands(string str);
    string RemoveChar(string str, char c);
    void   dump_dimensions(char c);
    void   print_char(char c);
    void   createFile(string name, string content);
    string ReadFile(string file_name);
    void   Barcode39(string value);
};
