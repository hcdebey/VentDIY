 
String url1, url2;
 
/* put this in setup()

  cp5.addTextfield("textInput_1").setPosition(20, 300).setSize(200, 40).setAutoClear(false).setFont(createFont("Georgia",30));
  cp5.addTextfield("textInput_2").setPosition(20, 370).setSize(200, 40).setAutoClear(false).setHeight(40) ;
  cp5.addBang("Submit").setPosition(240, 370).setSize(80, 40);    

*/
void Submit() {
  print("the following text was submitted :");
  url1 = cp5.get(Textfield.class,"textInput_1").getText();
  url2 = cp5.get(Textfield.class,"textInput_2").getText();
  print(" textInput 1 = " + url1);
  print(" textInput 2 = " + url2);
  println();
}
