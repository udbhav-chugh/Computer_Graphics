GLuint textureMap;

int MAINSPHERE = 1;
int LIGHTSOURCE = 2;
int LEFTWALL = 3;
int GROUND = 4;

//function to get checked texture
void getTexture(void)
{
  unsigned char data[256][256][3];
  for (int y = 0; y < 255; y++) {
    for (int x = 0; x < 255; x++) {
      unsigned char *temp = data[y][x];
      if( ((x ^ y) & 8 ) !=0){
        temp[0] = temp[1] = temp[2] = 255;
      }
      else{
        temp[0] = temp[1] = temp[2] = 0;
      }
    }
  }
  glGenTextures(1, &textureMap);
  glBindTexture(GL_TEXTURE_2D, textureMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
int point[] = {0,1,2,3};
int planeHelp[] = {0,1,2,3};

// code for shadow matrix
void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundNormal[4],GLfloat lightSourcePosition[4]){
  GLfloat dotProduct;
  dotProduct = groundNormal[point[0]] * lightSourcePosition[point[0]] + groundNormal[point[1]] * lightSourcePosition[point[1]] + groundNormal[point[2]] * lightSourcePosition[point[2]] + groundNormal[point[3]] * lightSourcePosition[point[3]];
  
  shadowMat[0][0] = dotProduct - lightSourcePosition[point[0]] * groundNormal[point[0]];
  shadowMat[point[0]][1] = 0.f - lightSourcePosition[point[1]] * groundNormal[point[0]];
  shadowMat[point[0]][2] = 0.f - lightSourcePosition[point[2]] * groundNormal[point[0]];
  shadowMat[point[0]][3] = 0.f - lightSourcePosition[point[3]] * groundNormal[point[0]];
  
  for(int j = 0; j < 4 ; ++j){
  	for (int i = 1; i<4;i++){
  		if(i==j){
  			shadowMat[i][j] = dotProduct - lightSourcePosition[point[j]] * groundNormal[point[i]];
  		}
  		else{
  			shadowMat[i][j] = 0.f - lightSourcePosition[point[j]] * groundNormal[point[i]];
  		}
  	}
  }
}

//get plane equation
void findplane(GLfloat plane[4],GLfloat vertex0[3], GLfloat vertex1[3], GLfloat vertex2[3]){
  GLfloat vector0[3], vector1[3];
  vector0[point[0]] = vertex1[point[0]] - vertex0[point[0]];
  vector0[point[1]] = vertex1[point[1]] - vertex0[point[1]];
  vector0[point[2]] = vertex1[point[2]] - vertex0[point[2]];
  vector1[point[0]] = vertex2[point[0]] - vertex0[point[0]];
  vector1[point[1]] = vertex2[point[1]] - vertex0[point[1]];
  vector1[point[2]] = vertex2[point[2]] - vertex0[point[2]];
  
  plane[planeHelp[0]] = vector0[point[1]] * vector1[point[2]] - vector0[point[2]] * vector1[point[1]];
  plane[planeHelp[1]] = -(vector0[point[0]] * vector1[point[2]] - vector0[point[2]] * vector1[point[0]]);
  plane[planeHelp[2]] = vector0[point[0]] * vector1[point[1]] - vector0[point[1]] * vector1[point[0]];
  plane[planeHelp[3]] = -(plane[planeHelp[0]] * vertex0[point[0]] + plane[planeHelp[1]] * vertex0[point[1]] + plane[planeHelp[2]] * vertex0[point[2]]);
}