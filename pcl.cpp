#include "pcl.h"
#include "barcode39.h"

void PCL::debug() {
  ESC = (char) 94;
}

int PCL::get39BarWidth(char c) {
  c = toupper(c);
  if (c == '1' || c == 'A' || c=='K' || c=='U') return B39_B1;
  if (c == '2' || c == 'B' || c=='L' || c=='V') return B39_B2;
  if (c == '3' || c == 'C' || c=='M' || c=='W') return B39_B3;
  if (c == '4' || c == 'D' || c=='N' || c=='X') return B39_B4;
  if (c == '5' || c == 'E' || c=='O' || c=='Y') return B39_B5;
  if (c == '6' || c == 'F' || c=='P' || c=='Z') return B39_B6;
  if (c == '7' || c == 'G' || c=='Q' || c=='-') return B39_B7;
  if (c == '8' || c == 'H' || c=='R' || c=='.') return B39_B8;
  if (c == '9' || c == 'I' || c=='S' || c==' ') return B39_B9;
  if (c == '0' || c == 'J' || c=='T' || c=='*') return B39_B10;
  if (c == '$' || c == '/' || c=='+' || c=='%') return B39_B11;
  return -1;
}

int PCL::get39WhiteWidth(char c) {
  c = toupper(c);
  if (c== '1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0') return B39_W1;
  if (c== 'A' || c=='B' || c=='C' || c=='D' || c=='E' || c=='F' || c=='G' || c=='H' || c=='I' || c=='J') return B39_W2;
  if (c== 'K' || c=='L' || c=='M' || c=='N' || c=='O' || c=='P' || c=='Q' || c=='R' || c=='S' || c=='T') return B39_W3;
  if (c== 'U' || c=='V' || c=='W' || c=='X' || c=='Y' || c=='Z' || c=='-' || c=='.' || c==' ' || c=='*') return B39_W4;
  if (c=='$') return B39_W5;
  if (c=='/') return B39_W6;
  if (c=='+') return B39_W7;
  if (c=='%') return B39_W8;
  return -1;
}

string PCL::code() { 
  return pcl_code; 
}

string PCL::Esc(string code) {
  return ESC + code;
}

void   PCL::Text(string code) {
  pcl_code += code; 
}

void   PCL::Reset() {
  Text(Esc("E"));
}

void PCL::EjectPage() {
  Reset();
}

void  PCL::XPos(int x) {
  ostringstream Xpos;
  Xpos << x;
  Text( Esc("*p" + Xpos.str() + "X") );
}

void  PCL::YPos(int y) {
  ostringstream Ypos;
  Ypos << y;
  Text( Esc("*p" + Ypos.str() + "Y") );
}

void   PCL::SetPos(int x, int y) {
  XPos(x);
  YPos(y);
}

void  PCL::SetFont(int size, Style style) {
  string is_bold = "0";
  if (style == bold) {is_bold="3";}
  ostringstream font_size;
  font_size << size;
  Text(Esc( "(s1p" +font_size.str()+ "vs" +is_bold+ "b4101T"));
}


void  PCL::SetBCRatio(float ratio) {
  barcode_width_ratio = ratio;  
}

void PCL::SetBCHeight(float height) {
  barcode_height = height;
}

void PCL::EnablePrintBarcodeText() {
  print_barcode_text = 1;
}

void PCL::DisablePrintBarcodeText() {
  print_barcode_text = 0;  
}

void PCL::MoveH(float h) {
  ostringstream Hpos;
  Hpos << h;
  string sign = "";
  if (h>=0) sign = "+";
  Text(Esc("&a"+sign+Hpos.str()+"H"));
}

void PCL::MoveV(float v) {
  ostringstream Vpos;
  Vpos << v;
  string sign = "";
  if (v>=0) sign = "+";
  Text(Esc("&a"+sign+Vpos.str()+"V"));
}

void PCL::DrawRectangle(float H, float V, int is_space) {
  ostringstream Hpos;
  ostringstream Vpos;
  ostringstream IsSpace;
  
  Hpos << H;
  Vpos << V;
  if (is_space != 1) is_space = 0;
  IsSpace << is_space;

  Text(Esc("*c" + Hpos.str() + "h" + Vpos.str() + "v" + IsSpace.str()+  "P"));   
}

void PCL::Push() {
  Text(Esc("&f0S"));
}

void PCL::Pop() {
  Text(Esc("&f1S"));
}

void PCL::Image(string file_name) {
  Text(RemoveResetCommands(ReadFile(file_name)));  
}

