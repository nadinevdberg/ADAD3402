/* This code is based on:
    https://www.youtube.com/watch?v=RkuBWEkBrZA&t=1s
    https://www.youtube.com/watch?v=akM4wMZIBWg
*/

import peasy.*;


PeasyCam cam;
PVector [][] globe;
int total = 80; //increasing this will change the resolution of the circle

float a = 1;
float b = 1;
float offset = 0; 
float m = 0;
float mchange = 0;

void setup(){
 size(1000, 1000, P3D);
 colorMode(HSB);
 cam = new PeasyCam(this, 1080);
 globe = new PVector[total+1][total+1];
 
 
}

float superShape(float theta, float m, float n1, float n2, float n3){

  float t1 =abs((1/a)*cos(m * theta / 4));
  t1 = pow(t1, n2);
  float t2 = abs((1/b)*sin(m * theta / 4));
  t2 = pow(t2, n3);
  float t3 = t1 + t2;
  float r = pow(t3, -1/n1);
  
  return r;
}

void draw() {
  background (255);
  noStroke();  
  lights();
  rotateX (float(frameCount) / 100);
  rotateY (float(frameCount) / 100);
  
  
  float r = 400; 
  float noiseScale = 0.02;
 m = map(cos(mchange), -1, 1, 0, 1);

  mchange += 0.1;

//  m= noise(mchange) * 0.02;
 
  for (int i = 0; i < total+1; i++){
      float lat = map(i, 0, total,-HALF_PI, HALF_PI);
      float r2 = superShape(lat, noise(m), 3, 0.5, 0.5); 
      for (int j = 0; j < total+1; j++){
        float lon = map(j, 0, total, -PI, PI);
        float r1 = superShape(lon, noise(m),0.6, 0.5, 0.5); 
       
        float x = r * r1 * cos(lon) * r2 * cos(lat);
        float y = r * r1 * sin(lon) * r2 * cos(lat);
        float z = r * r2 * sin(lat);
      
        globe[i][j] = new PVector(x, y, z);
      
      //PVector v = PVector.random3D();
      //v.mult(random(0, 15));
      //globe[i][j].add(v);
      
    }
    
  }
  //stroke(255);
 
   for (int i = 0; i < total; i++){
    beginShape(TRIANGLE_STRIP);
    //offset += 50;
    for (int j = 0; j < total+1; j++){
      float hu = map(i, 0, total, 0, 210);
      float sa = map(i, 0, total, 0, 100);
      float br = map(i, 0, total, 0,135);
      fill(hu, sa, br);
      PVector v1 = globe[i][j];
      vertex(v1.x, v1.y, v1.z);
      PVector v2 = globe[i+1][j];
      vertex(v2.x, v2.y, v2.z);
    }
    endShape();
  }
  
 }
