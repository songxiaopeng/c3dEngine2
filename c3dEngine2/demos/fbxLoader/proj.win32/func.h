
inline void printMat(float mat[16]){
	for(int i=0;i<16;i++){
		cout<<mat[i]<<" ";
	}cout<<endl;

}
inline bool isPointEq(const float p0[4],const float p1[4]){//判断两点是否重合
		const float localEps=0.0001;//已除以10
		if(fabs(p0[X]-p1[X])<localEps
			&&fabs(p0[Y]-p1[Y])<localEps
			&&fabs(p0[Z]-p1[Z])<localEps){
			return true;
		}else{
			return false;
		}
	}

inline	bool getNormalOfTri(const float p0[4],const float p1[4],const float p2[4],float norm[4]){//获得三角面的法向量，前端返回是否构成三角形
		float p01[4],p02[4];
		sub((float(&)[4])(*p1),(float(&)[4])(*p0),p01);
		sub((float(&)[4])(*p2),(float(&)[4])(*p0),p02);
		cross(p01,p02,norm);
		if(normalize(norm)==0){//如果nrom模为0，说明三点共线
			return false;
		}
		return true;
	}




inline	float PND_point_plane(const Cplane&plane,const float point[4]){//是点到平面的有向距离
		const float *norm=plane.norm;
		const float *p=plane.p;
		float ppoint[4];
		sub((float(&)[4])(*point),(float(&)[4])(*p),ppoint);
		float PNd=dot(norm,ppoint);
		return PNd;
		
}


inline bool IsExtensionSupported( char* szTargetExtension ) 
{ 
    const unsigned char *pszExtensions = NULL; 
    const unsigned char *pszStart; 
    unsigned char *pszWhere, *pszTerminator; 
  
    // Extension names should not have spaces 
    pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' ); 
    if( pszWhere || *szTargetExtension == '\0' ) 
        return false; 
  
    // Get Extensions String 
    pszExtensions = glGetString( GL_EXTENSIONS ); 
  
    // Search The Extensions String For An Exact Copy 
    pszStart = pszExtensions; 
    for(;;) 
    { 
        pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension ); 
        if( !pszWhere ) 
            break; 
        pszTerminator = pszWhere + strlen( szTargetExtension ); 
        if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' ) 
            if( *pszTerminator == ' ' || *pszTerminator == '\0' ) 
                return true; 
        pszStart = pszTerminator; 
    } 
    return false; 
} 

			
