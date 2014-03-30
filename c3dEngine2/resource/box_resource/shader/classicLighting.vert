
attribute vec4 a_position;

attribute vec4 a_normal;

attribute vec4 a_color;

attribute vec2 a_texCoord;





uniform mat4 modelMat;

uniform mat4 viewMat;

uniform mat4 projMat;

uniform mat4 normMat;

uniform vec4 lightPos_world;

uniform vec4 eyePos_world;

uniform vec4 diffuseMaterial;

uniform vec4 diffuseLight;

uniform vec4 ambientMaterial;

uniform vec4 ambientLight;

uniform vec4 specularMaterial;

uniform vec4 specularLight;

uniform float shininess;


varying vec4 v_mainColor;

varying vec4 v_secondaryColor;

varying vec2 v_texCoord;



void main(void){

    vec4 diffuseML=vec4(vec3(diffuseMaterial)*vec3(diffuseLight),diffuseMaterial.a);

    vec4 ambientML=ambientMaterial*ambientLight;

    vec4 specularML=specularMaterial*specularLight;

    //----get normal in world space

    vec4 norm_world = normMat*a_normal;

    //----get pos in world space

    vec4 pos_world = modelMat*a_position;

    //----lightPos already in world space

    //----calculate diffuse color

    vec4 posToLight=vec4(normalize(vec3(lightPos_world-pos_world)),0.0);

    float normDotPosToLight = max(0.0, dot(norm_world, posToLight));

    vec4 diffuseColor= vec4(normDotPosToLight*vec3(diffuseML),diffuseML.a);

    //----calculate ambient color

    vec4 ambientColor=ambientML;

    //----calculate specular color

    vec4 posToEye=vec4(normalize(vec3(eyePos_world-pos_world)),0.0);

    vec4 halfVector=(posToLight+posToEye)*0.5;

    float normDotHalfVector=max(0.0,dot(norm_world, halfVector));

    float pf=normDotHalfVector==0.0?0.0:pow(normDotHalfVector,shininess);

    vec4 specularColor= vec4(pf*vec3(specularML),1.0);

    //----set varying

    //the final alpha is equal to diffuseColor.a

    v_mainColor = vec4(vec3(ambientColor)+vec3(diffuseColor)*vec3(a_color),diffuseColor.a*a_color.a);

    float secondaryColorAlpha=pf;

    v_secondaryColor=vec4(vec3(specularColor),secondaryColorAlpha);

    v_texCoord = a_texCoord;

    gl_Position = projMat*viewMat* pos_world;


}