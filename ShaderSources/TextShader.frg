#version 440 core                                              

in VS_OUT {                                                    
	vec2 uv;                                                    
} fs_in;                                                       

out vec4 fragcolor;                                            
uniform sampler2D text;                                        
uniform vec4 col2D;                                            

void main()                                                    
{                                                              
	vec4 texel = texture(text,fs_in.uv);                       
	 
	if(texel.r == 0.0 && texel.g == 0.0 && texel.b == 0)        
		discard;                                                
    	else {                                                      
               vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.uv).r);
	       fragcolor =    sampled * col2D;                        
       }                                                           
}              
