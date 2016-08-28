varying vec3 f_color;
void main(void) {
  gl_FragColor[0] = f_color[0];
  gl_FragColor[1] = f_color[1];
  gl_FragColor[2] = f_color[2];
  gl_FragColor[3] = floor(mod(gl_FragCoord.y, 2.0));
}