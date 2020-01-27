import processing.serial.*;
import controlP5.*; // import controlP5 library
ControlP5 controlP5; // controlP5 object
color [] colors = new color[7]; 
Serial port;
String val;
String value1;
Textarea myTextarea;

boolean reverse;

void setup() {
 size(500,300);
  
 controlP5 = new ControlP5(this);
 myTextarea = controlP5.addTextarea("txt").setPosition(100,100).setSize(300,100).setLineHeight(14)
    .setColorBackground(color(255,100)).setColorForeground(color(255,100))
    .scroll(1).hideScrollbar();
 printArray(Serial.list()); 
 String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  port = new Serial(this, portName, 9600);
 // description : a bang controller triggers an event when pressed. 
 // parameters : name, x, y, width, height
 controlP5.addButton("Auto",1,20,10,60,20);
  controlP5.addButton("Left",1,90,10,60,20);
  controlP5.addButton("Right",1,160,10,60,20);
  controlP5.addButton("Room",1,230,10,60,20);
  controlP5.addButton("Reverse",1,300,10,60,20);
  controlP5.addButton("Stop",1,370,10,60,20);
  controlP5.addButton("oneEighty",1,440,10,60,20);
}
  
void draw() { 
 background(0); // background black
 
 // draw 7 squares and use as a fill color the colors from the colors array
 for(int i=0;i<7;i++) { // loop through colors array
 stroke(255);
 fill(colors[i]); // use color to fill
 rect(10+(i*45),210,40,40); // draw rectangle
 }
  
}

void Auto(){
    port.write('4');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1);     
     String s = myTextarea.getText();
    s += "Going Auto, ";
    myTextarea.setText(s);
}

void Left(){
    port.write('2');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1);         
    String s = myTextarea.getText();
    s += "Turned Left, ";
    myTextarea.setText(s);
}

void Right(){
    port.write('3');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1);       
    String s = myTextarea.getText();
    s += "Turned Right, ";
    myTextarea.setText(s);
}

void Room(){
    port.write('1');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1); 
     String s = myTextarea.getText();
    s += "found a room, ";
    myTextarea.setText(s);
}

void Reverse(){
    port.write('6');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1);   
    String s = myTextarea.getText();
    s += "Reversing, ";
    myTextarea.setText(s);
}

void Stop(){
    port.write('7');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1); 
     String s = myTextarea.getText();
    s += "Stopping, ";
    myTextarea.setText(s);
}

void oneEighty(){
    port.write('8');
//  print('w');
    delay(100);
    value1 = port.readString();
    print(value1); 
     String s = myTextarea.getText();
    s += "turning 180, ";
    myTextarea.setText(s);
}

//void keyPressed(){
//  if(key == 'w'){ 
//    reverse = true;
//  }
//}

//void keyReleased(){
//    if(key == 'w'){ 
//    reverse = false;
//  }
//}
