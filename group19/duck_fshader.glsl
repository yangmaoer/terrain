#version 330 core

uniform vec3 Ia, Id, Is;
uniform float p;

in vec3 normal_mv_tmp;

// Light and view directions.
in vec3 lightDirWorld, viewDirCamera;

out vec3 color;

void main() {


    // Specular lightning only relevant for water surfaces.
    float ka, kd, ks;
    ka = 0.9f;
    kd = 0.4f;
	

	vec3 N= normalize(normal_mv_tmp);
	vec3 L = normalize(lightDirWorld);
	vec3 V = normalize(viewDirCamera);

	vec3 yellow_color = vec3(1.0f, 1.0f, 0.0f);


    /// TODO: Phong shading.
    /// 1) compute ambient term.
	vec3 ambient_color = Ia * ka * yellow_color;
    /// 2) compute diffuse term.
	vec3 diffuse_color = Id * kd * yellow_color * max(dot(N,L),0.0);
   
	color = ambient_color + diffuse_color;
	
}

