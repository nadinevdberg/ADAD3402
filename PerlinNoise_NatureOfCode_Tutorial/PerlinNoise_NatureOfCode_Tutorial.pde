// Perlin Noise tutorial bij The Nature of Code

float t = 0;
void setup(){
  size(500, 500);
  
}

void draw(){
  background(0);
  fill(255);
  
t = t + 0.05;
  float x = noise(t);
  x = map(x,0,1, 0, width);
  ellipse(x, height/2, 40, 40);
}
