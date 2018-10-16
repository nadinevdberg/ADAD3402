/* This code is based on:
    https://www.youtube.com/watch?v=RkuBWEkBrZA&t=1s
    https://www.youtube.com/watch?v=akM4wMZIBWg
*/

import peasy.*;


PeasyCam cam;
PVector [][] globe;
int total = 50; //increasing this will change the resolution of the circle

void setup(){
 size(1080, 1080, P3D);
 colorMode(HSB);
 
 cam = new PeasyCam(this, 1080);
 globe = new PVector[total+1][total+1];
 
 
}

void draw() {
  background (15);
  //stroke(200);
  //noFill();
  noStroke();
    
  lights();



  
  // I is for longitude, J for lattitude
  // Use the radius, lat and lon values to convert them into X, Y and Z values
  float r = 400;

  for (int i = 0; i < total+1; i++){
      float lat = map(i, 0, total,0, PI);
    for (int j = 0; j < total+1; j++){
       float lon = map(j, 0, total,0, TWO_PI);
      
      float x = r * sin(lat) * cos(lon);
      float y = r * sin(lat) * sin(lon);
      float z = r * cos(lat);
      
      globe[i][j] = new PVector(x, y, z);
      
    //  PVector v = PVector.random3D();
    //  v.mult(random(0, 15));
    //  globe[i][j].add(v);
      
    }
    
  }
   for (int i = 0; i < total; i++){
    beginShape(TRIANGLE_STRIP);
    
    for (int j = 0; j < total+1; j++){
      float hu = map(j, 0, total, 50, 70);
      fill(hu, 100, 150);
      PVector v1 = globe[i][j];
      vertex(v1.x, v1.y, v1.z);
      PVector v2 = globe[i+1][j];
      vertex(v2.x, v2.y, v2.z);
    }
    endShape();
  }
  
 }