string PCL::RemoveResetCommands(string str) {
  string reset_command = Esc("E");
  int pos = str.find(reset_command);
  while (pos > -1) {
    str.erase(pos, reset_command.length());
    pos = str.find(reset_command);
  }
  return str;
}

string PCL::RemoveChar(string str, char c) {
  string result;
  for (size_t i = 0; i < str.size(); i++) {
    char chr = str[i];
    if (chr != c) result += chr;
  }
  return result;
}

void PCL::dump_dimensions(char chr) {
  int bar_width_bit_cnt = BAR_BIT_CNT;
  int white_width_bit_cnt = WHITE_BIT_CNT;

  unsigned  bar_width   = get39BarWidth(chr);
  unsigned  white_width = get39WhiteWidth(chr);
  if (bar_width == -1 || white_width == -1) {
    chr = '?';
    bar_width   = get39BarWidth(chr);
    white_width = get39WhiteWidth(chr);
  }

  int j, k;
  int bit;
  for (j = bar_width_bit_cnt -1, k = white_width_bit_cnt-1; j>= 0 ; j--, k--) {

    bit = (bar_width >> j) & 1;
    if (bit == 1) cout << "[1]";
    else          cout << "[0]";

    if (k>=0) {
      bit = (white_width >> k) & 1;
      if (bit == 1) cout << "1";
      else          cout << "0";
    }
  }
  cout << std::endl;
}

void PCL::print_char(char chr) {

  stringstream s;
  string chr_str;

  s << chr;
  s >> chr_str;

  int bar_width_bit_cnt = BAR_BIT_CNT;
  int white_width_bit_cnt = WHITE_BIT_CNT;

  unsigned  bar_width   = get39BarWidth(chr);
  unsigned  white_width = get39WhiteWidth(chr);
  if (bar_width == -1 || white_width == -1) {
    chr = '?';
    bar_width   = get39BarWidth(chr);
    white_width = get39WhiteWidth(chr);
  }

  if (print_barcode_text) {
    Push();
    Push();
  }

  int j, k;
  int bit;
  for (j = bar_width_bit_cnt -1, k = white_width_bit_cnt-1; j>= 0 ; j--, k--) {
    bit = (bar_width >> j) & 1;
    if (bit == 1) {
       DrawRectangle(PCL_WIDE_BAR * barcode_width_ratio, barcode_height, PCL_RECTANGLE_NOT_SPACE);
       MoveH(PCL_WIDE_BAR * barcode_width_ratio);
    }
    else {
       DrawRectangle(PCL_NARROW_BAR * barcode_width_ratio , barcode_height, PCL_RECTANGLE_NOT_SPACE);
       MoveH(PCL_NARROW_BAR * barcode_width_ratio);
    }
    if (k>=0) {
      bit = (white_width >> k) & 1;
      if (bit == 1) {
        DrawRectangle(PCL_WIDE_BAR * barcode_width_ratio, barcode_height, PCL_RECTANGLE_SPACE);
        MoveH(PCL_WIDE_BAR * barcode_width_ratio);
      }
      else  {
        DrawRectangle(PCL_NARROW_BAR * barcode_width_ratio, barcode_height, PCL_RECTANGLE_SPACE);
        MoveH(PCL_NARROW_BAR * barcode_width_ratio);
      }
    }
  }

  // Add Space
  DrawRectangle(PCL_NARROW_BAR * barcode_width_ratio, barcode_height, PCL_RECTANGLE_SPACE);
  MoveH(PCL_NARROW_BAR * barcode_width_ratio);

  if (print_barcode_text) {
    Pop();
    MoveV(barcode_height + PCL_TEXT_MARGIN);
    Text(chr_str);
    Pop();
    // move to Next char
    MoveH( (bar_width_bit_cnt+1) * PCL_WIDE_BAR * barcode_width_ratio);
  }

}

void   PCL::createFile(string name, string content) {
  ofstream ptr(name.c_str());
  ptr << content;
  ptr.close();
}

string  PCL::ReadFile(string file_name) {
  ifstream ptr(file_name.c_str());
  stringstream buffer;
  buffer << ptr.rdbuf();
  return buffer.str();
}

void  PCL::Barcode39(string value) {

  value = "*" + RemoveChar(value,'*') + "*";

  // Vertical Center On
  MoveV((barcode_height + PCL_TEXT_MARGIN) / -2) ;

  for (size_t i=0; i < value.size(); i++) {
    char chr = value[i];
    //dump_dimensions(chr);
    print_char(chr);
  }

  // Vertical Center Off
  MoveV((barcode_height + PCL_TEXT_MARGIN) / 2) ;

}



