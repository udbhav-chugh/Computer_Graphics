//This header file contains function to read the House.obj file and initialise the object
//The parser requires obj file to have vertex, vertex normal and vertex texture information

//object data class initialised after reading from House.obj
class objectData{
public:
	float vertex[3];
	float vertexNormal[3];
	float vertexTexture[3];

	objectData(){
		vertex[0]=0;vertex[1]=0;vertex[2]=0;
		vertexNormal[0]=0;vertexNormal[1]=0;vertexNormal[2]=0;
		vertexTexture[0]=0;vertexTexture[1]=0;vertexTexture[2]=0;
	}
};

void initialiseObject();
void drawObject();

objectData object;
vector<objectData> dataVector;
bool normalPresent = false;

float vertexTemp,vertexNormalTemp,vertexTextureTemp;
vector<float> vertex;
vector<float> vertexNormal;
vector<float> vertexTexture;

int i,j;
char line[200];
GLuint dataList;

//read v, vn and vt tags from House.obj and update object data 
void initialiseObject(){

	FILE *filePointer;
	filePointer=fopen("House.obj","r");
	if(filePointer==NULL){
		printf("File Not Found\n");
		return;
	}
	while(!(feof(filePointer))){
		fscanf(filePointer,"%s",line);
		//check for only 'v'
		if(line[0] == 'v' && line[1] != 'n' && line[1] != 't'){
			for(i=0;i<3;i++){
				fscanf(filePointer,"%f",&vertexTemp);
				vertex.push_back(vertexTemp);
			}
		}
		//check for 'vn'
		else if(line[0]=='v'&&line[1]=='n'){
			for(i=0;i<3;i++){
				fscanf(filePointer,"%f",&vertexNormalTemp);
				vertexNormal.push_back(vertexNormalTemp);
			}
		}
		//check for 'vt'
		else if(line[0]=='v'&&line[1]=='t'){
			for(i=0;i<3;i++){
				fscanf(filePointer,"%f",&vertexTextureTemp);	
				vertexTexture.push_back(vertexTextureTemp);
			}
		}
	}
	fclose(filePointer);
	drawObject();
}

//draw the inital object using frame data in House.obj
void drawObject(){
	dataList=glGenLists(1);
	FILE *filePointer2;
	filePointer2=fopen("House.obj","r");
	int eq;
	char ch[20];

	while(!(feof(filePointer2))){	
		fscanf(filePointer2,"%s",line);
		//read frames
		if(line[0]=='f' && strlen(line)==1){	
			for(i=0;i<3;i++){
				int v,vt,vn;
				int val=fscanf(filePointer2,"%d/%d/%d",&v,&vt,&vn);
				if(val==3)
					normalPresent=true;
				else{
					printf("Frame must have vertex, texture and normal in frame and each frame must have three vertices\n");
					return;
				}
				//Vertex
				v=v*3;
				object.vertex[0]=vertex[v];
				object.vertex[1]=vertex[v+1];
				object.vertex[2]=vertex[v+2];
				//Normal
				vn*=3;	
				object.vertexNormal[0]=vertexNormal[vn];
				object.vertexNormal[1]=vertexNormal[vn+1];
				object.vertexNormal[2]=vertexNormal[vn+2];					


				dataVector.push_back(object);
			}
		} 	
	}
	fclose(filePointer2);
	vertex.clear();
	vertexNormal.clear();
	vertexTexture.clear();

	glNewList(dataList, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(i=0;i<dataVector.size();i++){
		if(normalPresent==true){
			glNormal3f(dataVector[i].vertexNormal[0],dataVector[i].vertexNormal[1],dataVector[i].vertexNormal[2]);
		}
		glVertex3f(dataVector[i].vertex[0],dataVector[i].vertex[1],dataVector[i].vertex[2]);
	}
	glEnd();
	glEndList();
}
