//#version 150

varying vec4 colorVarying;

void main()
{
    if(colorVarying.w > 0.0) gl_FragColor = colorVarying;
    else discard;
    gl_FragDepth = gl_TexCoord[0].z / gl_TexCoord[0].w;
}

