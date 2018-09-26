// © The Coding Train - Fire effect tutorial

PImage buffer1;
PImage buffer2;

void setup(){
 // size(600, 400);
  buffer1 = createImage(width, height, RGB);
  buffer2 = createImage(width, height, RGB);
  
 
}

void settings(){
  size(600, 400, FX2D);
}

void fire(){
   buffer1.loadPixels();
  for (int x = 0; x < width; x++){
   int y = height -1;
   int index = x + y * width;
   buffer1.pixels[index] = color(255);
  }
  buffer1.updatePixels();
}

void draw(){
  fire();
  background(0);
buffer1.loadPixels();
buffer2.loadPixels(); 
  for (int x = 1; x < width-1; x++){
   for (int y = 1; y < height-1; y++){
     int index0 = x + y * width;
     int index1 =(x+1) + (y) * width;
     int index2 = (x-1) + (y) * width;
     int index3 =(x) + (y+1) * width;
     int index4 = (x) +(y-1) * width;
     color c1 = buffer1.pixels[index1];
     color c2 = buffer1.pixels[index2];
     color c3 = buffer1.pixels[index3];
     color c4 = buffer1.pixels[index4];
     
     float newC = brightness(c1) + brightness(c2) +brightness(c3) +brightness(c4);
     buffer2.pixels[index0] = color(newC * 0.25);
     
     
     
   }
  }
  
  buffer2.updatePixels();
  
  //swap
  PImage temp = buffer1;
  buffer1 = buffer2;
  buffer2 = temp;
  image(buffer2, 0, 0);
}
