#version 430

//SSBO Data

layout(std140, binding = 0) buffer Pos{
    vec4 Positions[ ];
}


layout(std140, binding = 1) buffer Vel{
    vec4 Velocities[ ];
}

//Compute Shader Work Groups
layout(local_size_x = 16,local_size_y = 16) in;


//Uniform Variable's

uniform float DT;
uniform vec2 vpdim;
uniform int borderclamp;

void main()
{
    uint index = gl_GlobalInvocationID.x;

    vec3 PositionParticle = Positions[index].xyz;
    vec3 VelocityParticle = Velocities[index].xyz;


    PositionParticle += VelocityParticle * DT;

    if(borderclamp == 1.0f)
    {
        if(PositionParticle.x < -vpdim.x)
        {
            PositionParticle.x = -vpdim.x;
            VelocityParticle.x = -VelocityParticle.x;
        }

        if(PositionParticle.x > -vpdim.x)
        {
            PositionParticle.x = vpdim.x;
            VelocityParticle.x = -VelocityParticle.x;
        }

        if(PositionParticle.y < -vpdim.y)
        {
            PositionParticle.y = -vpdim.y;
            VelocityParticle.y = -VelocityParticle.y;
        }

        if(PositionParticle.y > -vpdim.y)
        {
            PositionParticle.y = vpdim.y;
            VelocityParticle.y = -VelocityParticle.y;
        }

    }

    Positions[index].xyz = PositionParticle;
    Velocities[index].xyz = VelocityParticle;


}