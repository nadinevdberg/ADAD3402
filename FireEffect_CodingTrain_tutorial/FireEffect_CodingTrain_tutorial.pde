// © The Coding Train - Fire effect tutorial

PImage buffer1;
PImage buffer2;
PImage cooling;
int w = 600;
int h = 400;
float ystart=0.0;
void setup(){
 // size(600, 400);
  buffer1 = createImage(w, h, RGB);
  buffer2 = createImage(w, h, RGB);
  cooling = createImage(w, h, RGB);
}

void settings(){
  size(1200, 400, FX2D);
}



void draw(){
  
 fire(3);
  cool();

  background(0);
buffer1.loadPixels();
buffer2.loadPixels(); 
  for (int x = 1; x < w-1; x++){
   for (int y = 1; y < h-1; y++){
     int index0 = x + (y) * w;
     int index1 =(x+1) + (y) * w;
     int index2 = (x-1) + (y) * w;
     int index3 =(x) + (y+1) * w;
     int index4 = (x) +(y-1) * w;
     color c1 = buffer1.pixels[index1];
     color c2 = buffer1.pixels[index2];
     color c3 = buffer1.pixels[index3];
     color c4 = buffer1.pixels[index4];
     
     color c5 = cooling.pixels[index0];
     float newC = brightness(c1) + brightness(c2) +brightness(c3) +brightness(c4);
     newC = newC - brightness(c5);
     
     
     buffer2.pixels[index4] = color(newC * 0.25); 
     
   }
  }
  
  buffer2.updatePixels();
  
  //swap
  PImage temp = buffer1;
  buffer1 = buffer2;
  buffer2 = temp;
  image(buffer2, 0, 0);
  image(cooling,w,0);
}

void fire(int rows){
   buffer1.loadPixels();
 
  for (int x = 0; x < w; x++){
    for (int j = 0; j < rows; j++){
       int y = h -(j+1);
       int index = x + y * w;
       buffer1.pixels[index] = color(255);
    }  
  }
  buffer1.updatePixels();
}

void cool(){
  cooling.loadPixels();  
  float xoff = 0.0; // Start xoff at 0
  float increment = 0.02;  
  
  // For every x,y coordinate in a 2D space, calculate a noise value and produce a brightness value
  for (int x = 0; x < w; x++) {
    xoff += increment;   // Increment xoff 
    float yoff = ystart;   // For every xoff, start yoff at 0
    for (int y = 0; y < h; y++) {
      yoff += increment; // Increment yoff
      
      // Calculate noise and scale by 255
      float n = noise(xoff, yoff);

      float bright = noise(xoff, yoff) * 75;

      // Try using this line instead
      //float bright = random(0,255);
      
      // Set each pixel onscreen to a grayscale value
      cooling.pixels[x+y*w] = color(bright);
      
    }
  }
  
  cooling.updatePixels();
  ystart += increment;
}
