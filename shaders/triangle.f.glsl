#ifdef GL_ES
# ifdef GL_FRAGMENT_PRECISION_HIGH
    precision highp float;
# else
    precision mediump float;
# endif
#endif
varying vec3 f_color;
varying vec3 f_coord3d;
void main(void) {
  gl_FragColor[0] = f_color[0];
  gl_FragColor[1] = f_color[1];
  gl_FragColor[2] = f_color[2];
  gl_FragColor[3] = f_coord3d.y+1;
}