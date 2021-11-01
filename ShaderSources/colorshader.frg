        #version 450 core
		                                                          
	layout (location = 1) in vec3 veccolor;                            
	layout (location = 2) in vec2 tex;                                 
	out vec4 color;                                                    
	uniform vec3 triangleColor;                                        
	//out vec4 FragColor                                               
		                                                           
	in VS_OUT                                                          
	{                                                                  
	    vec4 color;                                                    
	    vec2 TexCoord;                                                
	} fs_in;                                                          

                 
//        bool IsTrivial(int x,int width,int y, int height){
//		if ((gl_FragCoord.x > x ) &&
//			(gl_FragCoord.x < (x+width)) &&
//			(gl_FragCoord.y > y) &&"
//			(gl_FragCoord.y < (y+height)) ) {
//			    return true;
//		}
//		else
//			return false;
//	}

	void main(void)                                                    
	{                                                                  
		// if(IsTrivial(30,30,20,80))                                     
	     	//	color = vec4(1.0, 1.0, 1.0,0.1);                                
	    	//else                                                               
	    	color = fs_in.color;         

	}    
