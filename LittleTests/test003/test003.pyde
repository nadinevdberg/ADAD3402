"""
This code is based on: https://www.youtube.com/watch?v=v8R9RXb6OVU
"""

def setup():
    global sphere_size
    size(1920, 1080, P3D)
    sphere_size = 400

def draw():
    global sphere_size
    background(10)
    translate(width / 2, height / 2, 0)
    rotateX (float(frameCount) / 1000)
    rotateY (float(frameCount) / 1000)
    noFill()
    stroke(255)
    sphere(sphere_size)
    
