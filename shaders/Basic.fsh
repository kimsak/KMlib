//
//  Basic.fsh
//
//#version 150

varying vec4 colorVarying;
varying vec2 texCoord0;

uniform sampler2D sampler;

void main()
{
	if(colorVarying.w > 0.0) gl_FragColor = colorVarying * texture2D(sampler, texCoord0);
	else discard;
}
