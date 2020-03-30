#define M_PI 3.1415926535897932384626433832795
#define NUM_LIGHTS 32

struct Light {
    vec2 position;
    // color of the light
    vec3 diffuse;
    // power of the light
    float power;
};

uniform Light lights[NUM_LIGHTS];
uniform int num_lights;
uniform vec2 screen;

const float constant = 1.0;
const float linear = 90.0;
const float quadratic = 0.032;

uniform sampler2D texture;

void main()
{
    vec2 norm_screen = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
    vec3 diffuse = vec3(0);


    for (int i = 0; i < num_lights; i++) {
        Light light = lights[i];

        vec2 norm_pos = light.position / screen;
        float distance = length(norm_pos - norm_screen);
        float attenuation = 1.0 / (constant + distance * linear + quadratic * distance * distance) * light.power;
        diffuse += light.diffuse * attenuation;
    }

    diffuse = clamp(diffuse, 0.0, 1.0);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = vec4(diffuse, 1.0) * pixel;
}