#version 450 core                                              

out vec4 fragcolor;     
in vec4 OutColor;      
                                    
uniform vec4 col2D;                                            

void main()                                                    
{                                                              
   fragcolor = OutColor * col2D;                               
}  


    
