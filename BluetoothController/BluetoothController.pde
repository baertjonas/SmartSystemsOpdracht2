import processing.serial.*; //<>// //<>//
import controlP5.*; // import controlP5 library
Serial BT;
ControlP5 controlP5; // controlP5 object
//JSONObject json;

int LeftSpeed = 0;
int LeftDir = 1;
int RightSpeed = 0;
int RightDir = 1;

String json = "{\"LeftSpeed\": "+ LeftSpeed +" ,\"LeftDir\": " + LeftDir +" ,\"RightSpeed\": " + RightSpeed + ",\"RightDir\": " + RightDir + "}";

// user interface elements
void setup() {
  size(300, 480);
  //json = new JSONObject();

  BT = new Serial(this, "/dev/cu.HC-05_JB-DevB", 9600);
  
  controlP5 = new ControlP5(this);

  Bang stop = controlP5.addBang("Stop", 120, 360, 60, 60);
  stop.setColorForeground(color(255, 0, 0));
  stop.setColorActive(color(128, 0, 0));

  controlP5.addToggle("Toggle Left", true, 30, 360, 60, 60);
  controlP5.addToggle("Toggle Right", true, 210, 360, 60, 60);

  controlP5.addSlider("Left Speed", 0, 255, 0, 30, 30, 60, 300);
  controlP5.addSlider("Right Speed", 0, 255, 0, 210, 30, 60, 300);
}

void draw() { 
  background(0); // background black
  
  BT.write(json);
  BT.write('\n');
  
  delay(100);
}

void controlEvent(ControlEvent theEvent) {
  print("control event from : "+theEvent.getController().getName());
  println(", value : "+theEvent.getController().getValue());

  if (theEvent.getController().getName()=="Stop") {
    //json.setInt("LeftSpeed", 0);
    //json.setInt("LeftDir", 1);
    //json.setInt("RightSpeed", 0);
    //json.setInt("RightDir", 1);
    LeftSpeed = 0;
    RightSpeed = 0;
    println("STOP!");
  }

  if (theEvent.getController().getName()=="Left Speed") {
    LeftSpeed = int(theEvent.getValue());
    println(LeftSpeed);
  } 
  
  if (theEvent.getController().getName()=="Right Speed") {
    RightSpeed = int(theEvent.getValue());
    println(RightSpeed);
  }
  
  if (theEvent.getController().getName()=="Toggle Left") {
    LeftDir = int(theEvent.getValue());
    if (LeftDir == 0) { LeftDir = -1; }
    println(LeftDir);
  }
  
  if (theEvent.getController().getName()=="Toggle Right") {
    RightDir = int(theEvent.getValue());
    if (RightDir == 0) { RightDir = -1; }
    println(RightDir);
  }
  
  json = "{\"LeftSpeed\": "+ LeftSpeed +" ,\"LeftDir\": " + LeftDir +" ,\"RightSpeed\": " + RightSpeed + ",\"RightDir\": " + RightDir + "}";
  println(json);  
}
