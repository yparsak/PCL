#include "pcl.h"

int main(int argc, char *argv[])
{

  PCL pcl;
// pcl.debug();
  pcl.SetBCHeight(300);
  pcl.DisablePrintBarcodeText();

  pcl.Reset();
  pcl.SetPos(320,120);
  pcl.SetFont(12, bold);
  pcl.Text("TITLE");
  pcl.SetFont(12, regular);

  pcl.SetPos(200,200);
  pcl.Barcode39("1"); 

  pcl.EnablePrintBarcodeText();
  pcl.SetPos(400,200);
  pcl.Barcode39("1");

  pcl.Reset();
  pcl.createFile("./test", pcl.code());

}
