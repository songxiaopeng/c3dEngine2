//-------------------------------------
// do not use chinese in comment
//-------------------------------------
//attribute pass from vbo or va
attribute vec4 a_position;
attribute vec2 a_texCoord;

//matrixs pass from outside
uniform mat4 projectionModelview;

//pass to fragment shader
varying vec2 texCoordOut;

void main(void) {
gl_Position = projectionModelview* a_position;
    texCoordOut = a_texCoord;
}