//#version 150

attribute vec4 position;        // モデル座標系における頂点の位置座標
attribute vec3 normal;	        // モデル座標系における頂点の法線ベクトル

varying vec4 colorVarying;	    // フラグメントシェーダに渡す色ベクトル

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

uniform mat4 normalMatrix;

// モデルカラー
uniform vec4 monoColor;

void main()
{
	// 光源の位置を設定
	vec3 lightDir = vec3(2.0, -3.0, 0.2);
//	vec3 normalZ = vec3(0.0, 0.0, 1.0);
	
	/**
	 *	ワールド変換
	 *	--> 位置座標、法線ベクトル
	 */
	vec4 wldModelPos = worldMatrix * position;
	vec4 wldNormal = normalMatrix * vec4(normal, 1.0);
	vec3 mToL = normalize(-lightDir);
	
	float nDotVP = max(0.0, dot(wldNormal.xyz, mToL));
	
    // 環境光の設定
    vec3 ambient = vec3(0.2);

	// ディフューズ色の設定
	vec3 diffuse = monoColor.rgb * nDotVP;
	colorVarying = vec4(diffuse + ambient, monoColor.a);
//	colorVarying = vec4(nDotVP, nDotVP, nDotVP, 1);
//	colorVarying = monoColor;
    
	// 位置座標設定
	gl_Position = projMatrix * viewMatrix * worldMatrix * position;
    
    gl_TexCoord[0] = gl_Position;
}
