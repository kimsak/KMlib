//#version 150

varying vec4 colorVarying;
varying vec2 texCoord0;

uniform sampler2D sampler;

void main()
{
    vec2 n_texcoord = texCoord0;
    n_texcoord.y = 1.0 - texCoord0.y;

	if(colorVarying.w > 0.0) gl_FragColor = colorVarying * texture2D(sampler, n_texcoord);
	else discard;
    //gl_FragColor = colorVarying * texture2D(sampler, texCoord0);
}
