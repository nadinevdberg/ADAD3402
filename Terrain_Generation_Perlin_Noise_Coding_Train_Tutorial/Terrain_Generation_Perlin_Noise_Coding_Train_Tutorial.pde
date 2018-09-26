// Tutorial by The Coding Train
// Coding Challenge #11: 3D Terrain Generation with Perlin Noise in Processing


 int cols, rows;
 int scl = 20;     //scale
 int w = 1920;
 int h = 1080;
 
 float yoff ;
 float xoff;
 float flying = 0;
 float movement = 0;
 
 //2 dimensional array
 float[][] terrain;
 
void setup() {
 size(600, 600, P3D); 
 cols = w / scl;
 rows = h / scl; 
 
 terrain = new float [cols][rows];


}

void draw(){
  
 background(0);
 stroke(255);
 noFill();
 
 flying += 0.005;
 movement += 0.005;
 yoff = flying;
 xoff = movement;
 for (int y = 0; y < rows; y++){
   xoff = 0;
  for (int x = 0; x < cols; x++){
    //pick a random set of values in the setup and instead of drawing them, get them from draw
   terrain[x][y] = map(noise(xoff,yoff), 0, 1, -250, 200);  
   xoff += 0.05;
  }
 yoff += 0.05;
 }
 
 translate(width/2, height/2);
 
 //rotate 60 degrees
 rotateX(PI/3);
 
 //move grid to left
 translate(-w/2, -h/2);

 // create raster with triangles using vertexes
 for (int y = 0; y < rows-1; y++){
   beginShape(TRIANGLE_STRIP);
   
   for (int x = 0 ; x < cols; x++){   
     vertex(x*scl, y*scl, terrain[x][y]);
     vertex(x*scl, (y+1)*scl, terrain[x][y+1]);  
   }
   endShape();
 }
}
